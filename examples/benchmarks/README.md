# Benchmarks

Two benchmark programs are available here:

* MemoryBenchmark: Determines the flash and static memory usage of each CRC
  algorithm
* CpuBenchmark: Determines the CPU microseconds needed to calculate the CRC of a
  1 kiB (1024) string.

The `*.txt` output of these benchmarks are combined in this README.md into a
single table for each microcontroller type below.

**Version**: AceCRC v1.0

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

### v1.0

Add `nibblem` variant, similar to `nibble` except that the CRC lookup table is
placed in static ram, instead of flash RAM. For AVR processors, there is small
increase in performance, 2-7%. But for ESP8266 processors, the performance goes
up by 1.9X to 2.7X.

### v0.4

* Updated `tools/generate.py` to convert an internal loop or index variable
  inside `crc_update()` from an `unsigned int` to `uint8_t`.
    * Reduced memory consumption by a 0-10 bytes.
    * Reduced CPU time by 6%-34% on 8-bit processors.
    * No algorithm got slower by using a `uint8_t` variable, even on 32-bit
      processors.
* Added benchmarks for a handful of third-party CRC libraries
  (CRC32, Arduino_CRC32, FastCRC) out of curiosity.

## Arduino Nano

* 16MHz ATmega328P
* Arduino IDE 1.8.13
* Arduino AVR Boards 1.8.3

```
+--------------------------------------------------------------+
| CRC algorithm                   |  flash/  ram |  micros/kiB |
|---------------------------------+--------------+-------------|
| crc8_bit                        |     72/    0 |        9312 |
| crc8_nibble                     |    130/    0 |        7352 |
| crc8_nibblem                    |    134/   16 |        7228 |
| crc8_byte                       |    292/    0 |         920 |
| crc16ccitt_bit                  |     80/    0 |       11096 |
| crc16ccitt_nibble               |    134/    0 |        5296 |
| crc16ccitt_nibblem              |    138/   32 |        5036 |
| crc16ccitt_byte                 |    562/    0 |        1496 |
| crc32_bit                       |    184/    0 |       16164 |
| crc32_nibble                    |    204/    0 |        7624 |
| crc32_nibblem                   |    208/   64 |        7104 |
| crc32_byte                      |   1106/    0 |        2276 |
|---------------------------------+--------------+-------------|
| CRC32                           |    208/    0 |        7688 |
| Arduino_CRC32                   |   1112/ 1024 |        2144 |
| FastCRC                         |   4262/    0 |        2160 |
+--------------------------------------------------------------+

```

## Sparkfun Pro Micro

* 16 MHz ATmega32U4
* Arduino IDE 1.8.13
* SparkFun AVR Boards 1.1.13

```
+--------------------------------------------------------------+
| CRC algorithm                   |  flash/  ram |  micros/kiB |
|---------------------------------+--------------+-------------|
| crc8_bit                        |     72/    0 |        9372 |
| crc8_nibble                     |    130/    0 |        7392 |
| crc8_nibblem                    |    134/   16 |        7272 |
| crc8_byte                       |    292/    0 |         928 |
| crc16ccitt_bit                  |     80/    0 |       11156 |
| crc16ccitt_nibble               |    134/    0 |        5316 |
| crc16ccitt_nibblem              |    138/   32 |        5068 |
| crc16ccitt_byte                 |    562/    0 |        1504 |
| crc32_bit                       |    184/    0 |       16248 |
| crc32_nibble                    |    204/    0 |        7660 |
| crc32_nibblem                   |    208/   64 |        7144 |
| crc32_byte                      |   1106/    0 |        2284 |
|---------------------------------+--------------+-------------|
| CRC32                           |    208/    0 |        7720 |
| Arduino_CRC32                   |   1112/ 1024 |        2160 |
| FastCRC                         |   4262/    0 |        2180 |
+--------------------------------------------------------------+

```

## SAMD21 M0 Mini

* 48 MHz ARM Cortex-M0+
* Arduino IDE 1.8.13
* Sparkfun SAMD Core 1.8.1

```
+--------------------------------------------------------------+
| CRC algorithm                   |  flash/  ram |  micros/kiB |
|---------------------------------+--------------+-------------|
| crc8_bit                        |     64/    0 |        2746 |
| crc8_nibble                     |     80/    0 |         625 |
| crc8_nibblem                    |     80/    0 |         625 |
| crc8_byte                       |    296/    0 |         295 |
| crc16ccitt_bit                  |     72/    0 |        2831 |
| crc16ccitt_nibble               |    104/    0 |         676 |
| crc16ccitt_nibblem              |    104/    0 |         706 |
| crc16ccitt_byte                 |    568/    0 |         399 |
| crc32_bit                       |    112/    0 |        2838 |
| crc32_nibble                    |    136/    0 |         652 |
| crc32_nibblem                   |    136/    0 |         636 |
| crc32_byte                      |   1080/    0 |         380 |
|---------------------------------+--------------+-------------|
| CRC32                           |    168/    0 |        1266 |
| Arduino_CRC32                   |   1088/    0 |         380 |
| FastCRC                         |   4536/    0 |         347 |
+--------------------------------------------------------------+

```

## STM32 Blue Pill

