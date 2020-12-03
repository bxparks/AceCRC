/**
 * \file
 * Functions and types for CRC checks.
 *
 * Generated on Thu Dec  3 12:33:17 2020
 * by pycrc v0.9.2, https://pycrc.org
 * using the configuration:
 *  - Width         = 16
 *  - Poly          = 0x1021
 *  - XorIn         = 0x1d0f
 *  - ReflectIn     = False
 *  - XorOut        = 0x0000
 *  - ReflectOut    = False
 *  - Algorithm     = bit-by-bit-fast
 *
 * Auto converted to Arduino C++ on Thu Dec  3 12:33:17 PST 2020
 * by AceCRC (https://github.com/bxparks/AceCRC).
 * DO NOT EDIT
 */
#include "crc16ccitt_bit.hpp" // header file converted by AceCRC
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

namespace ace_crc {
namespace crc16ccitt_bit {



crc_t crc_update(crc_t crc, const void *data, size_t data_len)
{
    const unsigned char *d = (const unsigned char *)data;
    unsigned int i;
    bool bit;
    unsigned char c;

    while (data_len--) {
        c = *d++;
        for (i = 0x80; i > 0; i >>= 1) {
            bit = crc & 0x8000;
            if (c & i) {
                bit = !bit;
            }
            crc <<= 1;
            if (bit) {
                crc ^= 0x1021;
            }
        }
        crc &= 0xffff;
    }
    return crc & 0xffff;
}

} // crc16ccitt_bit
} // ace_crc
