/**
 * \file
 * Functions and types for CRC checks.
 *
 * Generated on Fri Feb  3 16:16:46 2023
 * by pycrc v0.10.0, https://pycrc.org
 * using the configuration:
 *  - Width         = 16
 *  - Poly          = 0x8005
 *  - XorIn         = 0xffff
 *  - ReflectIn     = True
 *  - XorOut        = 0x0000
 *  - ReflectOut    = True
 *  - Algorithm     = bit-by-bit-fast
 *
 * Auto converted to Arduino C++ on Fri Feb  3 16:16:46 PST 2023
 * by AceCRC (https://github.com/bxparks/AceCRC).
 * DO NOT EDIT
 */
#include "crc16modbus_bit.hpp" // header file converted by AceCRC
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

namespace ace_crc {
namespace crc16modbus_bit {



crc_t crc_reflect(crc_t data, size_t data_len)
{
    unsigned int i;
    crc_t ret;

    ret = data & 0x01;
    for (i = 1; i < data_len; i++) {
        data >>= 1;
        ret = (ret << 1) | (data & 0x01);
    }
    return ret;
}


crc_t crc_update(crc_t crc, const void *data, size_t data_len)
{
    const unsigned char *d = (const unsigned char *)data;
    uint8_t i;
    crc_t bit;
    unsigned char c;

    while (data_len--) {
        c = *d++;
        for (i = 0x01; i & 0xff; i <<= 1) {
            bit = (crc & 0x8000) ^ ((c & i) ? 0x8000 : 0);
            crc <<= 1;
            if (bit) {
                crc ^= 0x8005;
            }
        }
        crc &= 0xffff;
    }
    return crc & 0xffff;
}

} // crc16modbus_bit
} // ace_crc
