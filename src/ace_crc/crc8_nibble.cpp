/**
 * \file
 * Functions and types for CRC checks.
 *
 * Generated on Sat Feb 20 19:59:49 2021
 * by pycrc v0.9.2, https://pycrc.org
 * using the configuration:
 *  - Width         = 8
 *  - Poly          = 0x07
 *  - XorIn         = 0x00
 *  - ReflectIn     = False
 *  - XorOut        = 0x00
 *  - ReflectOut    = False
 *  - Algorithm     = table-driven
 *
 * Auto converted to Arduino C++ on Sat Feb 20 19:59:49 PST 2021
 * by AceCRC (https://github.com/bxparks/AceCRC).
 * DO NOT EDIT
 */
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_SAMD)
  #include <avr/pgmspace.h>
#else
  #include <pgmspace.h>
#endif
#include "crc8_nibble.hpp" // header file converted by AceCRC
#include <stdlib.h>
#include <stdint.h>

namespace ace_crc {
namespace crc8_nibble {



/**
 * Static table used for the table_driven implementation.
 */
static const crc_t crc_table[16] PROGMEM = {
    0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b, 0x12, 0x15, 0x38, 0x3f, 0x36, 0x31, 0x24, 0x23, 0x2a, 0x2d
};


crc_t crc_update(crc_t crc, const void *data, size_t data_len)
{
    const unsigned char *d = (const unsigned char *)data;
    uint8_t tbl_idx;

    while (data_len--) {
        tbl_idx = (crc >> 4) ^ (*d >> 4);
        crc = (pgm_read_byte(crc_table + (tbl_idx & 0x0f))) ^ (crc << 4);
        tbl_idx = (crc >> 4) ^ (*d >> 0);
        crc = (pgm_read_byte(crc_table + (tbl_idx & 0x0f))) ^ (crc << 4);
        d++;
    }
    return crc & 0xff;
}

} // crc8_nibble
} // ace_crc
