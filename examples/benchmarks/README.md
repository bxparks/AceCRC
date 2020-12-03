# Benchmarks

Two benchmark programs are available in this directory:

* MemoryBenchmark: Determines the flash and static memory usage of each CRC
  algorithm
* CpuBenchmark: Determines the CPU microseconds needed to calculate the CRC of a
  1 kiB (1024) string.

The `*.txt` output of these benchmarks are combined in this README.md into a
single benchmark table for each microcontroller type below.

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
+--------------------------------------------------------------+
| CRC algorithm                   |  flash/  ram |  micros/kiB |
|---------------------------------+--------------+-------------|
| crc16ccitt_bit                  |     90/    0 |       12772 |
| crc16ccitt_nibble               |    158/    0 |        7086 |
| crc16ccitt_byte                 |    564/    0 |        1549 |
| crc32_bit                       |    192/    0 |       18379 |
| crc32_nibble                    |    220/    0 |        8956 |
| crc32_byte                      |   1106/    0 |        2388 |
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
| crc16ccitt_bit                  |     90/    0 |       12839 |
| crc16ccitt_nibble               |    158/    0 |        7124 |
| crc16ccitt_byte                 |    564/    0 |        1557 |
| crc32_bit                       |    192/    0 |       18489 |
| crc32_nibble                    |    220/    0 |        9003 |
| crc32_byte                      |   1106/    0 |        2401 |
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
| crc16ccitt_bit                  |     80/    0 |        2942 |
| crc16ccitt_nibble               |    136/    0 |         675 |
| crc16ccitt_byte                 |   1080/    0 |         446 |
| crc32_bit                       |    112/    0 |        2946 |
| crc32_nibble                    |    136/    0 |         637 |
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
| crc16ccitt_bit                  |    112/    0 |        1307 |
| crc16ccitt_nibble               |    224/    0 |         668 |
| crc16ccitt_byte                 |   1136/    0 |         366 |
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
| crc16ccitt_bit                  |    152/    0 |         504 |
| crc16ccitt_nibble               |    208/    0 |         109 |
| crc16ccitt_byte                 |   1148/    0 |          76 |
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

