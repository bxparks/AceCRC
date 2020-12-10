# CPU Benchmark

The `CPUBenchmark.ino` determines the CPU run time of each of various CRC
algorithms.

**Version**: AceCRC v0.3.2

**NOTE**: This file was auto-generated using `make README.md`. DO NOT EDIT.

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

I included the performance benchmarks for a number of third-party CRC libraries
just out of curiosity:

* CRC32 (https://github.com/bakercp/CRC32)
    * uses a 4-bit lookup table, should be comparable to `crc32_nibble`
* Arduino_CRC32 (https://github.com/arduino-libraries/Arduino_CRC32)
    * uses an 8-bit lookup table in RAM
    * comparable to `crc32_byte` but probably faster because accessing RAM is
      often faster than `PROGMEM` on most processors
* FastCRC (https://github.com/FrankBoesing/FastCRC)
    * uses a 10-bit lookup table (1024 elements)
    * should be faster than `crc32_byte` in theory, is actually slower than
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
| crc8_bit                        |       10980 |
| crc8_nibble                     |        7216 |
| crc8_byte                       |         910 |
| crc16ccitt_bit                  |       12778 |
| crc16ccitt_nibble               |        7088 |
| crc16ccitt_byte                 |        1552 |
| crc32_bit                       |       18446 |
| crc32_nibble                    |        8964 |
| crc32_byte                      |        2394 |
|---------------------------------+-------------|
| CRC32                           |        7672 |
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
| crc8_bit                        |       11034 |
| crc8_nibble                     |        7260 |
| crc8_byte                       |         914 |
| crc16ccitt_bit                  |       12848 |
| crc16ccitt_nibble               |        7126 |
| crc16ccitt_byte                 |        1564 |
| crc32_bit                       |       18540 |
| crc32_nibble                    |        9008 |
| crc32_byte                      |        2408 |
|---------------------------------+-------------|
| CRC32                           |        7712 |
| Arduino_CRC32                   |        2144 |
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
| crc8_bit                        |        2742 |
| crc8_nibble                     |         630 |
| crc8_byte                       |         286 |
| crc16ccitt_bit                  |        2831 |
| crc16ccitt_nibble               |         702 |
| crc16ccitt_byte                 |         399 |
| crc32_bit                       |        2945 |
| crc32_nibble                    |         652 |
| crc32_byte                      |         380 |
|---------------------------------+-------------|
| CRC32                           |        1269 |
| Arduino_CRC32                   |         380 |
| FastCRC32                       |         347 |
+---------------------------------+-------------+

```

## ESP8266

* NodeMCU 1.0 clone, 80MHz ESP8266
* Arduino IDE 1.8.13
* ESP8266 Boards 2.7.1

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |        1500 |
| crc8_nibble                     |         489 |
| crc8_byte                       |         233 |
| crc16ccitt_bit                  |        1499 |
| crc16ccitt_nibble               |         681 |
| crc16ccitt_byte                 |         364 |
| crc32_bit                       |        1388 |
| crc32_nibble                    |         617 |
| crc32_byte                      |         342 |
|---------------------------------+-------------|
| CRC32                           |         940 |
| Arduino_CRC32                   |         142 |
| FastCRC32                       |         489 |
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
| crc8_nibble                     |         117 |
| crc8_byte                       |          53 |
| crc16ccitt_bit                  |         498 |
| crc16ccitt_nibble               |         125 |
| crc16ccitt_byte                 |          75 |
| crc32_bit                       |         671 |
| crc32_nibble                    |         109 |
| crc32_byte                      |          71 |
|---------------------------------+-------------|
| CRC32                           |         190 |
| Arduino_CRC32                   |          71 |
| FastCRC32                       |          40 |
+---------------------------------+-------------+

```

## Teensy 3.2

* 96 MHz ARM Cortex-M4
* Arduino IDE 1.8.13
* Teensyduino 1.53.beta
* Compiler options: "Faster"

```
TBD
```

