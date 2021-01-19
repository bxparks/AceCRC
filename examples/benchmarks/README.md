# Benchmarks

Two benchmark programs are available here:

* MemoryBenchmark: Determines the flash and static memory usage of each CRC
  algorithm
* CpuBenchmark: Determines the CPU microseconds needed to calculate the CRC of a
  1 kiB (1024) string.

The `*.txt` output of these benchmarks are combined in this README.md into a
single table for each microcontroller type below.

**Version**: AceCRC v0.4.1

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
| crc8_bit                        |     72/    0 |        9306 |
| crc8_nibble                     |    130/    0 |        7346 |
| crc8_byte                       |    292/    0 |         908 |
| crc16ccitt_bit                  |     80/    0 |       11106 |
| crc16ccitt_nibble               |    134/    0 |        5290 |
| crc16ccitt_byte                 |    562/    0 |        1490 |
| crc32_bit                       |    184/    0 |       16062 |
| crc32_nibble                    |    204/    0 |        7610 |
| crc32_byte                      |   1106/    0 |        2262 |
|---------------------------------+--------------+-------------|
| CRC32                           |    208/    0 |        7674 |
| Arduino_CRC32                   |   1112/ 1024 |        2134 |
| FastCRC                         |   4262/    0 |        2130 |
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
| crc8_bit                        |     72/    0 |        9352 |
| crc8_nibble                     |    130/    0 |        7388 |
| crc8_byte                       |    292/    0 |         914 |
| crc16ccitt_bit                  |     80/    0 |       11164 |
| crc16ccitt_nibble               |    134/    0 |        5316 |
| crc16ccitt_byte                 |    562/    0 |        1500 |
| crc32_bit                       |    184/    0 |       16148 |
| crc32_nibble                    |    204/    0 |        7648 |
| crc32_byte                      |   1106/    0 |        2272 |
|---------------------------------+--------------+-------------|
| CRC32                           |    208/    0 |        7716 |
| Arduino_CRC32                   |   1112/ 1024 |        2148 |
| FastCRC                         |   4262/    0 |        2130 |
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
| crc8_nibble                     |     80/    0 |         630 |
| crc8_byte                       |    296/    0 |         286 |
| crc16ccitt_bit                  |     72/    0 |        2831 |
| crc16ccitt_nibble               |    104/    0 |         703 |
| crc16ccitt_byte                 |    568/    0 |         398 |
| crc32_bit                       |    112/    0 |        2837 |
| crc32_nibble                    |    136/    0 |         652 |
| crc32_byte                      |   1080/    0 |         380 |
|---------------------------------+--------------+-------------|
| CRC32                           |    168/    0 |        1269 |
| Arduino_CRC32                   |   1088/    0 |         381 |
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
| crc8_bit                        |     60/    0 |        2276 |
| crc8_nibble                     |     80/    0 |         502 |
| crc8_byte                       |    296/    0 |         259 |
| crc16ccitt_bit                  |     68/    0 |        1989 |
| crc16ccitt_nibble               |    104/    0 |         559 |
| crc16ccitt_byte                 |    564/    0 |         259 |
| crc32_bit                       |    108/    0 |        2245 |
| crc32_nibble                    |    140/    0 |         559 |
| crc32_byte                      |   1080/    0 |         245 |
|---------------------------------+--------------+-------------|
| CRC32                           |    172/    0 |         831 |
| Arduino_CRC32                   |   1096/    0 |         316 |
| FastCRC                         |   4492/    0 |         181 |
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
| crc8_bit                        |     96/    0 |        1499 |
| crc8_nibble                     |    144/    0 |         488 |
| crc8_byte                       |    336/    0 |         233 |
| crc16ccitt_bit                  |    112/    0 |        1501 |
| crc16ccitt_nibble               |    176/    0 |         681 |
| crc16ccitt_byte                 |    624/    0 |         364 |
| crc32_bit                       |    144/    0 |        1401 |
| crc32_nibble                    |    208/    0 |         617 |
| crc32_byte                      |   1120/    0 |         342 |
|---------------------------------+--------------+-------------|
| CRC32                           |    240/    0 |         937 |
| Arduino_CRC32                   |   1120/ 1024 |         143 |
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
| crc8_byte                       |    356/    0 |          53 |
| crc16ccitt_bit                  |    140/    0 |         498 |
| crc16ccitt_nibble               |    176/    0 |         125 |
| crc16ccitt_byte                 |    632/    0 |          75 |
| crc32_bit                       |    168/    0 |         396 |
| crc32_nibble                    |    200/    0 |         108 |
| crc32_byte                      |   1140/    0 |          71 |
|---------------------------------+--------------+-------------|
| CRC32                           |    272/    8 |         189 |
| Arduino_CRC32                   |   1196/    0 |          72 |
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
| crc8_bit                        |     68/    0 |        1134 |
| crc8_nibble                     |     88/    0 |         194 |
| crc8_byte                       |    300/    0 |          92 |
| crc16ccitt_bit                  |     76/    0 |        1176 |
| crc16ccitt_nibble               |    112/    0 |         193 |
| crc16ccitt_byte                 |    572/    0 |         141 |
| crc32_bit                       |    132/    0 |        1392 |
| crc32_nibble                    |    140/    0 |         183 |
| crc32_byte                      |   1080/    0 |         154 |
|---------------------------------+--------------+-------------|
| CRC32                           |    176/    0 |         429 |
| Arduino_CRC32                   |   1096/    0 |         156 |
| FastCRC                         |    172/    0 |          23 |
+--------------------------------------------------------------+

```

