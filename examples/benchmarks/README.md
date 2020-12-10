# Benchmarks

Two benchmark programs are available here:

* MemoryBenchmark: Determines the flash and static memory usage of each CRC
  algorithm
* CpuBenchmark: Determines the CPU microseconds needed to calculate the CRC of a
  1 kiB (1024) string.

The `*.txt` output of these benchmarks are combined in this README.md into a
single table for each microcontroller type below.

**Version**: AceCRC v0.3.2

**NOTE**: This file was auto-generated using `make README.md`. DO NOT EDIT.

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
+--------------------------------------------------------------+
| CRC algorithm                   |  flash/  ram |  micros/kiB |
|---------------------------------+--------------+-------------|
| crc8_bit                        |     80/    0 |       10980 |
| crc8_nibble                     |    126/    0 |        7216 |
| crc8_byte                       |    292/    0 |         910 |
| crc16ccitt_bit                  |     90/    0 |       12778 |
| crc16ccitt_nibble               |    158/    0 |        7088 |
| crc16ccitt_byte                 |    564/    0 |        1552 |
| crc32_bit                       |    192/    0 |       18446 |
| crc32_nibble                    |    220/    0 |        8964 |
| crc32_byte                      |   1106/    0 |        2394 |
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
| crc8_bit                        |     80/    0 |       11034 |
| crc8_nibble                     |    126/    0 |        7260 |
| crc8_byte                       |    292/    0 |         914 |
| crc16ccitt_bit                  |     90/    0 |       12848 |
| crc16ccitt_nibble               |    158/    0 |        7126 |
| crc16ccitt_byte                 |    564/    0 |        1564 |
| crc32_bit                       |    192/    0 |       18540 |
| crc32_nibble                    |    220/    0 |        9008 |
| crc32_byte                      |   1106/    0 |        2408 |
+--------------------------------------------------------------+

```

## SAMD21 M0 Mini

* 48 MHz ARM Cortex-M0+
* Arduino IDE 1.8.13
* Arduino SAMD Core 1.8.6

```
+--------------------------------------------------------------+
| CRC algorithm                   |  flash/  ram |  micros/kiB |
|---------------------------------+--------------+-------------|
| crc8_bit                        |     64/    0 |        2742 |
| crc8_nibble                     |     80/    0 |         630 |
| crc8_byte                       |    296/    0 |         286 |
| crc16ccitt_bit                  |     72/    0 |        2831 |
| crc16ccitt_nibble               |    104/    0 |         702 |
| crc16ccitt_byte                 |    568/    0 |         399 |
| crc32_bit                       |    112/    0 |        2945 |
| crc32_nibble                    |    136/    0 |         652 |
| crc32_byte                      |   1080/    0 |         380 |
+--------------------------------------------------------------+

```

## ESP8266

* NodeMCU 1.0 clone, 80MHz ESP8266
* Arduino IDE 1.8.13
* ESP8266 Boards 2.7.1

```
+--------------------------------------------------------------+
| CRC algorithm                   |  flash/  ram |  micros/kiB |
|---------------------------------+--------------+-------------|
| crc8_bit                        |     96/    0 |        1500 |
| crc8_nibble                     |    144/    0 |         489 |
| crc8_byte                       |    336/    0 |         233 |
| crc16ccitt_bit                  |    112/    0 |        1499 |
| crc16ccitt_nibble               |    192/    0 |         681 |
| crc16ccitt_byte                 |    624/    0 |         364 |
| crc32_bit                       |    144/    0 |        1388 |
| crc32_nibble                    |    208/    0 |         617 |
| crc32_byte                      |   1136/    0 |         342 |
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
| crc8_nibble                     |    152/    0 |         117 |
| crc8_byte                       |    356/    0 |          53 |
| crc16ccitt_bit                  |    140/    0 |         498 |
| crc16ccitt_nibble               |    176/    0 |         125 |
| crc16ccitt_byte                 |    632/    0 |          75 |
| crc32_bit                       |    168/    0 |         671 |
| crc32_nibble                    |    200/    0 |         109 |
| crc32_byte                      |   1140/    0 |          71 |
+--------------------------------------------------------------+

```

## Teensy 3.2

* 96 MHz ARM Cortex-M4
* Arduino IDE 1.8.13
* Teensyduino 1.53.beta
* Compiler options: "Faster"

```
TBD
```

