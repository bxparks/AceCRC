#ifndef CPUB_BENCHMARK_BENCHMARK_H
#define CPUB_BENCHMARK_BENCHMARK_H

// Mostly for ESP32 which does not define SERIAL_PORT_MONITOR
#ifndef SERIAL_PORT_MONITOR
  //#warning SERIAL_PORT_MONITOR not defined, assuming 'Serial'
  #define SERIAL_PORT_MONITOR Serial
#endif

// Define the size of the string (in KiB), dependent on the speed of the
// microcontroller
#if defined(ARDUINO_ARCH_AVR)
  const uint16_t STRING_SIZE_KIB = 1;
  const uint16_t NUM_SAMPLES = 10;
#elif defined(ARDUINO_ARCH_SAMD)
  const uint16_t STRING_SIZE_KIB = 1;
  const uint16_t NUM_SAMPLES = 20;
#elif defined(ESP8266)
  const uint16_t STRING_SIZE_KIB = 1;
  const uint16_t NUM_SAMPLES = 20;
#elif defined(ESP32)
  const uint16_t STRING_SIZE_KIB = 1;
  const uint16_t NUM_SAMPLES = 20;
#elif defined(TEENSYDUINO)
  const uint16_t STRING_SIZE_KIB = 1;
  const uint16_t NUM_SAMPLES = 20;
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
