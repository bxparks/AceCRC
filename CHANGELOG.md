# Changelog

* Unreleased
* 0.3.2 (2020-12-09)
    * Add CpuBenchmark numbers for some third-party CRC libraries for curiosity.
    * Rewrite README.md for clarity.
    * Use Arduino-CLI to gather MemoryBenchmark results faster.
    * No functional change.
* 0.3.1 (2020-12-03)
    * Use exact sized `uint16_t` and `uint32_t` as the typedef for `crc_t`,
      instead of the default `uint_fast16_t` and `uint_fast32_t` produced by
      pycrc. This change affects only the 32-bit processors where
      `uint_fast16_t` is defined to be 32 bits instead of 16 bits. Some of the
      `crc16ccitt` algorithms become slightly slower but some become slightly
      faster. The biggest difference is that the `crc_table` sizes for the
      `cc16ccitt` algorithms all become 1/2 the size, which is a big win.
    * Add CRC-8 algorithms in `crc8_bit`, `crc8_nibble`, and `crc8_byte`
      namespaces. Update MemoryBenchmark and CpuBenchmark numbers.
    * Add recommendation list of various algorithms in README.md.
* 0.3 (2020-12-03)
    * Botched release, deleted.
* 0.2 (2020-12-03)
    * Generate CPU times of each CRC algorithm and variant using
      [examples/benchmarks/CpuBenchmark](examples/benchmarks/CpuBenchmark).
    * Create combined CPU and Memory benchmark tables in
      [examples/benchmarks](examples/benchmarks).
    * Insert a `crc_calculate()` convenience function into the header files so
      that the CRC can be calculated in one-shot, instead of forcing the user to
      call `crc_init()`, `crc_update()` and `crc_finalize()`.
    * Remove `static` keyword from `*.hpp` files. Not needed in C++ and
      prevents doxygen doc generation of those functions.
* 0.1.1 (2020-11-29)
    * Fix embarrassing typos in library.properties.
* 0.1 (2020-11-29)
    * Move `crc_table` lookup table to flash using `PROGMEM`.
    * Add `MemoryBenchmark` to determine flash and static RAM consumption of
      each algorithm.
    * Add doxygen docs.
* Initial Commit (2020-11-29)
    * Initial commit with 2 CRC algorithms: `crc32()` and `crc16ccitt()`
