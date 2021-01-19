# CPU Benchmark

The `CPUBenchmark.ino` determines the CPU run time of each of various CRC
algorithms.

**Version**: AceCRC v0.4.1

**DO NOT EDIT**: This file was auto-generated using `make README.md`.

## How to Generate

This requires the [AUniter](https://github.com/bxparks/AUniter) script
to execute the Arduino IDE programmatically.

The `Makefile` has rules to generate the `*.txt` results file for several
microcontrollers that I usually support, but the `$ make benchmarks` command
does not work very well because the USB port of the microcontroller is a
dynamically changing parameter. I created a semi-automated way of collect the
`*.txt` files:

1. Connect the microcontroller to the serial port. I usually do this through a
USB hub with individually controlled switch.
2. Type `$ auniter ports` to determine its `/dev/ttyXXX` port number (e.g.
`/dev/ttyUSB0` or `/dev/ttyACM0`).
3. If the port is `USB0` or `ACM0`, type `$ make nano.txt`, etc.
4. Switch off the old microontroller.
5. Go to Step 1 and repeat for each microcontroller.

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

The CPU times below are given in microseconds to compute the CRC of a string of
characters between 0.5 kiB to 10 kiB long (depending on the speed of the
processor), normalized to 1 kiB, so has the units of `micros/kiB`.


## CPU Time Changes

### v0.4

I converted an internal loop variable in `crc_update()` (named `i` in the `bit`
variant and `tbl_idx` in `nibble` and `byte` variants) from an `unsigned int` to
a `uint8_t`. This variable counts from 0-7 in the `bit` variant, 0-15 in the
`nibble` variant, and 0-255 in the `byte` variant.

When I profiled these changes, it made *no difference* on the 32-bit processors
on any algorithm, except for one peculiar results on the ESP32:

* ESP32
    * crc32_bit: 70% faster

But on the 8-bit processors, there was significant performance improvements
across many algorithms, with *no decrease* in performance for the other
algorithms:

* Nano and Pro Micro
    * crc8_bit: 18% faster
    * crc16ccitt_bit: 15% faster
    * crc16ccitt_nibble: 34% faster
    * crc32_bit: 15% faster
    * crc32_nibble: 18% faster
    * crc32_byte: 6% faster

### v0.3.2

I added the performance benchmarks for a number of third-party CRC libraries
just out of curiosity:

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

## Arduino Nano

* 16MHz ATmega328P
* Arduino IDE 1.8.13
* Arduino AVR Boards 1.8.3

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |        9306 |
| crc8_nibble                     |        7346 |
| crc8_byte                       |         908 |
| crc16ccitt_bit                  |       11106 |
| crc16ccitt_nibble               |        5290 |
| crc16ccitt_byte                 |        1490 |
| crc32_bit                       |       16062 |
| crc32_nibble                    |        7610 |
| crc32_byte                      |        2262 |
|---------------------------------+-------------|
| CRC32                           |        7674 |
| Arduino_CRC32                   |        2134 |
| FastCRC32                       |        2130 |
+---------------------------------+-------------+

```

## Sparkfun Pro Micro

* 16 MHz ATmega32U4
* Arduino IDE 1.8.13
* SparkFun AVR Boards 1.1.13

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |        9352 |
| crc8_nibble                     |        7388 |
| crc8_byte                       |         914 |
| crc16ccitt_bit                  |       11164 |
| crc16ccitt_nibble               |        5316 |
| crc16ccitt_byte                 |        1500 |
| crc32_bit                       |       16148 |
| crc32_nibble                    |        7648 |
| crc32_byte                      |        2272 |
|---------------------------------+-------------|
| CRC32                           |        7716 |
| Arduino_CRC32                   |        2148 |
| FastCRC32                       |        2130 |
+---------------------------------+-------------+

```

## SAMD21 M0 Mini

* 48 MHz ARM Cortex-M0+
* Arduino IDE 1.8.13
* Arduino SAMD Core 1.8.6

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |        2746 |
| crc8_nibble                     |         630 |
| crc8_byte                       |         286 |
| crc16ccitt_bit                  |        2831 |
| crc16ccitt_nibble               |         703 |
| crc16ccitt_byte                 |         398 |
| crc32_bit                       |        2837 |
| crc32_nibble                    |         652 |
| crc32_byte                      |         380 |
|---------------------------------+-------------|
| CRC32                           |        1269 |
| Arduino_CRC32                   |         381 |
| FastCRC32                       |         347 |
+---------------------------------+-------------+

```

## STM32 Blue Pill

* STM32F103C8, 72 MHz ARM Cortex-M3
* Arduino IDE 1.8.13
* STM32duino 1.9.0

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |        2276 |
| crc8_nibble                     |         502 |
| crc8_byte                       |         259 |
| crc16ccitt_bit                  |        1989 |
| crc16ccitt_nibble               |         559 |
| crc16ccitt_byte                 |         259 |
| crc32_bit                       |        2245 |
| crc32_nibble                    |         559 |
| crc32_byte                      |         245 |
|---------------------------------+-------------|
| CRC32                           |         831 |
| Arduino_CRC32                   |         316 |
| FastCRC32                       |         181 |
+---------------------------------+-------------+

```

## ESP8266

* NodeMCU 1.0, 80MHz ESP8266
* Arduino IDE 1.8.13
* ESP8266 Boards 2.7.4

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |        1499 |
| crc8_nibble                     |         488 |
| crc8_byte                       |         233 |
| crc16ccitt_bit                  |        1501 |
| crc16ccitt_nibble               |         681 |
| crc16ccitt_byte                 |         364 |
| crc32_bit                       |        1401 |
| crc32_nibble                    |         617 |
| crc32_byte                      |         342 |
|---------------------------------+-------------|
| CRC32                           |         937 |
| Arduino_CRC32                   |         143 |
| FastCRC32                       |         486 |
+---------------------------------+-------------+

```

## ESP32

* ESP32-01 Dev Board, 240 MHz Tensilica LX6
* Arduino IDE 1.8.13
* ESP32 Boards 1.0.4

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |         498 |
| crc8_nibble                     |         118 |
| crc8_byte                       |          53 |
| crc16ccitt_bit                  |         498 |
| crc16ccitt_nibble               |         125 |
| crc16ccitt_byte                 |          75 |
| crc32_bit                       |         396 |
| crc32_nibble                    |         108 |
| crc32_byte                      |          71 |
|---------------------------------+-------------|
| CRC32                           |         189 |
| Arduino_CRC32                   |          72 |
| FastCRC32                       |          40 |
+---------------------------------+-------------+

```

## Teensy 3.2

* 96 MHz ARM Cortex-M4
* Arduino IDE 1.8.13
* Teensyduino 1.53
* Compiler options: "Faster"

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |        1134 |
| crc8_nibble                     |         194 |
| crc8_byte                       |          92 |
| crc16ccitt_bit                  |        1176 |
| crc16ccitt_nibble               |         193 |
| crc16ccitt_byte                 |         141 |
| crc32_bit                       |        1392 |
| crc32_nibble                    |         183 |
| crc32_byte                      |         154 |
|---------------------------------+-------------|
| CRC32                           |         429 |
| Arduino_CRC32                   |         156 |
| FastCRC32                       |          23 |
+---------------------------------+-------------+

```

