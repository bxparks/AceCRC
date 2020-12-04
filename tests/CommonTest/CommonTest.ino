#line 2 "CommonTest.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AceCRC.h>

using aunit::TestRunner;
using namespace ace_crc;

// --------------------------------------------------------------------------
// Verify that the sizeof(crc_t) is as expected. pycrc generates C99 code that
// defines crc_t as a typedef to uint_fast16_t or uint_fast32_t, which are
// supposed to be "the fastest native integer at least as large as uint16_t or
// uint32_t". That seems to mean that on 32-bit processors, both of those are
// 32 bits. And On 64-bit linux machines, that means a 64-bit int type.
//
// But examples/benchmarks/CpuBenchmark tests show that the speed difference is
// not large, and in fact, some of the algorithms actually run *slower* when
// using the "fast" version of the uint types. So in v0.3, I changed the
// `crc_t` type to use the explicit uint16_t and uint32_t types. This uint test
// verifies that change.
// --------------------------------------------------------------------------

static size_t CRC16_CRC_T_SIZE = 2;
static size_t CRC32_CRC_T_SIZE = 4;

test(CommonTest, sizeof) {
  assertEqual(sizeof(crc16ccitt_bit::crc_t), CRC16_CRC_T_SIZE);
  assertEqual(sizeof(crc16ccitt_nibble::crc_t), CRC16_CRC_T_SIZE);
  assertEqual(sizeof(crc16ccitt_byte::crc_t), CRC16_CRC_T_SIZE);

  assertEqual(sizeof(crc32_bit::crc_t), CRC32_CRC_T_SIZE);
  assertEqual(sizeof(crc32_nibble::crc_t), CRC32_CRC_T_SIZE);
  assertEqual(sizeof(crc32_byte::crc_t), CRC32_CRC_T_SIZE);
}

// --------------------------------------------------------------------------

void setup() {
#if ! defined(UNIX_HOST_DUINO)
  delay(1000); // wait to prevent garbage on SERIAL_PORT_MONITOR
#endif

  SERIAL_PORT_MONITOR.begin(115200);
  while (!SERIAL_PORT_MONITOR); // needed for Leonardo/Micro
}

void loop() {
  TestRunner::run();
}
