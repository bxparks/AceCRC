#!/bin/bash
#
# Generate CRC source code using pycrc (https://pycrc.org). Then convert the
# C-code into Arduino-compatible C++ code using the old Unix ed(1) editor.
#
# The 3 supported algorithms from pycrc are:
#
#   * bit: --algorithm bit-by-bit-fast
#   * nibble: --algorithm table-driven table-idx-width 4
#   * byte: --algorithm table-driven --table-idx-width 8

set -eu

# Set this to 0 to prevent conversion to PROGMEM and <pgmspace.h>.
# Might be useful to turn it off for debugging.
CONVERT_TO_PROGMEM=1

# Set this to 1 to preserve a copy of the original *.c and *.h files from pycrc.
# Useful for debugging purposes.
PRESERVE_C_FILES=0

function usage() {
    echo "Usage: generate.sh [--help|-h] \
    [--model {crc32|crc16ccitt}] [--algotag {bit|nibble|byte}] \
    {--header | --source}"
    exit 1
}

# Generate the *.h header file.
function generate_h() {
    local modelroot=$1
    local model=$2
    local flags="$3"
    local fileroot="${modelroot}_${algotag}"

    python3 -m pycrc \
        --model $model \
        $flags \
        --generate h \
        -o $fileroot.h
}

# Generate the *.c source file
function generate_c() {
    local modelroot=$1
    local model=$2
    local flags="$3"
    local fileroot="${modelroot}_${algotag}"

    python3 -m pycrc \
        --model $model \
        $flags \
        --generate c \
        -o $fileroot.c
}

# Convert C-style *.h file to Arduino C++ *.hpp file
function convert_h_to_hpp() {
    local modelroot=$1
    local algotag=$2
    local model=$3
    local old_header_guard=$4
    local new_header_guard=$5
    local fileroot="${modelroot}_${algotag}"

    ed $fileroot.h > /dev/null <<EOF
/ \*\//
i
 *
 * Auto converted to Arduino C++ on $(date)
 * by AceCRC (https://github.com/bxparks/AceCRC).
 * DO NOT EDIT
.
/#ifndef $old_header_guard/
.,+1s/$old_header_guard/$new_header_guard/
/#ifdef __cplusplus/
.,+2c
namespace ace_crc {
namespace $fileroot {
.
/#define CRC_ALGO/
s/#define/static const uint8_t/
s/ \([0-9][0-9]*\)$/ = \1;/
/#ifdef __cplusplus/
.,+2c
} // $fileroot
} // ace_crc
.
/#endif.*${old_header_guard}/
s/$old_header_guard/$new_header_guard/
w $fileroot.hpp
q
EOF

    if [[ $PRESERVE_C_FILES == 0 ]]; then
        rm $fileroot.h
    fi
}

# Convert C-style *.c file to Arduino C++ *.cpp file
function convert_c_to_cpp() {
    local modelroot=$1
    local algotag=$2
    local model=$3
    local pgm_read_func=$4
    local fileroot="${modelroot}_${algotag}"

    # The bit-by-bit algorithm does not use a crc_table, so we cannot attempt
    # to convert it to PROGMEM. Otherwise ed(1) script fails with error.
    if [[ $algotag == 'bit' || $CONVERT_TO_PROGMEM == 0 ]]; then
        ed $fileroot.c > /dev/null <<EOF
/ \*\//
i
 *
 * Auto converted to Arduino C++ on $(date)
 * by AceCRC (https://github.com/bxparks/AceCRC).
 * DO NOT EDIT
.
/#include "$fileroot.h"/
c
#include "$fileroot.hpp" // header file converted by AceCRC
.
/^$/a
namespace ace_crc {
namespace $fileroot {

.
\$a

} // $fileroot
} // ace_crc
.
w $fileroot.cpp
q
EOF

    # These algorithms use the 'crc_table' so move that table into flash memory
    # using PROGMEM, then convert the crc_table[i] expressions with the
    # equivalent ones using pgm_read_word() or pgm_read_dword().
    else
        ed $fileroot.c > /dev/null <<EOF
/ \*\//
i
 *
 * Auto converted to Arduino C++ on $(date)
 * by AceCRC (https://github.com/bxparks/AceCRC).
 * DO NOT EDIT
.
/#include "$fileroot.h"/
c
#include "$fileroot.hpp" // header file converted by AceCRC
.
i
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_SAMD)
  #include <avr/pgmspace.h>
#else
  #include <pgmspace.h>
#endif
.
/^$/a
namespace ace_crc {
namespace $fileroot {

.
/crc_table/s/= {/PROGMEM &/
g/crc_table\[\(tbl_idx.*\)\]/s//($pgm_read_func(crc_table + (\1)))/
\$a

} // $fileroot
} // ace_crc
.
w $fileroot.cpp
q
EOF
    fi

    if [[ $PRESERVE_C_FILES == 0 ]]; then
        rm $fileroot.c
    fi
}

header=0
source=0
model=''
algotag=''
while [[ $# -gt 0 ]]; do
    case $1 in
        --help|-h) usage ;;
        --header) header=1 ;;
        --source) source=1 ;;
        --model) shift; model="$1" ;;
        --algotag) shift; algotag="$1" ;;
        --) shift; break ;;
        -*) echo "Unknown flag '$1'" 1>&2; usage 1>&2 ;;
        *) break ;;
    esac
    shift
done

if [[ "$algotag" == '' ]]; then
    echo '--algotag is required'
    usage
fi
if [[ "$model" == '' ]]; then
    echo '--model is required'
    usage
fi

# Convert "crc-16-ccitt" to "crc16ccitt"
modelroot=$(echo $model | sed -e 's/-//g')
modelroot_upper="$(echo $modelroot | tr '[a-z]' '[A-Z]')"
algotag_upper="$(echo $algotag | tr '[a-z]' '[A-Z]')"

# CPP header guard e.g. "CRC16CCITT_BIT_H"
old_header_guard="${modelroot_upper}_${algotag_upper}_H"
new_header_guard="ACE_CRC_${modelroot_upper}_${algotag_upper}_HPP"

# Convert algotag to pycrc flags.
case $algotag in
    bit) pycrc_flags='--algorithm bit-by-bit-fast' ;;
    nibble) pycrc_flags='--algorithm table-driven --table-idx-width 4' ;;
    byte) pycrc_flags='--algorithm table-driven --table-idx-width 8' ;;
    *) echo "Unknown --algotag '$algotag'"; usage ;;
esac

# Determine the <progmem.h> function that extracts the lookup table.
case $model in
    crc-16-ccitt) pgm_read_func='pgm_read_word' ;;
    crc-32) pgm_read_func='pgm_read_dword' ;;
    *) echo 'Unknown --model '$model''; usage ;;
esac

# Perform the action that was requested by --header or --source.
if [[ $header == 1 ]]; then
    generate_h $modelroot $model "$pycrc_flags"
    convert_h_to_hpp $modelroot $algotag $model \
        $old_header_guard $new_header_guard
fi

if [[ $source == 1 ]]; then
    generate_c $modelroot $model "$pycrc_flags"
    convert_c_to_cpp $modelroot $algotag $model $pgm_read_func
fi
