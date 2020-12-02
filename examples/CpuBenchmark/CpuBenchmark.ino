#include <Arduino.h>
#include <AceCRC.h>
#include <AceCommon.h>

using namespace ace_crc;
using namespace ace_common;

const int NUM_SAMPLES = 100;
const uint16_t SIZE = 1024;
char string[SIZE];

volatile uint8_t disableCompilerOptimization;

void setupString() {
  for (uint16_t i = 0; i < SIZE; i++) {
    string[i] = random(256);
  }
}

void printStats(const char* name, TimingStats& stats) {
  Serial.print(name);
  Serial.print(' ');
  Serial.print(stats.getMin());
  Serial.print(' ');
  Serial.print(stats.getAvg());
  Serial.print(' ');
  Serial.println(stats.getMax());
}

/**
 * Run the given lambda function for 'count' many times, recording the elapsed
 * microseconds for each iteration. Then print the TimingStats (min, avg, max).
 */
template <typename F>
void runLambda(const char* name, uint16_t count, F&& lambda) {
  TimingStats stats;
  while (count--) {
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

void setup() {
#ifndef UNIX_HOST_DUINO
  delay(1000);
#endif
  Serial.begin(115200);
  while (! Serial); // wait for Serial on Leonardo/Pro Micro

  runLambda("crc16ccitt_bit", NUM_SAMPLES, []() -> uint16_t {
    uint16_t crc = crc16ccitt_bit::crc_init();
    crc = crc16ccitt_bit::crc_update(crc, string, SIZE);
    crc = crc16ccitt_bit::crc_finalize(crc);
    return crc;
  });

  runLambda("crc16ccitt_nibble", NUM_SAMPLES, []() -> uint16_t {
    uint16_t crc = crc16ccitt_nibble::crc_init();
    crc = crc16ccitt_nibble::crc_update(crc, string, SIZE);
    crc = crc16ccitt_nibble::crc_finalize(crc);
    return crc;
  });

  runLambda("crc16ccitt_byte", NUM_SAMPLES, []() -> uint16_t {
    uint16_t crc = crc16ccitt_byte::crc_init();
    crc = crc16ccitt_byte::crc_update(crc, string, SIZE);
    crc = crc16ccitt_byte::crc_finalize(crc);
    return crc;
  });

  Serial.println("END");
#ifdef UNIX_HOST_DUINO
  exit(0);
#endif
}

void loop() {
}
