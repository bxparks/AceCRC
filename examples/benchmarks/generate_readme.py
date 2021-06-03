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
samd_results = check_output(
    "cat CpuBenchmark/samd.txt MemoryBenchmark/samd.txt"
    "| ./generate_combined.awk",
    shell=True, text=True)
stm32_results = check_output(
    "cat CpuBenchmark/stm32.txt MemoryBenchmark/stm32.txt"
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
teensy32_results = check_output(
    "cat CpuBenchmark/teensy32.txt MemoryBenchmark/teensy32.txt"
    "| ./generate_combined.awk",
    shell=True, text=True)
#teensy32_results = 'TBD'

print(f"""\
# Benchmarks

Two benchmark programs are available here:

* MemoryBenchmark: Determines the flash and static memory usage of each CRC
  algorithm
* CpuBenchmark: Determines the CPU microseconds needed to calculate the CRC of a
  1 kiB (1024) string.

The `*.txt` output of these benchmarks are combined in this README.md into a
single table for each microcontroller type below.

**Version**: AceCRC v1.0.1

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

**v1.0.1+**

* Upgrade STM32duino Core from 1.9.0 to 2.0.0.
    * Flash memory increases by 2.3kB across the board.
    * Static memory decreases by 250 bytes across the board.
    * AceCRC code unchanged.
* Upgrade SparkFun SAMD Core from 1.8.1 to 1.8.3.
    * No changes to flash or static memory.

## Results

### Arduino Nano

* 16MHz ATmega328P
* Arduino IDE 1.8.13
* Arduino AVR Boards 1.8.3

```
{nano_results}
```

### SparkFun Pro Micro

* 16 MHz ATmega32U4
* Arduino IDE 1.8.13
* SparkFun AVR Boards 1.1.13

```
{micro_results}
```

### SAMD21 M0 Mini

* 48 MHz ARM Cortex-M0+
* Arduino IDE 1.8.13
* SparkFun SAMD Core 1.8.3

```
{samd_results}
```

### STM32 Blue Pill

* STM32F103C8, 72 MHz ARM Cortex-M3
* Arduino IDE 1.8.13
* STM32duino 2.0.0

```
{stm32_results}
```

### ESP8266

* NodeMCU 1.0, 80MHz ESP8266
* Arduino IDE 1.8.13
* ESP8266 Boards 2.7.4

```
{esp8266_results}
```

### ESP32

* ESP32-01 Dev Board, 240 MHz Tensilica LX6
* Arduino IDE 1.8.13
* ESP32 Boards 1.0.6

```
{esp32_results}
```

### Teensy 3.2

* 96 MHz ARM Cortex-M4
* Arduino IDE 1.8.13
* Teensyduino 1.53
* Compiler options: "Faster"

```
{teensy32_results}
```
""")
