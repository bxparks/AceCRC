# CPU Benchmark

The `CPUBenchmark.ino` determines the CPU run time of each of various CRC
algorithms.

**Version**: AceCRC v0.2

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
1024 characters (i.e. micros/kiB).

## CPU Time Changes

## Arduino Nano

* 16MHz ATmega328P
* Arduino IDE 1.8.13
* Arduino AVR Boards 1.8.3

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc16ccitt_bit                  |       12772 |
| crc16ccitt_nibble               |        7086 |
| crc16ccitt_byte                 |        1549 |
| crc32_bit                       |       18379 |
| crc32_nibble                    |        8956 |
| crc32_byte                      |        2388 |
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
| crc16ccitt_bit                  |       12839 |
| crc16ccitt_nibble               |        7124 |
| crc16ccitt_byte                 |        1557 |
| crc32_bit                       |       18489 |
| crc32_nibble                    |        9003 |
| crc32_byte                      |        2401 |
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
| crc16ccitt_bit                  |        2942 |
| crc16ccitt_nibble               |         675 |
| crc16ccitt_byte                 |         446 |
| crc32_bit                       |        2946 |
| crc32_nibble                    |         637 |
| crc32_byte                      |         380 |
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
| crc16ccitt_bit                  |        1307 |
| crc16ccitt_nibble               |         668 |
| crc16ccitt_byte                 |         366 |
| crc32_bit                       |        1388 |
| crc32_nibble                    |         617 |
| crc32_byte                      |         342 |
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
| crc16ccitt_bit                  |         504 |
| crc16ccitt_nibble               |         109 |
| crc16ccitt_byte                 |          76 |
| crc32_bit                       |         671 |
| crc32_nibble                    |         109 |
| crc32_byte                      |          71 |
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

