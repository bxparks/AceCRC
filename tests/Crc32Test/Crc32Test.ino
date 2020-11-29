#line 2 "Crc32Test.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AceCRC.h>

using aunit::TestRunner;
using namespace ace_crc::crc32;

static const char CHECK_STRING[] = "123456789";
static const size_t LENGTH = sizeof(CHECK_STRING) - 1;
static uint32_t EXPECTED_CRC = 0xcbf43926;

// --------------------------------------------------------------------------
// crc32
// --------------------------------------------------------------------------

test(crc32, bit) {
  uint32_t crc = bit::crc_init();
  crc = bit::crc_update(crc, CHECK_STRING, LENGTH);
  crc = bit::crc_finalize(crc);
  assertEqual(EXPECTED_CRC, crc);
}

test(crc32, nibble) {
  uint32_t crc = nibble::crc_init();
  crc = nibble::crc_update(crc, CHECK_STRING, LENGTH);
  crc = nibble::crc_finalize(crc);
  assertEqual(EXPECTED_CRC, crc);
}

test(crc32, byte) {
  uint32_t crc = byte::crc_init();
  crc = byte::crc_update(crc, CHECK_STRING, LENGTH);
  crc = byte::crc_finalize(crc);
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
