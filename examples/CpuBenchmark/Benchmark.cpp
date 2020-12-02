/*
 * These benchmarks must be in .h and .cpp files instead of a *.ino file,
 * because the Arduino builder seems to mess up the ordering of typedefs and
 * lambda expressions.
 */

#include <AceCRC.h>
#include <AceCommon.h> // TimingStats
#include <stdint.h>
#include <Arduino.h>
#include "Benchmark.h"

using namespace ace_crc;
using namespace ace_common;

char* string;

/**
 * Convert lambda expressions to function pointer, to avoid templatizing
 * the runLambda() function.
 */
typedef uint16_t (*Lambda)();

// Volatile to prevent the compiler from deciding that the entire program does
// nothing, causing it to opimize the whole program to nothing.
volatile uint8_t disableCompilerOptimization;

/** Fill the string buffer with some pseudo random printable characters. */
static void setupString() {
  for (uint16_t i = 0; i < STRING_SIZE; i++) {
    string[i] = random(32, 128); // printable ASCII
  }
  string[STRING_SIZE] = '\0'; // In case we want to examine the string
}

/** Print the result for each CRC algorithm. */
static void printStats(const char* name, TimingStats& stats) {
  Serial.print(name);
  Serial.print(' ');
  Serial.print(STRING_SIZE);
  Serial.print(' ');
  Serial.print(stats.getMin());
  Serial.print(' ');
  Serial.print(stats.getAvg());
  Serial.print(' ');
  Serial.print(stats.getMax());

  uint16_t perKiB = stats.getAvg() / STRING_SIZE_KIB;
  Serial.print(' ');
  Serial.println(perKiB);
}

/**
 * Run the given lambda function for 'count' many times, recording the elapsed
 * microseconds for each iteration. Then print the TimingStats (min, avg, max).
 */
static void runLambda(const char* name, Lambda lambda) {
  TimingStats stats;
  uint16_t count = NUM_SAMPLES;

  while (count--) {
    // Use a different string each iteration, to prevent the compiler from
    // optimizing out this loop into a single iteration.
    setupString();
    yield();

    uint16_t startMicros = micros();
    uint16_t crc = lambda();
    uint16_t elapsed = micros() - startMicros;
    disableCompilerOptimization = crc;
    stats.update(elapsed);
    yield();
  }
  printStats(name, stats);
}

void runBenchmarks() {
  runLambda("crc16ccitt_bit", []() -> uint16_t {
    uint16_t crc = crc16ccitt_bit::crc_init();
    crc = crc16ccitt_bit::crc_update(crc, string, STRING_SIZE);
    crc = crc16ccitt_bit::crc_finalize(crc);
    return crc;
  });

  runLambda("crc16ccitt_nibble", []() -> uint16_t {
    uint16_t crc = crc16ccitt_nibble::crc_init();
    crc = crc16ccitt_nibble::crc_update(crc, string, STRING_SIZE);
    crc = crc16ccitt_nibble::crc_finalize(crc);
    return crc;
  });

  runLambda("crc16ccitt_byte", []() -> uint16_t {
    uint16_t crc = crc16ccitt_byte::crc_init();
    crc = crc16ccitt_byte::crc_update(crc, string, STRING_SIZE);
    crc = crc16ccitt_byte::crc_finalize(crc);
    return crc;
  });

  runLambda("crc32_bit", []() -> uint16_t {
    uint16_t crc = crc32_bit::crc_init();
    crc = crc32_bit::crc_update(crc, string, STRING_SIZE);
    crc = crc32_bit::crc_finalize(crc);
    return crc;
  });

  runLambda("crc32_nibble", []() -> uint16_t {
    uint16_t crc = crc32_nibble::crc_init();
    crc = crc32_nibble::crc_update(crc, string, STRING_SIZE);
    crc = crc32_nibble::crc_finalize(crc);
    return crc;
  });

  runLambda("crc32_byte", []() -> uint16_t {
    uint16_t crc = crc32_byte::crc_init();
    crc = crc32_byte::crc_update(crc, string, STRING_SIZE);
    crc = crc32_byte::crc_finalize(crc);
    return crc;
  });

}
