/*
 * MIT License
 * Copyright (c) 2020 Brian T. Park
 */

/**
 * @mainpage AceCRC Library
 *
 * This is the Doxygen documentation for the
 * <a href="https://github.com/bxparks/AceCRC">AceCRC Library</a>.
 *
 * Click on the "Classes" menu above to see the list of classes.
 *
 * Click on the "Files" menu above to see the list of header files.
 */

#ifndef ACE_CRC_ACE_CRC_H
#define ACE_CRC_ACE_CRC_H

#include "ace_crc/crc8_bit.hpp"
#include "ace_crc/crc8_byte.hpp"
#include "ace_crc/crc8_nibble.hpp"
#include "ace_crc/crc8_nibblem.hpp"

#include "ace_crc/crc16ccitt_bit.hpp"
#include "ace_crc/crc16ccitt_byte.hpp"
#include "ace_crc/crc16ccitt_nibble.hpp"
#include "ace_crc/crc16ccitt_nibblem.hpp"

#include "ace_crc/crc32_bit.hpp"
#include "ace_crc/crc32_byte.hpp"
#include "ace_crc/crc32_nibble.hpp"
#include "ace_crc/crc32_nibblem.hpp"

// Version format: xxyyzz == "xx.yy.zz"
#define ACE_CRC_VERSION 402
#define ACE_CRC_VERSION_STRING "0.4.2"

#endif
