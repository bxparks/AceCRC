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
// 3 - crc8_byte
// 4 - crc16ccitt_bit
// 5 - crc16ccitt_nibble
// 6 - crc16ccitt_byte
// 7 - crc32_bit
// 8 - crc32_nibble
// 9 - crc32_byte
#define FEATURE 0

// A volatile integer to prevent the compiler from optimizing away the entire
// program.
volatile int disableCompilerOptimization = 0;

#if FEATURE != 0
  #include <AceCRC.h>
#endif

#if FEATURE == 0
  // nothing
#elif FEATURE == 1
  using namespace ace_crc::crc8_bit;
#elif FEATURE == 2
  using namespace ace_crc::crc8_nibble;
#elif FEATURE == 3
  using namespace ace_crc::crc8_byte;
#elif FEATURE == 4
  using namespace ace_crc::crc16ccitt_bit;
#elif FEATURE == 5
  using namespace ace_crc::crc16ccitt_nibble;
#elif FEATURE == 6
  using namespace ace_crc::crc16ccitt_byte;
#elif FEATURE == 7
  using namespace ace_crc::crc32_bit;
#elif FEATURE == 8
  using namespace ace_crc::crc32_nibble;
#elif FEATURE == 9
  using namespace ace_crc::crc32_byte;
#else
  #error Unknown FEATURE
#endif

static const char CHECK_STRING[] = "123456789";
static const size_t LENGTH = sizeof(CHECK_STRING) - 1; // ignore NUL char

void calculateCRC() {
  // Do some random work on disableCompilerOptimization so that the compiler
  // does not optimize away everything.
  if (disableCompilerOptimization > 9) disableCompilerOptimization = 0;
  int index = CHECK_STRING[disableCompilerOptimization] - '1';
  disableCompilerOptimization = CHECK_STRING[index];

#if FEATURE != 0
  crc_t crc = crc_calculate(CHECK_STRING, LENGTH);
  disableCompilerOptimization = crc;
#endif
}

void setup() {
  delay(2000); // wait for stability on some boards
}

void loop() {
  calculateCRC();
}
