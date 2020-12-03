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

uint16_t calcCrc16CcittBit(const char* data, size_t size) {
  uint16_t crc = crc16ccitt_bit::crc_init();
  crc = crc16ccitt_bit::crc_update(crc, data, size);
  return crc16ccitt_bit::crc_finalize(crc);
}

test(crc16ccitt_bit, check) {
  uint16_t crc = calcCrc16CcittBit(CHECK_STRING, LENGTH);
  assertEqual(EXPECTED_CRC, crc);
}

// Verify that arrays of zeros of different length have different CRCs
test(crc16ccitt_bit, zeros) {
  uint16_t crc1 = calcCrc16CcittBit(ZEROES, 1);
  uint16_t crc2 = calcCrc16CcittBit(ZEROES, 2);
  uint16_t crc3 = calcCrc16CcittBit(ZEROES, 3);
  uint16_t crc4 = calcCrc16CcittBit(ZEROES, 4);

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

uint16_t calcCrc16CcittNibble(const char* data, size_t size) {
  uint16_t crc = crc16ccitt_nibble::crc_init();
  crc = crc16ccitt_nibble::crc_update(crc, data, size);
  return crc16ccitt_nibble::crc_finalize(crc);
}

// Verify that arrays of zeros of different length have different CRCs
test(crc16ccitt_nibble, zeros) {
  uint16_t crc1 = calcCrc16CcittNibble(ZEROES, 1);
  uint16_t crc2 = calcCrc16CcittNibble(ZEROES, 2);
  uint16_t crc3 = calcCrc16CcittNibble(ZEROES, 3);
  uint16_t crc4 = calcCrc16CcittNibble(ZEROES, 4);

  assertNotEqual(crc1, crc2);
  assertNotEqual(crc1, crc3);
  assertNotEqual(crc1, crc4);
  assertNotEqual(crc2, crc3);
  assertNotEqual(crc2, crc4);
  assertNotEqual(crc3, crc4);
}

test(crc16ccitt_nibble, check) {
  uint16_t crc = calcCrc16CcittNibble(CHECK_STRING, LENGTH);
  assertEqual(EXPECTED_CRC, crc);
}

// --------------------------------------------------------------------------
// crc16ccitt_byte
// --------------------------------------------------------------------------

uint16_t calcCrc16CcittByte(const char* data, size_t size) {
  uint16_t crc = crc16ccitt_byte::crc_init();
  crc = crc16ccitt_byte::crc_update(crc, data, size);
  return crc16ccitt_byte::crc_finalize(crc);
}

// Verify that arrays of zeros of different length have different CRCs
test(crc16ccitt_byte, zeros) {
  uint16_t crc1 = calcCrc16CcittByte(ZEROES, 1);
  uint16_t crc2 = calcCrc16CcittByte(ZEROES, 2);
  uint16_t crc3 = calcCrc16CcittByte(ZEROES, 3);
  uint16_t crc4 = calcCrc16CcittByte(ZEROES, 4);

  assertNotEqual(crc1, crc2);
  assertNotEqual(crc1, crc3);
  assertNotEqual(crc1, crc4);
  assertNotEqual(crc2, crc3);
  assertNotEqual(crc2, crc4);
  assertNotEqual(crc3, crc4);
}

test(crc16ccitt_byte, check) {
  uint16_t crc = calcCrc16CcittBit(CHECK_STRING, LENGTH);
  assertEqual(EXPECTED_CRC, crc);
}

// --------------------------------------------------------------------------

void setup() {
#if ! defined(UNIX_HOST_DUINO)
  delay(1000); // wait to prevent garbage on SERIAL_PORT_MONITOR
#endif

  SERIAL_PORT_MONITOR.begin(115200);
  while(!SERIAL_PORT_MONITOR); // needed for Leonardo/Micro
}

void loop() {
  TestRunner::run();
}
