/*
 * A program which compiles in different CRC algorithms and variants to
 * determine the flash and static memory sizes from the output of the compiler.
 * Set the FEATURE macro to various integer to compile different algorithms.
 */

#include <Arduino.h>

// Set this to [0..n] to extract the flash and static memory usage.
// 0 - baseline
// 1 - crc8_bit
// 2 - crc8_nibble
// 3 - crc8_nibblem
// 4 - crc8_byte
// 5 - crc16ccitt_bit
// 6 - crc16ccitt_nibble
// 7 - crc16ccitt_nibblem
// 8 - crc16ccitt_byte
// 9 - crc32_bit
// 10 - crc32_nibble
// 11 - crc32_nibblem
// 12 - crc32_byte
// 13 - CRC32 library
// 14 - Arduino_CRC32 library
// 15 - FastCRC library
#define FEATURE 0

// A volatile integer to prevent the compiler from optimizing away the entire
// program.
volatile int disableCompilerOptimization = 0;

#if FEATURE == 0
  // nothing
#elif FEATURE == 1
  #include <AceCRC.h>
  using namespace ace_crc::crc8_bit;
#elif FEATURE == 2
  #include <AceCRC.h>
  using namespace ace_crc::crc8_nibble;
#elif FEATURE == 3
  #include <AceCRC.h>
  using namespace ace_crc::crc8_nibblem;
#elif FEATURE == 4
  #include <AceCRC.h>
  using namespace ace_crc::crc8_byte;
#elif FEATURE == 5
  #include <AceCRC.h>
  using namespace ace_crc::crc16ccitt_bit;
#elif FEATURE == 6
  #include <AceCRC.h>
  using namespace ace_crc::crc16ccitt_nibble;
#elif FEATURE == 7
  #include <AceCRC.h>
  using namespace ace_crc::crc16ccitt_nibblem;
#elif FEATURE == 8
  #include <AceCRC.h>
  using namespace ace_crc::crc16ccitt_byte;
#elif FEATURE == 9
  #include <AceCRC.h>
  using namespace ace_crc::crc32_bit;
#elif FEATURE == 10
  #include <AceCRC.h>
  using namespace ace_crc::crc32_nibble;
#elif FEATURE == 11
  #include <AceCRC.h>
  using namespace ace_crc::crc32_nibblem;
#elif FEATURE == 12
  #include <AceCRC.h>
  using namespace ace_crc::crc32_byte;
#elif FEATURE == 13
  #include <CRC32.h>
#elif FEATURE == 14
  #include <Arduino_CRC32.h>
#elif FEATURE == 15
  #include <FastCRC.h>
#else
  #error Unknown FEATURE
#endif

static const char CHECK_STRING[] = "123456789";
static const size_t LENGTH = sizeof(CHECK_STRING) - 1; // ignore NUL char

void calculateCRC() {
  // Do some random work on disableCompilerOptimization so that the compiler
  // does not optimize away everything.
  if (disableCompilerOptimization >= 9) disableCompilerOptimization = 0;
  int index = CHECK_STRING[disableCompilerOptimization] - '1';
  disableCompilerOptimization = CHECK_STRING[index];

#if FEATURE >=1 && FEATURE <= 12
  crc_t crc = crc_calculate(CHECK_STRING, LENGTH);
  disableCompilerOptimization = crc;
#elif FEATURE == 13
  uint32_t crc = CRC32::calculate(CHECK_STRING, LENGTH);
  disableCompilerOptimization = crc;
#elif FEATURE == 14
  uint32_t crc = Arduino_CRC32().calc((const uint8_t*) CHECK_STRING, LENGTH);
  disableCompilerOptimization = crc;
#elif FEATURE == 15
  uint32_t crc = FastCRC32().crc32((const uint8_t*) CHECK_STRING, LENGTH);
  disableCompilerOptimization = crc;
#endif
}

void setup() {
  delay(2000); // wait for stability on some boards
}

void loop() {
  calculateCRC();
}
