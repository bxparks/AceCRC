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
 * Return type of the Lambda test function. This return type does not really
 * matter because we are just going to ignore it. It needs to be identical
 * for all Lambdas because we converting them to function pointers, instead of
 * templatizing the runLambda() function. Select uint16_t as a compromise
 * between 8 bit and 32 bit integers.
 */
typedef uint16_t LambdaReturnType;

/**
 * Convert lambda expressions to function pointer, to avoid templatizing
 * the runLambda() function.
 */
typedef LambdaReturnType (*Lambda)();

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
  SERIAL_PORT_MONITOR.print(name);
  SERIAL_PORT_MONITOR.print(' ');
  SERIAL_PORT_MONITOR.print(STRING_SIZE);
  SERIAL_PORT_MONITOR.print(' ');
  SERIAL_PORT_MONITOR.print(stats.getMin());
  SERIAL_PORT_MONITOR.print(' ');
  SERIAL_PORT_MONITOR.print(stats.getAvg());
  SERIAL_PORT_MONITOR.print(' ');
  SERIAL_PORT_MONITOR.print(stats.getMax());

  uint16_t perKiB = stats.getAvg() / STRING_SIZE_KIB;
  SERIAL_PORT_MONITOR.print(' ');
  SERIAL_PORT_MONITOR.println(perKiB);
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
    LambdaReturnType crc = lambda();
    uint16_t elapsed = micros() - startMicros;
    disableCompilerOptimization = crc;
    stats.update(elapsed);
    yield();
  }
  printStats(name, stats);
}

void runBenchmarks() {
  runLambda("crc8_bit", []() -> LambdaReturnType {
    uint8_t crc = crc8_bit::crc_init();
    crc = crc8_bit::crc_update(crc, string, STRING_SIZE);
    crc = crc8_bit::crc_finalize(crc);
    return crc;
  });

  runLambda("crc8_nibble", []() -> LambdaReturnType {
    uint8_t crc = crc8_nibble::crc_init();
    crc = crc8_nibble::crc_update(crc, string, STRING_SIZE);
    crc = crc8_nibble::crc_finalize(crc);
    return crc;
  });

  runLambda("crc8_byte", []() -> LambdaReturnType {
    uint8_t crc = crc8_byte::crc_init();
    crc = crc8_byte::crc_update(crc, string, STRING_SIZE);
    crc = crc8_byte::crc_finalize(crc);
    return crc;
  });

  runLambda("crc16ccitt_bit", []() -> LambdaReturnType {
    uint16_t crc = crc16ccitt_bit::crc_init();
    crc = crc16ccitt_bit::crc_update(crc, string, STRING_SIZE);
    crc = crc16ccitt_bit::crc_finalize(crc);
    return crc;
  });

  runLambda("crc16ccitt_nibble", []() -> LambdaReturnType {
    uint16_t crc = crc16ccitt_nibble::crc_init();
    crc = crc16ccitt_nibble::crc_update(crc, string, STRING_SIZE);
    crc = crc16ccitt_nibble::crc_finalize(crc);
    return crc;
  });

  runLambda("crc16ccitt_byte", []() -> LambdaReturnType {
    uint16_t crc = crc16ccitt_byte::crc_init();
    crc = crc16ccitt_byte::crc_update(crc, string, STRING_SIZE);
    crc = crc16ccitt_byte::crc_finalize(crc);
    return crc;
  });

  runLambda("crc32_bit", []() -> LambdaReturnType {
    uint16_t crc = crc32_bit::crc_init();
    crc = crc32_bit::crc_update(crc, string, STRING_SIZE);
    crc = crc32_bit::crc_finalize(crc);
    return crc;
  });

  runLambda("crc32_nibble", []() -> LambdaReturnType {
    uint16_t crc = crc32_nibble::crc_init();
    crc = crc32_nibble::crc_update(crc, string, STRING_SIZE);
    crc = crc32_nibble::crc_finalize(crc);
    return crc;
  });

  runLambda("crc32_byte", []() -> LambdaReturnType {
    uint16_t crc = crc32_byte::crc_init();
    crc = crc32_byte::crc_update(crc, string, STRING_SIZE);
    crc = crc32_byte::crc_finalize(crc);
    return crc;
  });

}
