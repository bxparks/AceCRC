#!/usr/bin/python3
#
# Python script that regenerates the README.md from the embedded template. Uses
# ./generate_table.awk to regenerate the ASCII tables from the various *.txt
# files.

from subprocess import check_output

nano_results = check_output(
    "./generate_table.awk < nano.txt", shell=True, text=True)
micro_results = check_output(
    "./generate_table.awk < micro.txt", shell=True, text=True)
stm32_results = check_output(
    "./generate_table.awk < stm32.txt", shell=True, text=True)
esp8266_results = check_output(
    "./generate_table.awk < esp8266.txt", shell=True, text=True)
esp32_results = check_output(
    "./generate_table.awk < esp32.txt", shell=True, text=True)
teensy32_results = check_output(
    "./generate_table.awk < teensy32.txt", shell=True, text=True)

print(f"""\
# Memory Benchmark

The `MemoryBenchmark.ino` compiles example code snippets using the various
CRC algorithms. The `FEATURE` macro flag controls which feature is
compiled. The `collect.sh` edits this `FEATURE` flag programmatically, then runs
the Arduino IDE compiler on the program, and extracts the flash and static
memory usage into a text file (e.g. `nano.txt`).

The numbers shown below should be considered to be rough estimates. It is often
difficult to separate out the code size of the library from the overhead imposed
by the runtime environment of the processor. For example, it often seems like
the ESP8266 allocates flash memory in blocks of a certain quantity, so the
calculated flash size can jump around in unexpected ways.

**Version**: AceCRC v1.1.0

**DO NOT EDIT**: This file was auto-generated using `make README.md`.

## How to Generate

This requires the [AUniter](https://github.com/bxparks/AUniter) script
to execute the Arduino IDE programmatically.

The `Makefile` has rules for several microcontrollers:

```
$ make benchmarks
```
produces the following files:

```
nano.txt
micro.txt
stm32.txt
esp8266.txt
esp32.txt
teensy32.txt
```

The `generate_table.awk` program reads one of `*.txt` files and prints out an
ASCII table that can be directly embedded into this README.md file. For example
the following command produces the table in the Nano section below:

```
$ ./generate_table.awk < nano.txt
```

Fortunately, we no longer need to run `generate_table.awk` for each `*.txt`
file. The process has been automated using the `generate_readme.py` script which
will be invoked by the following command:
```
$ make README.md
```

## Algorithms

* 0 Baseline: A program that does (almost) nothing
* 1 `crc8_bit`
* 2 `crc8_nibble`
* 3 `crc8_nibblem`
* 4 `crc8_byte`
* 5 `crc16ccitt_bit`
* 6 `crc16ccitt_nibble`
* 7 `crc16ccitt_nibblem`
* 8 `crc16ccitt_byte`
* 9 `crc16modbus_bit`
* 10 `crc16modbus_nibble`
* 11 `crc16modbus_nibblem`
* 12 `crc16modbus_byte`
* 13 `crc32_bit`
* 14 `crc32_nibble`
* 15 `crc32_nibblem`
* 16 `crc32_byte`
* 17 - CRC32 library (https://github.com/arduino-libraries/Arduino_CRC32)
* 18 - Arduino_CRC32 library (https://github.com/bakercp/CRC32)
* 19 - FastCRC library (https://github.com/FrankBoesing/FastCRC)

## Library Size Changes

**v1.0**

The size of the `crc_table` lookup table is:

* CRC8 using 'nibble' variant: 16 * 1 = 16 bytes
* CRC8 using 'byte' variant: 256 * 1 = 256 bytes
* CRC16 using 'nibble' variant: 16 * 2 = 32 bytes
* CRC16 using 'byte' variant: 256 * 2 = 512 bytes
* CRC32  using 'nibble' variant: 16 * 4 = 64 bytes
* CRC32 using 'byte' variant: 256 * 4 = 1024 bytes

These are moved from static RAM to flash memory with the `PROGMEM` directive on
certain microcontrollers (e.g. AVR, ESP8266), For the other processors, either
the `crc_table` is already in flash memory, or the `PROGMEM` attribute does not
do anything.

The `nibblem` variant is exactly the same as the `nibble` variant, except that
`PROGMEM` keyword is not used for the lookup `crc_table`, so that it is placed
in static memory instead of flash memory. This improves the speed of the
algorithm on AVR and ESP8266 processors because accessing static memory is
faster than flash memory on those processors.

**v1.1.0**

* Upgrade tool chain
* Remove SAMD21 board which I can no longer test.
* Add CRC-16-MODBUS algorithm.

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
* Arduino IDE 1.8.19
* Arduino AVR Boards 1.8.5

```
{nano_results}
```

### SparkFun Pro Micro

* 16 MHz ATmega32U4
* Arduino IDE 1.8.19
* SparkFun AVR Boards 1.1.13

```
{micro_results}
```

### STM32 Blue Pill

* STM32F103C8, 72 MHz ARM Cortex-M3
* Arduino IDE 1.8.19
* STM32duino 2.4.0

```
{stm32_results}
```

### ESP8266

* NodeMCU 1.0, 80MHz ESP8266
* Arduino IDE 1.8.19
* ESP8266 Boards 3.0.2

```
{esp8266_results}
```

### ESP32

* ESP32-01 Dev Board, 240 MHz Tensilica LX6
* Arduino IDE 1.8.19
* ESP32 Boards 2.0.5

```
{esp32_results}
```

### Teensy 3.2

* 96 MHz ARM Cortex-M4
* Arduino IDE 1.8.19
* Teensyduino 1.57
* Compiler options: "Faster"

```
{teensy32_results}
```
""")
