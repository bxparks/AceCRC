#ifndef CPUB_BENCHMARK_BENCHMARK_H
#define CPUB_BENCHMARK_BENCHMARK_H

// Mostly for ESP32 which does not define SERIAL_PORT_MONITOR
#ifndef SERIAL_PORT_MONITOR
  //#warning SERIAL_PORT_MONITOR not defined, assuming 'Serial'
  #define SERIAL_PORT_MONITOR Serial
#endif

// Define the size of the string (in units of one page, 256 bytes), dependent
// on the speed of the microcontroller. We use PAGE size because
// <Arduino_CRC32.h> places its 1kB lookup table into RAM, so we can only
// afford to allocate 1 or 2 pages (256 or 512 bytes) for the sample 'string'.
#if defined(ARDUINO_ARCH_AVR)
  const uint16_t STRING_SIZE_PAGE = 2;  // we can only afford a 512 string
  const uint16_t NUM_SAMPLES = 10;
#elif defined(ARDUINO_ARCH_SAMD)
  const uint16_t STRING_SIZE_PAGE = 4;
  const uint16_t NUM_SAMPLES = 20;
#elif defined(ESP8266)
  const uint16_t STRING_SIZE_PAGE = 4;
  const uint16_t NUM_SAMPLES = 20;
#elif defined(ESP32)
  const uint16_t STRING_SIZE_PAGE = 4;
  const uint16_t NUM_SAMPLES = 20;
#elif defined(TEENSYDUINO)
  const uint16_t STRING_SIZE_PAGE = 4;
  const uint16_t NUM_SAMPLES = 20;
#elif defined(UNIX_HOST_DUINO)
  const uint16_t STRING_SIZE_PAGE = 40;
  const uint16_t NUM_SAMPLES = 100;
#else
  #error Unsupported architecture
#endif

// Allocate a string of STRING_SIZE_PAGE pages.
static const uint16_t STRING_SIZE = STRING_SIZE_PAGE * 256;

/** String buffer. */
extern char* string;

/** Run all runmarks. */
void runBenchmarks();

#endif
