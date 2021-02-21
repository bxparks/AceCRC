#line 2 "Crc16CcittTest.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AceCRC.h>

using aunit::TestRunner;
using namespace ace_crc;

static const char CHECK_STRING[] = "123456789";
static const size_t LENGTH = sizeof(CHECK_STRING) - 1;
static uint16_t EXPECTED_CRC = 0xe5cc;

static const size_t ZEROS_LENGTH = 4;
static char ZEROES[ZEROS_LENGTH] = {0, 0, 0, 0};

// --------------------------------------------------------------------------
// crc16ccitt_bit
// --------------------------------------------------------------------------

test(crc16ccitt_bit, check) {
  uint16_t crc = crc16ccitt_bit::crc_calculate(CHECK_STRING, LENGTH);
  assertEqual(EXPECTED_CRC, crc);
}

// Verify that arrays of zeros of different length have different CRCs
test(crc16ccitt_bit, zeros) {
  uint16_t crc1 = crc16ccitt_bit::crc_calculate(ZEROES, 1);
  uint16_t crc2 = crc16ccitt_bit::crc_calculate(ZEROES, 2);
  uint16_t crc3 = crc16ccitt_bit::crc_calculate(ZEROES, 3);
  uint16_t crc4 = crc16ccitt_bit::crc_calculate(ZEROES, 4);

  assertNotEqual(crc1, crc2);
  assertNotEqual(crc1, crc3);
  assertNotEqual(crc1, crc4);
  assertNotEqual(crc2, crc3);
  assertNotEqual(crc2, crc4);
  assertNotEqual(crc3, crc4);
}

// --------------------------------------------------------------------------
// crc16ccitt_nibble
// --------------------------------------------------------------------------

// Verify that arrays of zeros of different length have different CRCs
test(crc16ccitt_nibble, zeros) {
  uint16_t crc1 = crc16ccitt_nibble::crc_calculate(ZEROES, 1);
  uint16_t crc2 = crc16ccitt_nibble::crc_calculate(ZEROES, 2);
  uint16_t crc3 = crc16ccitt_nibble::crc_calculate(ZEROES, 3);
  uint16_t crc4 = crc16ccitt_nibble::crc_calculate(ZEROES, 4);

  assertNotEqual(crc1, crc2);
  assertNotEqual(crc1, crc3);
  assertNotEqual(crc1, crc4);
  assertNotEqual(crc2, crc3);
  assertNotEqual(crc2, crc4);
  assertNotEqual(crc3, crc4);
}

test(crc16ccitt_nibble, check) {
  uint16_t crc = crc16ccitt_nibble::crc_calculate(CHECK_STRING, LENGTH);
  assertEqual(EXPECTED_CRC, crc);
}

// --------------------------------------------------------------------------
// crc16ccitt_nibblem
// --------------------------------------------------------------------------

// Verify that arrays of zeros of different length have different CRCs
test(crc16ccitt_nibblem, zeros) {
  uint16_t crc1 = crc16ccitt_nibblem::crc_calculate(ZEROES, 1);
  uint16_t crc2 = crc16ccitt_nibblem::crc_calculate(ZEROES, 2);
  uint16_t crc3 = crc16ccitt_nibblem::crc_calculate(ZEROES, 3);
  uint16_t crc4 = crc16ccitt_nibblem::crc_calculate(ZEROES, 4);

  assertNotEqual(crc1, crc2);
  assertNotEqual(crc1, crc3);
  assertNotEqual(crc1, crc4);
  assertNotEqual(crc2, crc3);
  assertNotEqual(crc2, crc4);
  assertNotEqual(crc3, crc4);
}

test(crc16ccitt_nibblem, check) {
  uint16_t crc = crc16ccitt_nibblem::crc_calculate(CHECK_STRING, LENGTH);
  assertEqual(EXPECTED_CRC, crc);
}

// --------------------------------------------------------------------------
// crc16ccitt_byte
// --------------------------------------------------------------------------

// Verify that arrays of zeros of different length have different CRCs
test(crc16ccitt_byte, zeros) {
  uint16_t crc1 = crc16ccitt_byte::crc_calculate(ZEROES, 1);
  uint16_t crc2 = crc16ccitt_byte::crc_calculate(ZEROES, 2);
  uint16_t crc3 = crc16ccitt_byte::crc_calculate(ZEROES, 3);
  uint16_t crc4 = crc16ccitt_byte::crc_calculate(ZEROES, 4);

  assertNotEqual(crc1, crc2);
  assertNotEqual(crc1, crc3);
  assertNotEqual(crc1, crc4);
  assertNotEqual(crc2, crc3);
  assertNotEqual(crc2, crc4);
  assertNotEqual(crc3, crc4);
}

test(crc16ccitt_byte, check) {
  uint16_t crc = crc16ccitt_byte::crc_calculate(CHECK_STRING, LENGTH);
  assertEqual(EXPECTED_CRC, crc);
}

// --------------------------------------------------------------------------

void setup() {
#if ! defined(EPOXY_DUINO)
  delay(1000); // wait to prevent garbage on SERIAL_PORT_MONITOR
#endif

  SERIAL_PORT_MONITOR.begin(115200);
  while (!SERIAL_PORT_MONITOR); // needed for Leonardo/Micro
}

void loop() {
  TestRunner::run();
}
