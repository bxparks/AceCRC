#include <Arduino.h>
#include <AceCRC.h>
#include <AceCommon.h>

using namespace ace_crc;
using namespace ace_common;

// Define the size of the string (in KiB), dependent on the speed of the
// microcontroller
#if defined(ARDUINO_ARCH_AVR)
  const uint16_t STRING_SIZE_KIB = 1;
#elif defined(ARDUINO_ARCH_SAMD)
  const uint16_t STRING_SIZE_KIB = 2;
#elif defined(ESP8266)
  const uint16_t STRING_SIZE_KIB = 10;
#elif defined(ESP32)
  const uint16_t STRING_SIZE_KIB = 10;
#elif defined(TEENSYDUINO)
  const uint16_t STRING_SIZE_KIB = 10;
#elif defined(UNIX_HOST_DUINO)
  const uint16_t STRING_SIZE_KIB = 10;
#else
  #error Unsupported architecture
#endif
const uint16_t STRING_SIZE = STRING_SIZE_KIB * 1024;
char* string;

// The number of samples.
const uint16_t NUM_SAMPLES = 100;

// Volatile to prevent the compiler from deciding that the entire program does
// nothing, causing it to opimize the whole program to nothing.
volatile uint8_t disableCompilerOptimization;

/** Fill the string buffer with some pseudo random printable characters. */
void setupString() {
  for (uint16_t i = 0; i < STRING_SIZE; i++) {
    string[i] = random(32, 128); // printable ASCII
  }
  string[STRING_SIZE] = '\0'; // In case we want to examine the string
}

/** Print the result for each CRC algorithm. */
void printStats(const char* name, TimingStats& stats) {
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
 * Convert lambda expressions to function pointer, to avoid templatizing
 * the runLambda() function.
 */
typedef uint16_t (*Lambda)();

/**
 * Run the given lambda function for 'count' many times, recording the elapsed
 * microseconds for each iteration. Then print the TimingStats (min, avg, max).
 */
void runLambda(const char* name, Lambda lambda) {
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

// -----------------------------------------------------------------------------

void setup() {
#ifndef UNIX_HOST_DUINO
  delay(1000);
#endif
  Serial.begin(115200);
  while (! Serial); // wait for Serial on Leonardo/Pro Micro

  // Allocate string buffer
  string = new char[STRING_SIZE];

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

  Serial.println("END");
#ifdef UNIX_HOST_DUINO
  exit(0);
#endif
}

void loop() {
}
