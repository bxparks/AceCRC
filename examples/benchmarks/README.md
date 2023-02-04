# Benchmarks

Two benchmark programs are available here:

* MemoryBenchmark: Determines the flash and static memory usage of each CRC
  algorithm
* CpuBenchmark: Determines the CPU microseconds needed to calculate the CRC of a
  1 kiB (1024) string.

The `*.txt` output of these benchmarks are combined in this README.md into a
single table for each microcontroller type below.

**Version**: AceCRC v1.1.0

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
* Arduino IDE 1.8.19
* Arduino AVR Boards 1.8.5

```
+--------------------------------------------------------------+
| CRC algorithm                   |  flash/  ram |  micros/kiB |
|---------------------------------+--------------+-------------|
| crc8_bit                        |     64/    0 |        7808 |
| crc8_nibble                     |    130/    0 |        7356 |
| crc8_nibblem                    |    134/   16 |        7224 |
| crc8_byte                       |    292/    0 |         916 |
|---------------------------------+--------------+-------------|
| crc16ccitt_bit                  |     84/    0 |       11888 |
| crc16ccitt_nibble               |    134/    0 |        5296 |
| crc16ccitt_nibblem              |    138/   32 |        5040 |
| crc16ccitt_byte                 |    562/    0 |        1496 |
|---------------------------------+--------------+-------------|
| crc16modbus_bit                 |    120/    0 |       11692 |
| crc16modbus_nibble              |    132/    0 |        5232 |
| crc16modbus_nibblem             |    134/   32 |        4912 |
| crc16modbus_byte                |    562/    0 |        1496 |
|---------------------------------+--------------+-------------|
| crc32_bit                       |    188/    0 |       18248 |
| crc32_nibble                    |    204/    0 |        7616 |
| crc32_nibblem                   |    208/   64 |        7104 |
| crc32_byte                      |   1106/    0 |        2272 |
|---------------------------------+--------------+-------------|
| CRC32                           |    208/    0 |        7688 |
| Arduino_CRC32                   |   1112/ 1024 |        2144 |
| FastCRC                         |   4262/    0 |        2160 |
+--------------------------------------------------------------+

```

### SparkFun Pro Micro

* 16 MHz ATmega32U4
* Arduino IDE 1.8.19
* SparkFun AVR Boards 1.1.13

```
+--------------------------------------------------------------+
| CRC algorithm                   |  flash/  ram |  micros/kiB |
|---------------------------------+--------------+-------------|
| crc8_bit                        |     64/    0 |        7852 |
| crc8_nibble                     |    130/    0 |        7396 |
| crc8_nibblem                    |    134/   16 |        7264 |
| crc8_byte                       |    292/    0 |         920 |
|---------------------------------+--------------+-------------|
| crc16ccitt_bit                  |     84/    0 |       11952 |
| crc16ccitt_nibble               |    134/    0 |        5332 |
| crc16ccitt_nibblem              |    138/   32 |        5068 |
| crc16ccitt_byte                 |    562/    0 |        1528 |
|---------------------------------+--------------+-------------|
| crc16modbus_bit                 |    120/    0 |       11752 |
| crc16modbus_nibble              |    132/    0 |        5268 |
| crc16modbus_nibblem             |    134/   32 |        4932 |
| crc16modbus_byte                |    562/    0 |        1500 |
|---------------------------------+--------------+-------------|
| crc32_bit                       |    188/    0 |       18344 |
| crc32_nibble                    |    204/    0 |        7664 |
| crc32_nibblem                   |    208/   64 |        7140 |
| crc32_byte                      |   1106/    0 |        2288 |
|---------------------------------+--------------+-------------|
| CRC32                           |    208/    0 |        7720 |
| Arduino_CRC32                   |   1112/ 1024 |        2164 |
| FastCRC                         |   4262/    0 |        2180 |
+--------------------------------------------------------------+

```

### STM32 Blue Pill

* STM32F103C8, 72 MHz ARM Cortex-M3
* Arduino IDE 1.8.19
* STM32duino 2.4.0

```
+--------------------------------------------------------------+
| CRC algorithm                   |  flash/  ram |  micros/kiB |
|---------------------------------+--------------+-------------|
| crc8_bit                        |     68/    0 |        2261 |
| crc8_nibble                     |     80/    0 |         502 |
| crc8_nibblem                    |     80/    0 |         531 |
| crc8_byte                       |    296/    0 |         259 |
|---------------------------------+--------------+-------------|
| crc16ccitt_bit                  |     84/    0 |        2390 |
| crc16ccitt_nibble               |    104/    0 |         573 |
| crc16ccitt_nibblem              |    104/    0 |         559 |
| crc16ccitt_byte                 |    564/    0 |         302 |
|---------------------------------+--------------+-------------|
| crc16modbus_bit                 |    120/    0 |        2407 |
| crc16modbus_nibble              |    104/    0 |         560 |
| crc16modbus_nibblem             |    104/    0 |         574 |
| crc16modbus_byte                |    564/    0 |         244 |
|---------------------------------+--------------+-------------|
| crc32_bit                       |    116/    0 |        2324 |
| crc32_nibble                    |    140/    0 |         559 |
| crc32_nibblem                   |    140/    0 |         573 |
| crc32_byte                      |   1080/    0 |         245 |
|---------------------------------+--------------+-------------|
| CRC32                           |    168/    0 |         846 |
| Arduino_CRC32                   |   1096/    0 |         246 |
| FastCRC                         |   4488/    0 |         188 |
+--------------------------------------------------------------+

```

