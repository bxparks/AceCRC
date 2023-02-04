#line 2 "Crc8Test.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AceCRC.h>

using aunit::TestRunner;
using namespace ace_crc;

static const char CHECK_STRING[] = "123456789";
static const size_t LENGTH = sizeof(CHECK_STRING) - 1;
static uint8_t EXPECTED_CRC = 0xf4;

static const size_t ZEROS_LENGTH = 4;
static char ZEROES[ZEROS_LENGTH] = {0, 0, 0, 0};

// --------------------------------------------------------------------------
// crc8_bit
// --------------------------------------------------------------------------

test(crc8_bit, check) {
  uint8_t crc = crc8_bit::crc_calculate(CHECK_STRING, LENGTH);
  assertEqual(EXPECTED_CRC, crc);
}

// Arrays of zeros of different lengths ALL have CRC=0 for CRC8, making it
// unsuitable for situations where a string of zeros is likely to happen.
test(crc8_bit, zeros) {
  uint8_t crc1 = crc8_bit::crc_calculate(ZEROES, 1);
  uint8_t crc2 = crc8_bit::crc_calculate(ZEROES, 2);
  uint8_t crc3 = crc8_bit::crc_calculate(ZEROES, 3);
  uint8_t crc4 = crc8_bit::crc_calculate(ZEROES, 4);

  assertEqual((uint8_t) 0, crc1);
  assertEqual((uint8_t) 0, crc2);
  assertEqual((uint8_t) 0, crc3);
  assertEqual((uint8_t) 0, crc4);
}

// --------------------------------------------------------------------------
// crc8_nibble
// --------------------------------------------------------------------------

test(crc8_nibble, check) {
  uint8_t crc = crc8_nibble::crc_calculate(CHECK_STRING, LENGTH);
  assertEqual(EXPECTED_CRC, crc);
}

// Arrays of zeros of different lengths ALL have CRC=0 for CRC8, making it
// unsuitable for situations where a string of zeros is likely to happen.
test(crc8_nibble, zeros) {
  uint8_t crc1 = crc8_nibble::crc_calculate(ZEROES, 1);
  uint8_t crc2 = crc8_nibble::crc_calculate(ZEROES, 2);
  uint8_t crc3 = crc8_nibble::crc_calculate(ZEROES, 3);
  uint8_t crc4 = crc8_nibble::crc_calculate(ZEROES, 4);

  assertEqual((uint8_t) 0, crc1);
  assertEqual((uint8_t) 0, crc2);
  assertEqual((uint8_t) 0, crc3);
  assertEqual((uint8_t) 0, crc4);
}

// --------------------------------------------------------------------------
// crc8_nibblem
// --------------------------------------------------------------------------

test(crc8_nibblem, check) {
  uint8_t crc = crc8_nibblem::crc_calculate(CHECK_STRING, LENGTH);
  assertEqual(EXPECTED_CRC, crc);
}

// Arrays of zeros of different lengths ALL have CRC=0 for CRC8, making it
// unsuitable for situations where a string of zeros is likely to happen.
test(crc8_nibblem, zeros) {
  uint8_t crc1 = crc8_nibblem::crc_calculate(ZEROES, 1);
  uint8_t crc2 = crc8_nibblem::crc_calculate(ZEROES, 2);
  uint8_t crc3 = crc8_nibblem::crc_calculate(ZEROES, 3);
  uint8_t crc4 = crc8_nibblem::crc_calculate(ZEROES, 4);

  assertEqual((uint8_t) 0, crc1);
  assertEqual((uint8_t) 0, crc2);
  assertEqual((uint8_t) 0, crc3);
  assertEqual((uint8_t) 0, crc4);
}

// --------------------------------------------------------------------------
// crc8_byte
// --------------------------------------------------------------------------

// Arrays of zeros of different lengths ALL have CRC=0 for CRC8, making it
// unsuitable for situations where a string of zeros is likely to happen.
test(crc8_byte, zeros) {
  uint8_t crc1 = crc8_byte::crc_calculate(ZEROES, 1);
  uint8_t crc2 = crc8_byte::crc_calculate(ZEROES, 2);
  uint8_t crc3 = crc8_byte::crc_calculate(ZEROES, 3);
  uint8_t crc4 = crc8_byte::crc_calculate(ZEROES, 4);

  assertEqual((uint8_t) 0, crc1);
  assertEqual((uint8_t) 0, crc2);
  assertEqual((uint8_t) 0, crc3);
  assertEqual((uint8_t) 0, crc4);
}

test(crc8_byte, check) {
  uint8_t crc = crc8_byte::crc_calculate(CHECK_STRING, LENGTH);
  assertEqual(EXPECTED_CRC, crc);
}

// --------------------------------------------------------------------------

void setup() {
#if ! defined(EPOXY_DUINO)
  delay(1000); // wait to prevent garbage on SERIAL_PORT_MONITOR
#endif

  SERIAL_PORT_MONITOR.begin(115200);
  while (!SERIAL_PORT_MONITOR); // needed for Leonardo/Micro
#if defined(EPOXY_DUINO)
  SERIAL_PORT_MONITOR.setLineModeUnix();
#endif
}

void loop() {
  TestRunner::run();
}
