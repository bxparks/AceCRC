#include <Arduino.h>
#include "Benchmark.h"

void setup() {
#ifndef EPOXY_DUINO
  delay(2000);
#endif
  SERIAL_PORT_MONITOR.begin(115200);
  while (! SERIAL_PORT_MONITOR); // wait for Serial on Leonardo/Pro Micro
#ifdef EPOXY_DUINO
  SERIAL_PORT_MONITOR.setLineModeUnix();
#endif

  // Allocate string buffer
  string = new char[STRING_SIZE];

  // Run all benchmarks.
  runBenchmarks();

  SERIAL_PORT_MONITOR.println("END");
#ifdef EPOXY_DUINO
  exit(0);
#endif
}

void loop() {
}
