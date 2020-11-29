#line 2 "Crc16CcittTest.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AceCRC.h>

using aunit::TestRunner;
using namespace ace_crc::crc16ccitt;

static const char CHECK_STRING[] = "123456789";
static const size_t LENGTH = sizeof(CHECK_STRING) - 1;
static uint16_t EXPECTED_CRC = 0xe5cc;

// --------------------------------------------------------------------------
// crc16ccitt
// --------------------------------------------------------------------------

test(crc16ccitt, bit) {
  uint16_t crc = bit::crc_init();
  crc = bit::crc_update(crc, CHECK_STRING, LENGTH);
  crc = bit::crc_finalize(crc);
  assertEqual(EXPECTED_CRC, crc);
}

test(crc16ccitt, nibble) {
  uint16_t crc = nibble::crc_init();
  crc = nibble::crc_update(crc, CHECK_STRING, LENGTH);
  crc = nibble::crc_finalize(crc);
  assertEqual(EXPECTED_CRC, crc);
}

test(crc16ccitt, byte) {
  uint16_t crc = byte::crc_init();
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
