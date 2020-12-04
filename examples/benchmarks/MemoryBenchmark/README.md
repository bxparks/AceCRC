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

**Version**: AceCRC v0.2

**NOTE**: This file was auto-generated using `make README.md`. DO NOT EDIT.

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
samd.txt
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

## Functionality

* 0 Baseline: A program that does (almost) nothing
* 1 `crc16ccitt_bit`
* 2 `crc16ccitt_nibble`
* 3 `crc16ccitt_byte`
* 4 `crc32_bit`
* 5 `crc32_nibble`
* 6 `crc32_byte`

## Library Size Changes

The size of the `crc_table` lookup table is:

* CRC16 using 'nibble' variant: 16 * 2 = 32 bytes
* CRC16 using 'byte' variant: 256 * 2 = 512 bytes
* CRC32  using 'nibble' variant: 16 * 4 = 64 bytes
* CRC32 using 'byte' variant: 256 * 4 = 1024 bytes

These are moved from static RAM to flash memory with the `PROGMEM` directive on
certain microcontrollers (e.g. AVR, ESP8266), For the other processors, either
the `crc_table` is already in flash memory, or the `PROGMEM` attribute does not
do anything.

## Arduino Nano

* 16MHz ATmega328P
* Arduino IDE 1.8.13
* Arduino AVR Boards 1.8.3

```
+--------------------------------------------------------------+
| functionality                   |  flash/  ram |       delta |
|---------------------------------+--------------+-------------|
| baseline                        |    684/   21 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc16ccitt_bit                  |    774/   21 |    90/    0 |
| crc16ccitt_nibble               |    842/   21 |   158/    0 |
| crc16ccitt_byte                 |   1248/   21 |   564/    0 |
| crc32_bit                       |    876/   21 |   192/    0 |
| crc32_nibble                    |    904/   21 |   220/    0 |
| crc32_byte                      |   1790/   21 |  1106/    0 |
+--------------------------------------------------------------+

```

## Sparkfun Pro Micro

* 16 MHz ATmega32U4
* Arduino IDE 1.8.13
* SparkFun AVR Boards 1.1.13

```
+--------------------------------------------------------------+
| functionality                   |  flash/  ram |       delta |
|---------------------------------+--------------+-------------|
| baseline                        |   3610/  161 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc16ccitt_bit                  |   3700/  161 |    90/    0 |
| crc16ccitt_nibble               |   3768/  161 |   158/    0 |
| crc16ccitt_byte                 |   4174/  161 |   564/    0 |
| crc32_bit                       |   3802/  161 |   192/    0 |
| crc32_nibble                    |   3830/  161 |   220/    0 |
| crc32_byte                      |   4716/  161 |  1106/    0 |
+--------------------------------------------------------------+

```

## SAMD21 M0 Mini

* 48 MHz ARM Cortex-M0+
* Arduino IDE 1.8.13
* Arduino SAMD Core 1.8.6

```
+--------------------------------------------------------------+
| functionality                   |  flash/  ram |       delta |
|---------------------------------+--------------+-------------|
| baseline                        |  10112/    0 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc16ccitt_bit                  |  10184/    0 |    72/    0 |
| crc16ccitt_nibble               |  10216/    0 |   104/    0 |
| crc16ccitt_byte                 |  10680/    0 |   568/    0 |
| crc32_bit                       |  10224/    0 |   112/    0 |
| crc32_nibble                    |  10248/    0 |   136/    0 |
| crc32_byte                      |  11192/    0 |  1080/    0 |
+--------------------------------------------------------------+

```

## ESP8266

* NodeMCU 1.0 clone, 80MHz ESP8266
* Arduino IDE 1.8.13
* ESP8266 Boards 2.7.1

```
+--------------------------------------------------------------+
| functionality                   |  flash/  ram |       delta |
|---------------------------------+--------------+-------------|
| baseline                        | 256984/26812 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc16ccitt_bit                  | 257096/26812 |   112/    0 |
| crc16ccitt_nibble               | 257176/26812 |   192/    0 |
| crc16ccitt_byte                 | 257608/26812 |   624/    0 |
| crc32_bit                       | 257128/26812 |   144/    0 |
| crc32_nibble                    | 257192/26812 |   208/    0 |
| crc32_byte                      | 258120/26812 |  1136/    0 |
+--------------------------------------------------------------+

```

## ESP32

* ESP32-01 Dev Board, 240 MHz Tensilica LX6
* Arduino IDE 1.8.13
* ESP32 Boards 1.0.4

```
+--------------------------------------------------------------+
| functionality                   |  flash/  ram |       delta |
|---------------------------------+--------------+-------------|
| baseline                        | 206677/14564 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc16ccitt_bit                  | 206817/14564 |   140/    0 |
| crc16ccitt_nibble               | 206853/14564 |   176/    0 |
| crc16ccitt_byte                 | 207309/14564 |   632/    0 |
| crc32_bit                       | 206845/14564 |   168/    0 |
| crc32_nibble                    | 206877/14564 |   200/    0 |
| crc32_byte                      | 207817/14564 |  1140/    0 |
+--------------------------------------------------------------+

```

## Teensy 3.2

* 96 MHz ARM Cortex-M4
* Arduino IDE 1.8.13
* Teensyduino 1.53.beta
* Compiler options: "Faster"

```
+--------------------------------------------------------------+
| functionality                   |  flash/  ram |       delta |
|---------------------------------+--------------+-------------|
| baseline                        |   7696/ 3048 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc16ccitt_bit                  |   7772/ 3048 |    76/    0 |
| crc16ccitt_nibble               |   7808/ 3048 |   112/    0 |
| crc16ccitt_byte                 |   8268/ 3048 |   572/    0 |
| crc32_bit                       |   7820/ 3048 |   124/    0 |
| crc32_nibble                    |   7836/ 3048 |   140/    0 |
| crc32_byte                      |   8776/ 3048 |  1080/    0 |
+--------------------------------------------------------------+

```

