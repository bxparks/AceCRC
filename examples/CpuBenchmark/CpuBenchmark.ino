#include <Arduino.h>
#include "Benchmark.h"

void setup() {
#ifndef UNIX_HOST_DUINO
  delay(1000);
#endif
  Serial.begin(115200);
  while (! Serial); // wait for Serial on Leonardo/Pro Micro

  // Allocate string buffer
  string = new char[STRING_SIZE];

  // Run all benchmarks.
  runBenchmarks();

  Serial.println("END");
#ifdef UNIX_HOST_DUINO
  exit(0);
#endif
}

void loop() {
}
