#line 2 "Crc32Test.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AceCRC.h>

using aunit::TestRunner;
using namespace ace_crc;

static const char CHECK_STRING[] = "123456789";
static const size_t LENGTH = sizeof(CHECK_STRING) - 1;
static uint32_t EXPECTED_CRC = 0xcbf43926;

static const size_t ZEROS_LENGTH = 4;
static char ZEROES[ZEROS_LENGTH] = {0, 0, 0, 0};

// --------------------------------------------------------------------------
// crc32_bit
// --------------------------------------------------------------------------

uint32_t calcCrc32Bit(const char* data, size_t size) {
  uint32_t crc = crc32_bit::crc_init();
  crc = crc32_bit::crc_update(crc, data, size);
  return crc32_bit::crc_finalize(crc);
}

test(crc32_bit, check) {
  uint32_t crc = calcCrc32Bit(CHECK_STRING, LENGTH);
  assertEqual(EXPECTED_CRC, crc);
}

// Verify that arrays of zeros of different length have different CRCs
test(crc32_bit, zeros) {
  uint32_t crc1 = calcCrc32Bit(ZEROES, 1);
  uint32_t crc2 = calcCrc32Bit(ZEROES, 2);
  uint32_t crc3 = calcCrc32Bit(ZEROES, 3);
  uint32_t crc4 = calcCrc32Bit(ZEROES, 4);

  assertNotEqual(crc1, crc2);
  assertNotEqual(crc1, crc3);
  assertNotEqual(crc1, crc4);
  assertNotEqual(crc2, crc3);
  assertNotEqual(crc2, crc4);
  assertNotEqual(crc3, crc4);
}

// --------------------------------------------------------------------------
// crc32_nibble
// --------------------------------------------------------------------------

uint32_t calcCrc32Nibble(const char* data, size_t size) {
  uint32_t crc = crc32_nibble::crc_init();
  crc = crc32_nibble::crc_update(crc, data, size);
  return crc32_nibble::crc_finalize(crc);
}

test(crc32_nibble, check) {
  uint32_t crc = calcCrc32Nibble(CHECK_STRING, LENGTH);
  assertEqual(EXPECTED_CRC, crc);
}

// Verify that arrays of zeros of different length have different CRCs
test(crc32_nibble, zeros) {
  uint32_t crc1 = calcCrc32Nibble(ZEROES, 1);
  uint32_t crc2 = calcCrc32Nibble(ZEROES, 2);
  uint32_t crc3 = calcCrc32Nibble(ZEROES, 3);
  uint32_t crc4 = calcCrc32Nibble(ZEROES, 4);

  assertNotEqual(crc1, crc2);
  assertNotEqual(crc1, crc3);
  assertNotEqual(crc1, crc4);
  assertNotEqual(crc2, crc3);
  assertNotEqual(crc2, crc4);
  assertNotEqual(crc3, crc4);
}

// --------------------------------------------------------------------------
// crc32_byte
// --------------------------------------------------------------------------

uint32_t calcCrc32Byte(const char* data, size_t size) {
  uint32_t crc = crc32_byte::crc_init();
  crc = crc32_byte::crc_update(crc, data, size);
  return crc32_byte::crc_finalize(crc);
}

// Verify that arrays of zeros of different length have different CRCs
test(crc32_byte, zeros) {
  uint32_t crc1 = calcCrc32Byte(ZEROES, 1);
  uint32_t crc2 = calcCrc32Byte(ZEROES, 2);
  uint32_t crc3 = calcCrc32Byte(ZEROES, 3);
  uint32_t crc4 = calcCrc32Byte(ZEROES, 4);

  assertNotEqual(crc1, crc2);
  assertNotEqual(crc1, crc3);
  assertNotEqual(crc1, crc4);
  assertNotEqual(crc2, crc3);
  assertNotEqual(crc2, crc4);
  assertNotEqual(crc3, crc4);
}

test(crc32_byte, check) {
  uint32_t crc = calcCrc32Byte(CHECK_STRING, LENGTH);
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
