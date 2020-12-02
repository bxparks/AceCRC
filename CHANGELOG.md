# Changelog

* Unreleased
    * Generate CPU times of each CRC algorithm and variant using
      [examples/CpuBenchmark](examples/CpuBenchmark).
* 0.1.1 (2020-11-29)
    * Fix embarrassing typos in library.properties.
* 0.1 (2020-11-29)
    * Move `crc_table` lookup table to flash using `PROGMEM`.
    * Add `MemoryBenchmark` to determine flash and static RAM consumption of
      each algorithm.
    * Add doxygen docs.
* Initial Commit (2020-11-29)
    * Initial commit with 2 CRC algorithms: `crc32()` and `crc16ccitt()`
