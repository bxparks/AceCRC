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
esp8266_results = check_output(
    "cat CpuBenchmark/esp8266.txt MemoryBenchmark/esp8266.txt"
    "| ./generate_combined.awk",
    shell=True, text=True)
esp32_results = check_output(
    "cat CpuBenchmark/esp32.txt MemoryBenchmark/esp32.txt"
    "| ./generate_combined.awk",
    shell=True, text=True)
#teensy32_results = check_output(
#    "cat CpuBenchmark/nano.txt MemoryBenchmark/nano.txt | ./generate_table.awk < teensy32.txt", shell=True, text=True)
teensy32_results = 'TBD'

print(f"""\
# Benchmarks

Two benchmark programs are available here:

* MemoryBenchmark: Determines the flash and static memory usage of each CRC
  algorithm
* CpuBenchmark: Determines the CPU microseconds needed to calculate the CRC of a
  1 kiB (1024) string.

The `*.txt` output of these benchmarks are combined in this README.md into a
single table for each microcontroller type below.

**NOTE**: This file was auto-generated using `make README.md`. DO NOT EDIT.

**Version**: AceCRC v0.1.1

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

## Arduino Nano

* 16MHz ATmega328P
* Arduino IDE 1.8.13
* Arduino AVR Boards 1.8.3

```
{nano_results}
```

## Sparkfun Pro Micro

* 16 MHz ATmega32U4
* Arduino IDE 1.8.13
* SparkFun AVR Boards 1.1.13

```
{micro_results}
```

## SAMD21 M0 Mini

* 48 MHz ARM Cortex-M0+
* Arduino IDE 1.8.13
* Arduino SAMD Core 1.8.6

```
{samd_results}
```

## ESP8266

* NodeMCU 1.0 clone, 80MHz ESP8266
* Arduino IDE 1.8.13
* ESP8266 Boards 2.7.1

```
{esp8266_results}
```

## ESP32

* ESP32-01 Dev Board, 240 MHz Tensilica LX6
* Arduino IDE 1.8.13
* ESP32 Boards 1.0.4

```
{esp32_results}
```

## Teensy 3.2

* 96 MHz ARM Cortex-M4
* Arduino IDE 1.8.13
* Teensyduino 1.53.beta
* Compiler options: "Faster"

```
{teensy32_results}
```
""")
