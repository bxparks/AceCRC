/**
 * \file
 * Functions and types for CRC checks.
 *
 * Generated on Sat Feb 20 19:59:50 2021
 * by pycrc v0.9.2, https://pycrc.org
 * using the configuration:
 *  - Width         = 32
 *  - Poly          = 0x04c11db7
 *  - XorIn         = 0xffffffff
 *  - ReflectIn     = True
 *  - XorOut        = 0xffffffff
 *  - ReflectOut    = True
 *  - Algorithm     = table-driven
 *
 * Auto converted to Arduino C++ on Sat Feb 20 19:59:50 PST 2021
 * by AceCRC (https://github.com/bxparks/AceCRC).
 * DO NOT EDIT
 */
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_SAMD)
  #include <avr/pgmspace.h>
#else
  #include <pgmspace.h>
#endif
#include "crc32_nibble.hpp" // header file converted by AceCRC
#include <stdlib.h>
#include <stdint.h>

namespace ace_crc {
namespace crc32_nibble {



/**
 * Static table used for the table_driven implementation.
 */
static const crc_t crc_table[16] PROGMEM = {
    0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
};


crc_t crc_update(crc_t crc, const void *data, size_t data_len)
{
    const unsigned char *d = (const unsigned char *)data;
    uint8_t tbl_idx;

    while (data_len--) {
        tbl_idx = crc ^ *d;
        crc = (pgm_read_dword(crc_table + (tbl_idx & 0x0f))) ^ (crc >> 4);
        tbl_idx = crc ^ (*d >> 4);
        crc = (pgm_read_dword(crc_table + (tbl_idx & 0x0f))) ^ (crc >> 4);
        d++;
    }
    return crc & 0xffffffff;
}

} // crc32_nibble
} // ace_crc
