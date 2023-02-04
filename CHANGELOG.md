# Changelog

* Unreleased
* 1.1.0 (2023-02-03)
    * Upgrade tool chain
        * Arduino IDE from 1.8.13 to 1.8.19
        * Arduino CLI from 0.15.2 to 0.27.1
        * Arduino AVR Core from 1.8.3 to 1.8.5
        * SparkFun AVR Core 1.8.13
        * SparkFun SAMD Core from 1.8.1 to 1.8.7
        * STM32duino Core from 1.9.0 to 2.3.0
        * ESP8266 Core from 2.7.4 to 3.0.2
        * ESP32 Core from 1.0.6 to 2.0.5
        * TeensyDuino from 1.54 to 1.57
    * Remove SAMD21 boards.
        * No longer supported.
    * Add CRC-16-MODBUS from pycrc (see
      [Issue#12](https://github.com/bxparks/AceCRC/issues/12)).
* 1.0.1 (2021-04-19)
    * Update EpoxyDuino Makefiles for better compatibility with FreeBSD.
    * Add recommendation to use `nibblem` on ESP8266.
    * Upgrade to ESP32 Arduino Core v1.0.6 and update benchmark numbers (no
      significant changes).
    * No functional change in this release.
* 1.0 (2021-02-21)
    * Add `nibblem` variant.
        * Same as `nibble` but the 16-element lookup table is stored in static
          memory instead of flash memory.
        * On ESP8266, this causes a **1.9X-2.7X** speed improvement because
          accessing the flash memory access is much slower than static memory.
        * Only a 2-7% speed improvement for AVR processors.
    * Graduate to v1.0.
* 0.4.2 (2021-01-22)
    * Update UnixHostDuino 0.4 to EpoxyDuino 0.5
    * No functional change in this release.
* 0.4.1 (2021-01-19)
    * Add official support for STM32 by validating against STM32 Blue Pill
      board. Update CpuBenchmark and MemoryBenchmark numbers.
    * Re-add benchmark numbers for Teensy 3.2. Able to upload to it again
      after reinstalling Ubuntu 20.04.
    * No functional change in this release.
* 0.4 (2020-12-10)
    * Convert internal loop or index variable inside `crc_update()` fgrom
      `unsigned int` to a one-byte `uint8_t`. Improves CPU performance by 6%-34%
      on 8-bit processors. See
      [examples/benchmarks/CpuBenchmark](examples/benchmarks/CpuBenchmark). No
      change in performance for 32-bit processors.
    * Add MemoryBenchmark numbers for the same third-party CRC libraries as
      CpuBenchmark.
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
