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

**NOTE**: This file was auto-generated using `make README.md`. DO NOT EDIT.

**Version**: AceCRC v0.1

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
* 1 crc16ccitt::bit
* 2 crc16ccitt::nibble
* 3 crc16ccitt::byte
* 4 crc32::bit
* 5 crc32::nibble
* 6 crc32::byte

## Library Size Changes

## Arduino Nano

* 16MHz ATmega328P
* Arduino IDE 1.8.13
* Arduino AVR Boards 1.8.3

```
+--------------------------------------------------------------+
| functionality                   |    flash/ram |       delta |
|---------------------------------+--------------+-------------|
| Baseline                        |    684/   21 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc16ccitt::bit                 |    774/   21 |    90/    0 |
| crc16ccitt::nibble              |    848/   53 |   164/   32 |
| crc16ccitt::byte                |   1248/  533 |   564/  512 |
| crc32::bit                      |    876/   21 |   192/    0 |
| crc32::nibble                   |    902/   85 |   218/   64 |
| crc32::byte                     |   1796/ 1045 |  1112/ 1024 |
+--------------------------------------------------------------+

```

## Sparkfun Pro Micro

* 16 MHz ATmega32U4
* Arduino IDE 1.8.13
* SparkFun AVR Boards 1.1.13

```
+--------------------------------------------------------------+
| functionality                   |    flash/ram |       delta |
|---------------------------------+--------------+-------------|
| Baseline                        |   3610/  161 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc16ccitt::bit                 |   3700/  161 |    90/    0 |
| crc16ccitt::nibble              |   3774/  193 |   164/   32 |
| crc16ccitt::byte                |   4174/  673 |   564/  512 |
| crc32::bit                      |   3802/  161 |   192/    0 |
| crc32::nibble                   |   3828/  225 |   218/   64 |
| crc32::byte                     |   4722/ 1185 |  1112/ 1024 |
+--------------------------------------------------------------+

```

## SAMD21 M0 Mini

* 48 MHz ARM Cortex-M0+
* Arduino IDE 1.8.13
* Arduino SAMD Core 1.8.6

```
+--------------------------------------------------------------+
| functionality                   |    flash/ram |       delta |
|---------------------------------+--------------+-------------|
| Baseline                        |  10112/    0 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc16ccitt::bit                 |  10192/    0 |    80/    0 |
| crc16ccitt::nibble              |  10248/    0 |   136/    0 |
| crc16ccitt::byte                |  11192/    0 |  1080/    0 |
| crc32::bit                      |  10224/    0 |   112/    0 |
| crc32::nibble                   |  10248/    0 |   136/    0 |
| crc32::byte                     |  11192/    0 |  1080/    0 |
+--------------------------------------------------------------+

```

## ESP8266

* NodeMCU 1.0 clone, 80MHz ESP8266
* Arduino IDE 1.8.13
* ESP8266 Boards 2.7.1

```
+--------------------------------------------------------------+
| functionality                   |    flash/ram |       delta |
|---------------------------------+--------------+-------------|
| Baseline                        | 256984/26812 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc16ccitt::bit                 | 257096/26812 |   112/    0 |
| crc16ccitt::nibble              | 257160/26876 |   176/   64 |
| crc16ccitt::byte                | 258104/27836 |  1120/ 1024 |
| crc32::bit                      | 257128/26812 |   144/    0 |
| crc32::nibble                   | 257144/26876 |   160/   64 |
| crc32::byte                     | 258088/27836 |  1104/ 1024 |
+--------------------------------------------------------------+

```

## ESP32

* ESP32-01 Dev Board, 240 MHz Tensilica LX6
* Arduino IDE 1.8.13
* ESP32 Boards 1.0.4

```
+--------------------------------------------------------------+
| functionality                   |    flash/ram |       delta |
|---------------------------------+--------------+-------------|
| Baseline                        | 206677/14564 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc16ccitt::bit                 | 206829/14564 |   152/    0 |
| crc16ccitt::nibble              | 206885/14564 |   208/    0 |
| crc16ccitt::byte                | 207825/14564 |  1148/    0 |
| crc32::bit                      | 206845/14564 |   168/    0 |
| crc32::nibble                   | 206877/14564 |   200/    0 |
| crc32::byte                     | 207817/14564 |  1140/    0 |
+--------------------------------------------------------------+

```

## Teensy 3.2

* 96 MHz ARM Cortex-M4
* Arduino IDE 1.8.13
* Teensyduino 1.53.beta
* Compiler options: "Faster"

```
+--------------------------------------------------------------+
| functionality                   |    flash/ram |       delta |
|---------------------------------+--------------+-------------|
| Baseline                        |   7696/ 3048 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc16ccitt::bit                 |   7788/ 3048 |    92/    0 |
| crc16ccitt::nibble              |   7844/ 3048 |   148/    0 |
| crc16ccitt::byte                |   8788/ 3048 |  1092/    0 |
| crc32::bit                      |   7820/ 3048 |   124/    0 |
| crc32::nibble                   |   7836/ 3048 |   140/    0 |
| crc32::byte                     |   8776/ 3048 |  1080/    0 |
+--------------------------------------------------------------+

```

