#!/usr/bin/python3
#
# Python script that regenerates the README.md from the embedded template. Uses
# ./generate_table.awk to regenerate the ASCII tables from the various *.txt
# files.

from subprocess import check_output

nano_results = check_output(
    "cat CpuBenchmark/nano.txt MemoryBenchmark/nano.txt"
    "| ./generate_combined.awk",
    shell=True, text=True)
micro_results = check_output(
    "cat CpuBenchmark/micro.txt MemoryBenchmark/micro.txt"
    "| ./generate_combined.awk",
    shell=True, text=True)
samd21_results = check_output(
    "cat CpuBenchmark/samd21.txt MemoryBenchmark/samd21.txt"
    "| ./generate_combined.awk",
    shell=True, text=True)
stm32_results = check_output(
    "cat CpuBenchmark/stm32.txt MemoryBenchmark/stm32.txt"
    "| ./generate_combined.awk",
    shell=True, text=True)
samd51_results = check_output(
    "cat CpuBenchmark/samd51.txt MemoryBenchmark/samd51.txt"
    "| ./generate_combined.awk",
    shell=True, text=True)
esp8266_results = check_output(
    "cat CpuBenchmark/esp8266.txt MemoryBenchmark/esp8266.txt"
    "| ./generate_combined.awk",
    shell=True, text=True)
esp32_results = check_output(
    "cat CpuBenchmark/esp32.txt MemoryBenchmark/esp32.txt"
    "| ./generate_combined.awk",
    shell=True, text=True)

print(f"""\
# Benchmarks

Two benchmark programs are available here:

* MemoryBenchmark: Determines the flash and static memory usage of each CRC
  algorithm
* CpuBenchmark: Determines the CPU microseconds needed to calculate the CRC of a
  1 kiB (1024) string.

The `*.txt` output of these benchmarks are combined in this README.md into a
single table for each microcontroller type below.

**Version**: AceCRC v1.1.1

**DO NOT EDIT**: This file was auto-generated using `make README.md`.

## How to Generate

This requires the [AUniter](https://github.com/bxparks/AUniter) script
to execute the Arduino IDE programmatically.

Go into the CpuBenchmark and MemoryBenchmark directories and generate
the `*.txt` files as described in the respective README.md files.

Type

```
$ make README.md
```

in this directory. The various `*.txt` files will be piped through the
`generate_combined.awk` program to generate the ASCII tables below.

## Changes

**v0.4**

* Updated `tools/generate.py` to convert an internal loop or index variable
  inside `crc_update()` from an `unsigned int` to `uint8_t`.
    * Reduced memory consumption by a 0-10 bytes.
    * Reduced CPU time by 6%-34% on 8-bit processors.
    * No algorithm got slower by using a `uint8_t` variable, even on 32-bit
      processors.
* Added benchmarks for a handful of third-party CRC libraries
  (CRC32, Arduino_CRC32, FastCRC) out of curiosity.

**v1.0**

Add `nibblem` variant, similar to `nibble` except that the CRC lookup table is
placed in static ram, instead of flash RAM. For AVR processors, there is small
increase in performance, 2-7%. But for ESP8266 processors, the performance goes
up by 1.9X to 2.7X.

**v1.1.0**

* Upgrade tool chain.
* Remove SAMD21 board, no longer able to test.
* Add crc16modbus.

## Results

* CRC32 (https://github.com/bakercp/CRC32)
    * uses a 4-bit lookup table, should be comparable to `crc32_nibble`
* Arduino_CRC32 (https://github.com/arduino-libraries/Arduino_CRC32)
    * uses an 8-bit lookup table in RAM not `PROGMEM`
    * comparable to `crc32_byte` but usually faster because accessing RAM is
      faster than `PROGMEM` on most processors
* FastCRC (https://github.com/FrankBoesing/FastCRC)
    * uses a 10-bit lookup table (1024 elements)
    * should be faster than `crc32_byte` in theory, but is actually slower than
      `crc32_byte` for an ESP8266 (I think this is because access to `PROGMEM`
      data is extra slow on an ESP8266)

### Arduino Nano

* 16MHz ATmega328P
* Arduino IDE 1.8.19, Arduino CLI 0.33.0
* Arduino AVR Boards 1.8.6

```
{nano_results}
```

### SparkFun Pro Micro

* 16 MHz ATmega32U4
* Arduino IDE 1.8.19, Arduino CLI 0.33.0
* SparkFun AVR Boards 1.1.13

```
{micro_results}
```

## Seeed Studio XIAO (SAMD21)

* SAMD21, 48 MHz ARM Cortex-M0+
* Arduino IDE 1.8.19, Arduino CLI 0.33.0
* Seeeduino SAMD Boards 1.8.4

```
{samd21_results}

### STM32 Blue Pill

* STM32F103C8, 72 MHz ARM Cortex-M3
* Arduino IDE 1.8.19, Arduino CLI 0.33.0
* STM32duino 2.6.0

```
{stm32_results}
```

## Adafruit ItsyBitsy M4 (SAMD51)

* SAMD51, 120 MHz ARM Cortex-M4
* Arduino IDE 1.8.19, Arduino CLI 0.33.0
* Adafruit SAMD 1.7.13

```
{stm32_results}
```

### ESP8266

* NodeMCU 1.0, 80MHz ESP8266
* Arduino IDE 1.8.19, Arduino CLI 0.33.0
* ESP8266 Boards 3.0.2

```
{esp8266_results}
```

### ESP32

* ESP32-01 Dev Board, 240 MHz Tensilica LX6
* Arduino IDE 1.8.19, Arduino CLI 0.33.0
* ESP32 Boards 2.0.9

```
{esp32_results}
```
""")