* STM32F103C8, 72 MHz ARM Cortex-M3
* Arduino IDE 1.8.13
* STM32duino 1.9.0

```
+--------------------------------------------------------------+
| CRC algorithm                   |  flash/  ram |  micros/kiB |
|---------------------------------+--------------+-------------|
| crc8_bit                        |     60/    0 |        1982 |
| crc8_nibble                     |     80/    0 |         459 |
| crc8_nibblem                    |     80/    0 |         517 |
| crc8_byte                       |    296/    0 |         245 |
| crc16ccitt_bit                  |     68/    0 |        2039 |
| crc16ccitt_nibble               |    104/    0 |         573 |
| crc16ccitt_nibblem              |    104/    0 |         559 |
| crc16ccitt_byte                 |    564/    0 |         302 |
| crc32_bit                       |    108/    0 |        2245 |
| crc32_nibble                    |    140/    0 |         559 |
| crc32_nibblem                   |    140/    0 |         574 |
| crc32_byte                      |   1080/    0 |         244 |
|---------------------------------+--------------+-------------|
| CRC32                           |    172/    0 |         931 |
| Arduino_CRC32                   |   1096/    0 |         316 |
| FastCRC                         |   4492/    0 |         183 |
+--------------------------------------------------------------+

```

## ESP8266

* NodeMCU 1.0, 80MHz ESP8266
* Arduino IDE 1.8.13
* ESP8266 Boards 2.7.4

```
+--------------------------------------------------------------+
| CRC algorithm                   |  flash/  ram |  micros/kiB |
|---------------------------------+--------------+-------------|
| crc8_bit                        |     96/    0 |        1500 |
| crc8_nibble                     |    144/    0 |         490 |
| crc8_nibblem                    |    128/   16 |         257 |
| crc8_byte                       |    336/    0 |         233 |
| crc16ccitt_bit                  |    112/    0 |        1499 |
| crc16ccitt_nibble               |    176/    0 |         681 |
| crc16ccitt_nibblem              |    144/   32 |         270 |
| crc16ccitt_byte                 |    624/    0 |         363 |
| crc32_bit                       |    144/    0 |        1400 |
| crc32_nibble                    |    208/    0 |         618 |
| crc32_nibblem                   |    160/   64 |         232 |
| crc32_byte                      |   1120/    0 |         345 |
|---------------------------------+--------------+-------------|
| CRC32                           |    240/    0 |         950 |
| Arduino_CRC32                   |   1120/ 1024 |         142 |
| FastCRC                         |   4704/    0 |         486 |
+--------------------------------------------------------------+

```

## ESP32

* ESP32-01 Dev Board, 240 MHz Tensilica LX6
* Arduino IDE 1.8.13
* ESP32 Boards 1.0.4

```
+--------------------------------------------------------------+
| CRC algorithm                   |  flash/  ram |  micros/kiB |
|---------------------------------+--------------+-------------|
| crc8_bit                        |    132/    0 |         498 |
| crc8_nibble                     |    152/    0 |         118 |
| crc8_nibblem                    |    152/    0 |         117 |
| crc8_byte                       |    356/    0 |          52 |
| crc16ccitt_bit                  |    140/    0 |         498 |
| crc16ccitt_nibble               |    176/    0 |         125 |
| crc16ccitt_nibblem              |    176/    0 |         125 |
| crc16ccitt_byte                 |    632/    0 |          75 |
| crc32_bit                       |    168/    0 |         396 |
| crc32_nibble                    |    200/    0 |         108 |
| crc32_nibblem                   |    200/    0 |         108 |
| crc32_byte                      |   1140/    0 |          71 |
|---------------------------------+--------------+-------------|
| CRC32                           |    272/    8 |         189 |
| Arduino_CRC32                   |   1196/    0 |          71 |
| FastCRC                         |   4640/   16 |          40 |
+--------------------------------------------------------------+

```

## Teensy 3.2

* 96 MHz ARM Cortex-M4
* Arduino IDE 1.8.13
* Teensyduino 1.53
* Compiler options: "Faster"

```
+--------------------------------------------------------------+
| CRC algorithm                   |  flash/  ram |  micros/kiB |
|---------------------------------+--------------+-------------|
| crc8_bit                        |     68/    0 |        1133 |
| crc8_nibble                     |     88/    0 |         193 |
| crc8_nibblem                    |     88/    0 |         193 |
| crc8_byte                       |    300/    0 |          92 |
| crc16ccitt_bit                  |     76/    0 |        1176 |
| crc16ccitt_nibble               |    112/    0 |         193 |
| crc16ccitt_nibblem              |    112/    0 |         193 |
| crc16ccitt_byte                 |    572/    0 |         140 |
| crc32_bit                       |    132/    0 |        1393 |
| crc32_nibble                    |    140/    0 |         183 |
| crc32_nibblem                   |    140/    0 |         183 |
| crc32_byte                      |   1080/    0 |         155 |
|---------------------------------+--------------+-------------|
| CRC32                           |    176/    0 |         429 |
| Arduino_CRC32                   |   1096/    0 |         155 |
| FastCRC                         |    172/    0 |          23 |
+--------------------------------------------------------------+

```

