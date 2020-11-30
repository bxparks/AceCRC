#line 2 "Crc16CcittTest.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AceCRC.h>

using aunit::TestRunner;
using namespace ace_crc;

static const char CHECK_STRING[] = "123456789";
static const size_t LENGTH = sizeof(CHECK_STRING) - 1;
static uint16_t EXPECTED_CRC = 0xe5cc;

// --------------------------------------------------------------------------
// crc16ccitt
// --------------------------------------------------------------------------

test(crc16ccitt_bit, check) {
  uint16_t crc = crc16ccitt_bit::crc_init();
  crc = crc16ccitt_bit::crc_update(crc, CHECK_STRING, LENGTH);
  crc = crc16ccitt_bit::crc_finalize(crc);
  assertEqual(EXPECTED_CRC, crc);
}

test(crc16ccitt_nibble, check) {
  uint16_t crc = crc16ccitt_nibble::crc_init();
  crc = crc16ccitt_nibble::crc_update(crc, CHECK_STRING, LENGTH);
  crc = crc16ccitt_nibble::crc_finalize(crc);
  assertEqual(EXPECTED_CRC, crc);
}

test(crc16ccitt_byte, check) {
  uint16_t crc = crc16ccitt_byte::crc_init();
  crc = crc16ccitt_byte::crc_update(crc, CHECK_STRING, LENGTH);
  crc = crc16ccitt_byte::crc_finalize(crc);
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
