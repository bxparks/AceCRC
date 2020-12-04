# AceCRC

This library contains a number of CRC algorithms that were generated from
`pycrc` (https://pycrc.org) and programmatically converted to Arduino format to
use C++ namespaces to avoid name collisions and `PROGMEM` flash memory for
lookup tables to save static RAM. From the [list of pycrc supported
algorithms](https://pycrc.org/models.html), this library supports:

* CRC-8
* CRC-16-CCITT
* CRC-32

For each algorithm, 3 different implementations were generated:

* bit-by-bit (bit)
    * brute-force loops to calculate the polynomial divisions
    * smallest code size, but slowest
* table lookup using 4-bits (nibble)
    * generates a lookup table of 16 elements
    * larger code size, but faster
* table lookup using 8-bits (byte)
    * generates a lookup table of 256 elements
    * largest code size, but fastest

The `pycrc` program generates `*.h` and `*.c` files containing C99 code with the
following definitions:

* `crc_t crc_init(void);`
* `crc_t crc_update(crc_t crc, const void *data, size_t data_len);`
* `crc_t crc_finalize(crc_t crc);`

This library converts the C99 code in the following way:

* each algorithm and variant is wrapped its own C++ namespace to avoid name
  collision
    * `ace_crc::crc8_bit`
    * `ace_crc::crc8_nibble`
    * `ace_crc::crc8_byte`
    * `ace_crc::crc16ccitt_bit`
    * `ace_crc::crc16ccitt_nibble`
    * `ace_crc::crc16ccitt_byte`
    * `ace_crc::crc32_bit`
    * `ace_crc::crc32_nibble`
    * `ace_crc::crc32_byte`
* a convenience function `crc_t crc_calculate(const void *data, size_t
  data_len)` is inserted into the header file of each namespace
    * calculates the CRC in one-shot
* the `crc_table` lookup table is moved into flash memory using `PROGMEM`
    * the static RAM usage of all CRC routines becomes zero (other than a few
      stack variables)
    * (Note that on platforms that do not support flash memory storage of
      data, `PROGMEM` is a no-op, and the various `pgm_read_{xxx}()` routines
      become just normal memory accessors.)
* the `static` keyword is removed from header files
    * not needed in C++ 
    * prevents generation of doxygen docs for those functions
* the `#define CRC_ALGO_{XXX}` macro is converted into a `const uint8_t`
    * becomes part of its enclosing namespace, preventing name collision
* the typedef for `crc_t` is changed from `uint_fast8_t`, `uint_fast16_t`, and
  `uint_fast32_t` to `uint8_t`, `uint16_t`, and `uint32_t` respectively
    * affects only 32-bit processors, and only the `crc8` and `crc16ccitt_*`
      algorithms
    * see section [Integer Sizes](#IntegerSizes) below for more information

**Version**: 0.3.1 (2020-12-03)

**Changelog**: [CHANGELOG.md](CHANGELOG.md)

**Table of Contents**:

* [HelloCRC](#HelloCRC)
* [Installation](#Installation)
    * [Dependencies](#Dependencies)
* [Documentation](#Documentation)
* [Usage](#Usage)
    * [Headers and Namespaces](#Headers)
    * [Core CRC Functions](#CoreFunctions)
    * [Integer Sizes](#IntegerSizes)
* [Resource Consumption](#ResourceConsumption)
    * [Memory Benchmarks](#MemoryBenchmarks)
    * [CPU Benchmarks](#CpuBenchmarks)
    * [Recommendations](#Recommendations)
* [Background and Motivation](#Motivation)
    * [Other CRC Libraries](#OtherLibraries)
* [Bugs and Limitations](#Bugs)
* [System Requirements](#SystemRequirements)
    * [Tool Chain](#ToolChain)
    * [Hardware](#Hardware)
    * [Operating System](#OperatingSystem)
* [License](#License)
* [Feedback and Support](#Feedback)
* [Authors](#Authors)


<a name="HelloCRC"></a>
## HelloCRC

Here is the sample program from [examples/HelloCRC](examples/HelloCRC) that uses
the CRC-16-CCITT algorithm using a 4-bit lookup table (16 elements):

```C++
#include <Arduino.h>
#include <AceCRC.h>

using namespace ace_crc::crc16ccitt_nibble;

static const char CHECK_STRING[] = "123456789";
static const size_t LENGTH = sizeof(CHECK_STRING) - 1;

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait - Leonardo/Micro

  crc_t crc = crc_init();
  crc = crc_update(crc, CHECK_STRING, LENGTH);
  crc = crc_finalize(crc);
  Serial.print("0x");
  Serial.println((unsigned long) crc, 16);

  crc = crc_calculate(CHECK_STRING, LENGTH);
  Serial.print("0x");
  Serial.println((unsigned long) crc, 16);
}

void loop() {
}
```

This prints the hexadecimal numbers
```
0xE5CC
0xE5CC
```
as expected.

<a name="Installation"></a>
## Installation

The latest stable release is available in the Arduino IDE Library Manager.
Search for "AceCRC" and click install.

The development version can be installed by cloning the git repo:

* AceCRC (https://github.com/bxparks/AceCRC)

You can copy over the contents to the `./libraries` directory used by the
Arduino IDE. (The result is a directory named `./libraries/AceCRC`). Or you can
create symlinks from `./libraries` to these directories.

The `develop` branch contains the latest development.
The `master` branch contains the stable releases.

<a name="Dependencies"></a>
### Dependencies

This library has no external dependencies for client use. But the following
dependencies are required for development and testing purposes:

* To regenerate and rebuild the source code, you need pycrc
  (https://pycrc.org/).
* To run the unit tests under `tests`, you need AUnit
  (https://github.com/bxparks/AUnit)
* To run the unit tests under Linux or MacOS, you need UnixHostDuino
  (https://github.com/bxparks/UnixHostDuino)

<a name="Documentation"></a>
## Documentation

* [README.md](README.md) - this file
* [Doxygen docs](https://bxparks.github.io/AceCRC/html) hosted on GitHub Pages
* [examples/benchmarks](examples/benchmarks) - for memory and CPU consumption
  number for each algorithm on various microcontrollers.

<a name="Usage"></a>
## Usage

<a name="Headers"></a>
### Headers and Namespaces

Only a single header file `AceCRC.h` is required to use this library.

```C++
#include <AceCRC.h>
```

Then select the namespace of the algorithm that you want to use. For example,
to use the version of `crc32` which uses a 4-bit table (16 entries), use the
following:

```C++
using namespace ace_crc::crc32_nibble;
```

To use the 8-bit table: use:

```C++
using namespace ace_crc::crc32_byte;
```

<a name="CoreFunctions"></a>
### Core CRC Functions

All algorithms and their variants are placed in separate C++ namespaces so they
do not collide, and you can use multiple CRC algorithms in a single program
without worrying about name collision.

The `crc_t` typedef, the function names, and their signatures from the
underlying generated code from `pycrc` remain unchanged. For reference, the
principle functions are:

* `crc_t crc_init(void);`
* `crc_t crc_update(crc_t crc, const void *data, size_t data_len);`
* `crc_t crc_finalize(crc_t crc);`

This library adds the following convenience function to each header file in each
namespace:

* `crc_t crc_calculate(const void *data, size_t data_len);`

See the [examples/HelloCRC](examples/HelloCRC) example code to see how these
functions are used. The `crc_update()` function can be called multiple times
with additional data, before calling `crc_finalize()`.

The `crc_calculate()` convenience function replaces the three separate calls to
`crc_init()`, `crc_update()`, `crc_finalize()` with a single call.

<a name="IntegerSizes"></a>
### Integer Sizes

By default, the `pycrc` program generates C99 code which contains one of the
following definitions of the `crc_t` type:

```C++
typedef uint_fast8_t crc_t;
typedef uint_fast16_t crc_t;
typedef uint_fast32_t crc_t;
```

These are converted by this library to these instead:
```C++
typedef uint8_t crc_t;
typedef uint16_t crc_t;
typedef uint32_t crc_t;
```

On 8-bit processors, `uint_fast8_t` is identical to `uint8_t`, `uint_fast16_t`
is identical to `uint16_t`, and `uint_fast32_t` is identical to `uint32_t`.

On 32-bit processors (e.g. SAMD, ESP8266, ESP32), `uint_fast8_t` and
`uint_fast16_t` are both defined to be `uint32_t`, presumably because the 32-bit
integer type is faster for most operations (but not always). The main effect of
these definitions is to increase the size of the `crc_table` for the CRC-8 and
CRC-16-CCITT algorithms by a factor of 4x or 2x, compared to what they could be.

After collecting the CPU and memory consumption results of various algorithms on
different microcontrollers in [examples/benchmarks](examples/benchmarks), I
found that using the smaller `uint8_t` or `uint16_t` did not affect the speed of
the algorithms very much (2-14%). Some were got slightly slower, but some
actually got slightly faster using the exact `uint8_t` and `uint16_t` types,
which are supposed to be slower.

The bigger difference is the sizes of the internal `crc_table` which become a
lot smaller when the `crc_t` becomes smaller. It also seemed potentially
confusing for the end user if `sizeof(crc_t)` returned 4 instead of 1 or 2 when
using the CRC-8 or CRC-16-CCITT algorithms.

I concluded that it was better in the Arduino microcontroller environments to
make the `crc_t` type correspond to the exact sized integer types (`uint8_t`,
`uint16_t`, `uint32_t`).

The `size_t` is used as the type of the `data_len` parameter of the
`crc_update()` or the `crc_calculate()` function. On 8-bit processors `size_t`
is 2 bytes, and on 32-bit processors `size_t` is 4 bytes. To calculate the CRC
of an array that's longer than 64 kiB long on 8-bit processors, it must be
broken down into chunks smaller than 64 kiB and processed through the
`crc_update()` function multiple times. I suspect that this situation will
happen only rarely on 8-bit processors which tend to deal with fairly small
amounts of data.

<a name="ResourceConsumption"></a>
## Resource Consumption

<a name="MemoryBenchmarks"></a>
### Memory Benchmarks

I wrote a bunch of scripts in
[examples/benchmarks/MemoryBenchmark](examples/benchmarks/MemoryBenchmark) to
automatically gather the flash and static RAM consumption of various CRC
algorithms on various microcontrollers. The results are summarized in the
`README.md` in that directory. None of the algorithms consumed any static RAM,
because all their lookup tables are located in flash using `PROGMEM`.

Here are rough flash memory consumption for each algorithm:

* `crc8_bit`: 64-130 bytes
* `crc8_nibble`: 80-150 bytes
* `crc8_byte`: 290-360 bytes
* `crc16ccitt_bit`: 90-140 bytes
* `crc16ccitt_nibble`: 100-190 bytes
* `crc16ccitt_byte`: 560-630 bytes
* `crc32_bit`: 110-190 bytes
* `crc32_nibble`: 140-220 bytes
* `crc32_byte`: 1100-1200 bytes

<a name="CpuBenchmarks"></a>
### CPU Benchmarks

The CPU performance of each CRC algorithm and variant is given in
[examples/benchmarks/CpuBenchmark](examples/benchmarks/CpuBenchmark) as units of
microseconds per kiB (1024 bytes).

For 8-bit processors (e.g. Nano, Micro), the numbers are roughly:
* "bit": 13000-18000 micros/kiB
* "nibble": 7000-9000 micros/kiB
* "byte": 1500-2400 micros/kiB

For 32-bit processors (e.g. SAMD, ESP8266, ESP32), the numbers are in the range
of:
* "bit": 500-3000 micros/kiB
* "nibble": 100-700 micros/kiB
* "byte": 70-400 micros/kiB

<a name="Recommendations"></a>
### Recommendations

The benchmark numbers from `CpuBenchmark` and `MemoryBenchmark` are combined
into a single place in [examples/benchmarks](examples/benchmarks) for
convenience.

Comparing the different variants ("bit", "nibble" and "byte"), it seems that the
"nibble" variants (4-bit lookup table) offer a good tradeoff between
flash memory consumption and CPU speed in the following ways:

* Compared to the "bit" versions, the "nibble" variants are about the same size
  but they can be up to ~2X (8-bit) to ~5X (32-bit) faster.
* Compared to the "byte" versions, the "nibble" variants can be 4-5X
  smaller in flash size, but only about 3-4X (8-bit) to 1.5-2X (32-bit) slower.

The CRC-8 algorithm has the unfortunate property that arrays of zeros of
different lengths (e.g. 1 zero or 2 zeros) have the exact same CRC (0). The
other two (CRC-16-CCITT and CRC32) are able to distinguish strings of zeroes of
different lengths. In terms of flash size and performance, the CRC-8 algorithm
is not all that much faster than the CRC-16-CCITT, even on 8-bit processors. For
these reasons, the CRC-8 algorithm is not recommended, unless you are really
strapped for flash bytes.

The CRC-16-CCITT was selected for this library over the CRC-16 algorithm because
CRC-16 suffers the same problem as CRC-8 with regards to arrays of zeros of
different lengths. The CRC-16-CCITT uses a non-zero XOR-input which allows it to
distinguish different lengths of zeros.

Between the CRC-16-CCITT and CRC-32 algorithms, if we look at the `_nibble`
variants, there is very little difference in flash size and CPU speed, even on
8-bit processors. On 32-bit processors, the CRC-32 is actually faster. The
advantage of CRC-32 over CRC-16-CCITT is that 32 bits will be able to detected
far more errors than 16 bits.

Putting all these together, here are my recommended algorithms in decreasing
order of preference:
1. `crc32_nibble` in most situtations for a balance of flash size (~200 bytes)
   and speed
2. `crc16ccitt_nibble` to save 60 bytes of flash on 8-bit AVR processors, with
   a reasonable amount of error detection
3. `crc32_byte` if you need the fastest algorithm and you have 1100 bytes of
   flash to spare
4. `crc16ccitt_bit` if you need to implement a very tiny CRC algorithm (90 bytes
   on an 8-bit AVR processor), and you are not worried about speed
5. `crc8_bit` if you need to implement the absolute smallest CRC algorithm (80
   bytes on an 8-bit AVR processor), and you are not worried about speed, and
   you can tolerate high chances of corruption

You can consult the results in [examples/benchmarks](examples/benchmarks) to
determine exactly you want to make the space versus time tradeoff for your
specific application.

<a name="Motivation"></a>
## Background and Motiviation

Before writing this library, I did not understand how CRC algorithms worked and
how they were implemented. I just knew that they calculated a checksum. I had
been using the `crc32()` algorithm from the FastCRC library
(https://github.com/FrankBoesing/FastCRC) but when I dug in a little deeper, I
discovered that it was configured to use "large tables" by default, which is
why it is "fast". But that meant that the `crc32()` algorithm was pulling in a
table of 1024 elements of 4 bytes each, for a total of 4kB.

The `crc32()` function was being called from my `CrcEeprom` class
(https://github.com/bxparks/AceUtils), which I had included in various
applications running on an Arduino Nano or Sparkfun Pro Micro with only 32kB of
flash. Due to my ignorance, I was using at least 1/8 of my flash memory budget
just to calculate the CRC32!

I decided to figure out how to write my own CRC routines. The best reference I
found was [A Painless Guide to CRC Error Detection
Algorithms](http://ross.net/crc/download/crc_v3.txt) by Ross Williams written in
1993. Once I read that, I could understand how a code generator such as `pycrc`
(https://pycrc.org/) worked. For each algorithm type (with a given polynomial
generator), the `pycrc` code can generate multiple implementations. The 3 that
seemed most useful in the context of small memory Arduino microcontrollers were:

* bit-by-bit brute force algorithm
* 4-bit lookup table using 16 elements
* 8-bit lookup table using 256 elements

I calculated the flash and static memory consumption of each algorithm using
[examples/benchmarks/MemoryBenchmark](examples/benchmarks/MemoryBenchmark). From
those benchmarks, I can see that I am able to reduce the flash memory usage of
the `CrcEeprom` class by a least 4kB by using a CRC algorithm that consumes only
about 150-250 bytes (either the CRC16CCITT or CRC32 algorithm using a 4-bit
lookup table).

<a name="OtherLibraries"></a>
### Other CRC Libraries

I did a quick survey of existing CRC libraries for Arduino, before deciding to
write my own. Part of the motiation was that I wanted to learn this stuff. The
other part was that the existing libraries did not offer me enough control over
space and time tradeoffs.

* Arduino_CRC32 (https://github.com/arduino-libraries/Arduino_CRC32)
    * uses pycrc to generate the CRC-32 with 8-bit lookup table
    * equivalent to `crc32_byte` algorithm in the AceCRC library
    * does **not** use `PROGMEM`, so the lookup table consumes 1024 bytes of
      static RAM
* CRCx (https://github.com/hideakitai/CRCx)
    * a thin abstraction layer on top of FastCRC
      (https://github.com/FrankBoesing/FastCRC) and
      CRCpp (https://github.com/d-bahr/CRCpp)
    * FastCRC is used for Arduino
    * FastCRC and CRCpp are *vendored* (copied) into that library
    * FastCRC uses extra large tables by default and does not use `PROGMEM`, as
      described above
* CRC32 (https://github.com/bakercp/CRC32)
    * uses a 4-bit lookup table
    * equivalent to `crc32_nibble` algorithm in the AceCRC library
    * uses `PROGMEM` if available
* FastCRC (https://github.com/FrankBoesing/FastCRC)
    * uses extra large lookup tables (1024 elements, instead of usual 256
      elements) by default
    * does **not** use `PROGMEM` so lookup tables consume static RAM on AVR
      processors and ESP8266
    * no longer availabe on Arduino Library Manager
      (see https://github.com/FrankBoesing/FastCRC/issues/25)
* uCRC16BPBLib (https://github.com/Naguissa/uCRC16BPBLib)
    * calculates CRC-16-CCITT using bit-by-bit loop
    * allows incremental CRC16 to be updated bit-by-bit
    * does not use lookup table
* uCRC16Lib (https://github.com/Naguissa/uCRC16Lib)
    * I think the same bit-by-bit internal loop as above
    * but exposes only byte-by-byte API
* uCRC16XModemLib (https://github.com/Naguissa/uCRC16XModemLib)
    * calculates CRC-16-XMODEM using bit-by-bit loop

Some platforms include an implementation of a CRC algorithm in a core header
or an example file:

* ESP8266
    * `#include <coredecls.h>`
    * `uint32_t crc32 (const void* data, size_t length,
        uint32_t crc = 0xffffffff);`
    * performs a bit-by-bit loop with no lookup table
    * equivalent to `crc32_bit` in the AceCRC library
* AVR
    * `arduino/hardware/avr/1.8.3/libraries/EEPROM/examples/eeprom_crc/eeprom_crc.ino`
    * contains a CRC-32 implementation using a 4-bit lookup table
    * equivalent to `crc32_nibble` in AceCRC

<a name="Bugs"></a>
## Bugs and Limitations

None that I know of right now.

<a name="SystemRequirements"></a>
## System Requirements

<a name="ToolChain"></a>
### Tool Chain

* [Arduino IDE 1.8.13](https://www.arduino.cc/en/Main/Software)
* [Arduino AVR Boards 1.8.3](https://github.com/arduino/ArduinoCore-avr)
* [Arduino SAMD Boards 1.8.9](https://github.com/arduino/ArduinoCore-samd)
* [SparkFun AVR Boards 1.1.13](https://github.com/sparkfun/Arduino_Boards)
* [SparkFun SAMD Boards 1.8.1](https://github.com/sparkfun/Arduino_Boards)
* [ESP8266 Arduino 2.7.4](https://github.com/esp8266/Arduino)
* [ESP32 Arduino 1.0.4](https://github.com/espressif/arduino-esp32)
* [Teensydino 1.53](https://www.pjrc.com/teensy/td_download.html)

<a name="Hardware"></a>
### Hardware

The library is extensively tested on the following boards:

* Arduino Nano clone (16 MHz ATmega328P)
* SparkFun Pro Micro clone (16 MHz ATmega32U4)
* SAMD21 M0 Mini (48 MHz ARM Cortex-M0+) (compatible with Arduino Zero)
* WeMos D1 Mini clone (ESP-12E module, 80 MHz ESP8266)
* ESP32 dev board (ESP-WROOM-32 module, 240 MHz dual core Tensilica LX6)

I will occasionally test on the following hardware as a sanity check:

* Teensy 3.2 (72 MHz ARM Cortex-M4)
* Mini Mega 2560 (Arduino Mega 2560 compatible, 16 MHz ATmega2560)

<a name="OperatingSystem"></a>
### Operating System

I use Ubuntu 18.04 and 20.04 for the vast majority of my development. I expect
that the library will work fine under MacOS and Windows, but I have not tested
them.

The generator script in `./tools/generate.sh` has only been tested under Ubuntu
20.04.

<a name="License"></a>
## License

[MIT License](https://opensource.org/licenses/MIT)

<a name="Feedback"></a>
## Feedback and Support

If you have any questions, comments, bug reports, or feature requests, please
file a GitHub ticket instead of emailing me unless the content is sensitive.
(The problem with email is that I cannot reference the email conversation when
other people ask similar questions later.) I'd love to hear about how this
software and its documentation can be improved. I can't promise that I will
incorporate everything, but I will give your ideas serious consideration.

<a name="Authors"></a>
## Authors

Created by Brian T. Park (brian@xparks.net).
