#line 2 "Crc32Test.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AceCRC.h>

using aunit::TestRunner;
using namespace ace_crc;

static const char CHECK_STRING[] = "123456789";
static const size_t LENGTH = sizeof(CHECK_STRING) - 1;
static uint32_t EXPECTED_CRC = 0xcbf43926;

// --------------------------------------------------------------------------
// crc32
// --------------------------------------------------------------------------

test(crc32_bit, check) {
  uint32_t crc = crc32_bit::crc_init();
  crc = crc32_bit::crc_update(crc, CHECK_STRING, LENGTH);
  crc = crc32_bit::crc_finalize(crc);
  assertEqual(EXPECTED_CRC, crc);
}

test(crc32_nibble, check) {
  uint32_t crc = crc32_nibble::crc_init();
  crc = crc32_nibble::crc_update(crc, CHECK_STRING, LENGTH);
  crc = crc32_nibble::crc_finalize(crc);
  assertEqual(EXPECTED_CRC, crc);
}

test(crc32_byte, check) {
  uint32_t crc = crc32_byte::crc_init();
  crc = crc32_byte::crc_update(crc, CHECK_STRING, LENGTH);
  crc = crc32_byte::crc_finalize(crc);
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
