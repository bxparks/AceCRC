/**
 * \file
 * Functions and types for CRC checks.
 *
 * Generated on Fri Feb  3 16:16:46 2023
 * by pycrc v0.10.0, https://pycrc.org
 * using the configuration:
 *  - Width         = 16
 *  - Poly          = 0x1021
 *  - XorIn         = 0x1d0f
 *  - ReflectIn     = False
 *  - XorOut        = 0x0000
 *  - ReflectOut    = False
 *  - Algorithm     = table-driven
 *
 * Auto converted to Arduino C++ on Fri Feb  3 16:16:46 PST 2023
 * by AceCRC (https://github.com/bxparks/AceCRC).
 * DO NOT EDIT
 */
#include "crc16ccitt_nibblem.hpp" // header file converted by AceCRC
#include <stdlib.h>
#include <stdint.h>

namespace ace_crc {
namespace crc16ccitt_nibblem {



/**
 * Static table used for the table_driven implementation.
 */
static const crc_t crc_table[16] = {
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
    0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef
};


crc_t crc_update(crc_t crc, const void *data, size_t data_len)
{
    const unsigned char *d = (const unsigned char *)data;
    uint8_t tbl_idx;

    while (data_len--) {
        tbl_idx = (crc >> 12) ^ (*d >> 4);
        crc = crc_table[tbl_idx & 0x0f] ^ (crc << 4);
        tbl_idx = (crc >> 12) ^ (*d >> 0);
        crc = crc_table[tbl_idx & 0x0f] ^ (crc << 4);
        d++;
    }
    return crc & 0xffff;
}

} // crc16ccitt_nibblem
} // ace_crc
