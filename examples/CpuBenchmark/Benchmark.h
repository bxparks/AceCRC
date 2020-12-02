#ifndef CPUB_BENCHMARK_BENCHMARK_H
#define CPUB_BENCHMARK_BENCHMARK_H

// Define the size of the string (in KiB), dependent on the speed of the
// microcontroller
#if defined(ARDUINO_ARCH_AVR)
  const uint16_t STRING_SIZE_KIB = 1;
  const uint16_t NUM_SAMPLES = 20;
#elif defined(ARDUINO_ARCH_SAMD)
  const uint16_t STRING_SIZE_KIB = 2;
  const uint16_t NUM_SAMPLES = 100;
#elif defined(ESP8266)
  const uint16_t STRING_SIZE_KIB = 10;
  const uint16_t NUM_SAMPLES = 100;
#elif defined(ESP32)
  const uint16_t STRING_SIZE_KIB = 10;
  const uint16_t NUM_SAMPLES = 100;
#elif defined(TEENSYDUINO)
  const uint16_t STRING_SIZE_KIB = 10;
  const uint16_t NUM_SAMPLES = 100;
#elif defined(UNIX_HOST_DUINO)
  const uint16_t STRING_SIZE_KIB = 10;
  const uint16_t NUM_SAMPLES = 100;
#else
  #error Unsupported architecture
#endif

static const uint16_t STRING_SIZE = STRING_SIZE_KIB * 1024;

/** String buffer. */
extern char* string;

/** Run all runmarks. */
void runBenchmarks();

#endif