### ESP8266

* NodeMCU 1.0, 80MHz ESP8266
* Arduino IDE 1.8.19
* ESP8266 Boards 3.0.2

```
+--------------------------------------------------------------+
| CRC algorithm                   |  flash/  ram |  micros/kiB |
|---------------------------------+--------------+-------------|
| crc8_bit                        |    128/    0 |        1512 |
| crc8_nibble                     |    144/    0 |         488 |
| crc8_nibblem                    |    112/   16 |         270 |
| crc8_byte                       |    336/    0 |         246 |
|---------------------------------+--------------+-------------|
| crc16ccitt_bit                  |    128/    0 |        1820 |
| crc16ccitt_nibble               |    160/    0 |         668 |
| crc16ccitt_nibblem              |    144/   32 |         283 |
| crc16ccitt_byte                 |    608/    0 |         375 |
|---------------------------------+--------------+-------------|
| crc16modbus_bit                 |    160/    0 |        1937 |
| crc16modbus_nibble              |    160/    0 |         642 |
| crc16modbus_nibblem             |    128/   32 |         245 |
| crc16modbus_byte                |    608/    0 |         375 |
|---------------------------------+--------------+-------------|
| crc32_bit                       |    144/    0 |        1567 |
| crc32_nibble                    |    176/    0 |         590 |
| crc32_nibblem                   |    160/   64 |         244 |
| crc32_byte                      |   1104/    0 |         340 |
|---------------------------------+--------------+-------------|
| CRC32                           |    224/    0 |         835 |
| Arduino_CRC32                   |   1120/ 1024 |         155 |
| FastCRC                         |   4704/    0 |         452 |
+--------------------------------------------------------------+

```

### ESP32

* ESP32-01 Dev Board, 240 MHz Tensilica LX6
* Arduino IDE 1.8.19
* ESP32 Boards 2.0.5

```
+--------------------------------------------------------------+
| CRC algorithm                   |  flash/  ram |  micros/kiB |
|---------------------------------+--------------+-------------|
| crc8_bit                        |    144/    0 |         521 |
| crc8_nibble                     |    152/    0 |         117 |
| crc8_nibblem                    |    152/    0 |         117 |
| crc8_byte                       |    356/    0 |          52 |
|---------------------------------+--------------+-------------|
| crc16ccitt_bit                  |    152/    0 |         516 |
| crc16ccitt_nibble               |    180/    0 |         135 |
| crc16ccitt_nibblem              |    180/    0 |         134 |
| crc16ccitt_byte                 |    632/    0 |          83 |
|---------------------------------+--------------+-------------|
| crc16modbus_bit                 |    196/    0 |         555 |
| crc16modbus_nibble              |    172/    0 |         120 |
| crc16modbus_nibblem             |    172/    0 |         120 |
| crc16modbus_byte                |    624/    0 |          75 |
|---------------------------------+--------------+-------------|
| crc32_bit                       |    176/    0 |         464 |
| crc32_nibble                    |    200/    0 |         113 |
| crc32_nibblem                   |    200/    0 |         112 |
| crc32_byte                      |   1136/    0 |          71 |
|---------------------------------+--------------+-------------|
| CRC32                           |    240/    0 |         198 |
| Arduino_CRC32                   |   1192/    0 |          71 |
| FastCRC                         |   4612/    0 |          43 |
+--------------------------------------------------------------+

```

### Teensy 3.2

* 96 MHz ARM Cortex-M4
* Arduino IDE 1.8.19
* Teensyduino 1.57
* Compiler options: "Faster"

```
+--------------------------------------------------------------+
| CRC algorithm                   |  flash/  ram |  micros/kiB |
|---------------------------------+--------------+-------------|
| crc8_bit                        |     76/    0 |        1262 |
| crc8_nibble                     |     88/    0 |         193 |
| crc8_nibblem                    |     88/    0 |         193 |
| crc8_byte                       |    300/    0 |          92 |
|---------------------------------+--------------+-------------|
| crc16ccitt_bit                  |     88/    0 |        1348 |
| crc16ccitt_nibble               |    112/    0 |         193 |
| crc16ccitt_nibblem              |    112/    0 |         193 |
| crc16ccitt_byte                 |    572/    0 |         140 |
|---------------------------------+--------------+-------------|
| crc16modbus_bit                 |    136/    0 |        1520 |
| crc16modbus_nibble              |    116/    0 |         182 |
| crc16modbus_nibblem             |    116/    0 |         183 |
| crc16modbus_byte                |    568/    0 |         139 |
|---------------------------------+--------------+-------------|
| crc32_bit                       |    136/    0 |        1393 |
| crc32_nibble                    |    140/    0 |         183 |
| crc32_nibblem                   |    140/    0 |         183 |
| crc32_byte                      |   1080/    0 |         154 |
|---------------------------------+--------------+-------------|
| CRC32                           |    176/    0 |         429 |
| Arduino_CRC32                   |   1096/    0 |         155 |
| FastCRC                         |    172/    0 |          23 |
+--------------------------------------------------------------+

```

