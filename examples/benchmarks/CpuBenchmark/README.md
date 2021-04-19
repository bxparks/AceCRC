# CPU Benchmark

The `CPUBenchmark.ino` determines the CPU run time of each of various CRC
algorithms.

**Version**: AceCRC v1.0.1

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

### v1.0

Added CPU benchmarks for the `nibblem` variant. On AVR and ESP8266, there was
some performance increase compared to the `nibble` variant, because static
memory access is faster than flash memory access on those processors. On other
microcontrollers, there was no change in performance.

* AVR
    * crc8_nibblem is 2% faster than crc8_nibble
    * crc16ccitt_nibblem is 5% faster than crc16ccitt_nibble
    * crc32_nibblem is 7% faster than crc32_nibble
* ESP8266
    * crc8_nibblem is 1.9X faster than crc8_nibble
    * crc16ccitt_nibblem is 2.5X faster than crc16ccitt_nibble
    * crc32_nibblem is 2.7X faster than crc32_nibble

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
| crc8_bit                        |        9312 |
| crc8_nibble                     |        7352 |
| crc8_nibblem                    |        7228 |
| crc8_byte                       |         920 |
| crc16ccitt_bit                  |       11096 |
| crc16ccitt_nibble               |        5296 |
| crc16ccitt_nibblem              |        5036 |
| crc16ccitt_byte                 |        1496 |
| crc32_bit                       |       16164 |
| crc32_nibble                    |        7624 |
| crc32_nibblem                   |        7104 |
| crc32_byte                      |        2276 |
|---------------------------------+-------------|
| CRC32                           |        7688 |
| Arduino_CRC32                   |        2144 |
| FastCRC32                       |        2160 |
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
| crc8_bit                        |        9372 |
| crc8_nibble                     |        7392 |
| crc8_nibblem                    |        7272 |
| crc8_byte                       |         928 |
| crc16ccitt_bit                  |       11156 |
| crc16ccitt_nibble               |        5316 |
| crc16ccitt_nibblem              |        5068 |
| crc16ccitt_byte                 |        1504 |
| crc32_bit                       |       16248 |
| crc32_nibble                    |        7660 |
| crc32_nibblem                   |        7144 |
| crc32_byte                      |        2284 |
|---------------------------------+-------------|
| CRC32                           |        7720 |
| Arduino_CRC32                   |        2160 |
| FastCRC32                       |        2180 |
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
| crc8_nibble                     |         625 |
| crc8_nibblem                    |         625 |
| crc8_byte                       |         295 |
| crc16ccitt_bit                  |        2831 |
| crc16ccitt_nibble               |         676 |
| crc16ccitt_nibblem              |         706 |
| crc16ccitt_byte                 |         399 |
| crc32_bit                       |        2838 |
| crc32_nibble                    |         652 |
| crc32_nibblem                   |         636 |
| crc32_byte                      |         380 |
|---------------------------------+-------------|
| CRC32                           |        1266 |
| Arduino_CRC32                   |         380 |
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
| crc8_bit                        |        1982 |
| crc8_nibble                     |         459 |
| crc8_nibblem                    |         517 |
| crc8_byte                       |         245 |
| crc16ccitt_bit                  |        2039 |
| crc16ccitt_nibble               |         573 |
| crc16ccitt_nibblem              |         559 |
| crc16ccitt_byte                 |         302 |
| crc32_bit                       |        2245 |
| crc32_nibble                    |         559 |
| crc32_nibblem                   |         574 |
| crc32_byte                      |         244 |
|---------------------------------+-------------|
| CRC32                           |         931 |
| Arduino_CRC32                   |         316 |
| FastCRC32                       |         183 |
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
| crc8_bit                        |        1500 |
| crc8_nibble                     |         490 |
| crc8_nibblem                    |         257 |
| crc8_byte                       |         233 |
| crc16ccitt_bit                  |        1499 |
| crc16ccitt_nibble               |         681 |
| crc16ccitt_nibblem              |         270 |
| crc16ccitt_byte                 |         363 |
| crc32_bit                       |        1400 |
| crc32_nibble                    |         618 |
| crc32_nibblem                   |         232 |
| crc32_byte                      |         345 |
|---------------------------------+-------------|
| CRC32                           |         950 |
| Arduino_CRC32                   |         142 |
| FastCRC32                       |         486 |
+---------------------------------+-------------+

```

## ESP32

* ESP32-01 Dev Board, 240 MHz Tensilica LX6
* Arduino IDE 1.8.13
* ESP32 Boards 1.0.6

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |         498 |
| crc8_nibble                     |         117 |
| crc8_nibblem                    |         117 |
| crc8_byte                       |          53 |
| crc16ccitt_bit                  |         498 |
| crc16ccitt_nibble               |         125 |
| crc16ccitt_nibblem              |         125 |
| crc16ccitt_byte                 |          75 |
| crc32_bit                       |         397 |
| crc32_nibble                    |         109 |
| crc32_nibblem                   |         108 |
| crc32_byte                      |          71 |
|---------------------------------+-------------|
| CRC32                           |         188 |
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
| crc8_bit                        |        1133 |
| crc8_nibble                     |         193 |
| crc8_nibblem                    |         193 |
| crc8_byte                       |          92 |
| crc16ccitt_bit                  |        1176 |
| crc16ccitt_nibble               |         193 |
| crc16ccitt_nibblem              |         193 |
| crc16ccitt_byte                 |         140 |
| crc32_bit                       |        1393 |
| crc32_nibble                    |         183 |
| crc32_nibblem                   |         183 |
| crc32_byte                      |         155 |
|---------------------------------+-------------|
| CRC32                           |         429 |
| Arduino_CRC32                   |         155 |
| FastCRC32                       |          23 |
+---------------------------------+-------------+

```

