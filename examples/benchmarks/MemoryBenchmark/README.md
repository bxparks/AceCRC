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

**Version**: AceCRC v0.4.1

**DO NOT EDIT**: This file was auto-generated using `make README.md`.

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
stm32.txt
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
* 1 `crc8_bit`
* 2 `crc8_nibble`
* 3 `crc8_byte`
* 4 `crc16ccitt_bit`
* 5 `crc16ccitt_nibble`
* 6 `crc16ccitt_byte`
* 7 `crc32_bit`
* 8 `crc32_nibble`
* 9 `crc32_byte`

## Library Size Changes

The size of the `crc_table` lookup table is:

* CRC8 using 'nibble' variant: 16 * 1 = 16 bytes
* CRC8 using 'byte' variant: 256 * 1 = 256 bytes
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
| crc8_bit                        |    756/   21 |    72/    0 |
| crc8_nibble                     |    814/   21 |   130/    0 |
| crc8_byte                       |    976/   21 |   292/    0 |
| crc16ccitt_bit                  |    764/   21 |    80/    0 |
| crc16ccitt_nibble               |    818/   21 |   134/    0 |
| crc16ccitt_byte                 |   1246/   21 |   562/    0 |
| crc32_bit                       |    868/   21 |   184/    0 |
| crc32_nibble                    |    888/   21 |   204/    0 |
| crc32_byte                      |   1790/   21 |  1106/    0 |
|---------------------------------+--------------+-------------|
| CRC32                           |    892/   21 |   208/    0 |
| Arduino_CRC32                   |   1796/ 1045 |  1112/ 1024 |
| FastCRC                         |   4946/   21 |  4262/    0 |
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
| crc8_bit                        |   3682/  161 |    72/    0 |
| crc8_nibble                     |   3740/  161 |   130/    0 |
| crc8_byte                       |   3902/  161 |   292/    0 |
| crc16ccitt_bit                  |   3690/  161 |    80/    0 |
| crc16ccitt_nibble               |   3744/  161 |   134/    0 |
| crc16ccitt_byte                 |   4172/  161 |   562/    0 |
| crc32_bit                       |   3794/  161 |   184/    0 |
| crc32_nibble                    |   3814/  161 |   204/    0 |
| crc32_byte                      |   4716/  161 |  1106/    0 |
|---------------------------------+--------------+-------------|
| CRC32                           |   3818/  161 |   208/    0 |
| Arduino_CRC32                   |   4722/ 1185 |  1112/ 1024 |
| FastCRC                         |   7872/  161 |  4262/    0 |
+--------------------------------------------------------------+

```

## SAMD21 M0 Mini

* 48 MHz ARM Cortex-M0+
* Arduino IDE 1.8.13
* Sparkfun SAMD Core 1.8.1

```
+--------------------------------------------------------------+
| functionality                   |  flash/  ram |       delta |
|---------------------------------+--------------+-------------|
| baseline                        |  10112/    0 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc8_bit                        |  10176/    0 |    64/    0 |
| crc8_nibble                     |  10192/    0 |    80/    0 |
| crc8_byte                       |  10408/    0 |   296/    0 |
| crc16ccitt_bit                  |  10184/    0 |    72/    0 |
| crc16ccitt_nibble               |  10216/    0 |   104/    0 |
| crc16ccitt_byte                 |  10680/    0 |   568/    0 |
| crc32_bit                       |  10224/    0 |   112/    0 |
| crc32_nibble                    |  10248/    0 |   136/    0 |
| crc32_byte                      |  11192/    0 |  1080/    0 |
|---------------------------------+--------------+-------------|
| CRC32                           |  10280/    0 |   168/    0 |
| Arduino_CRC32                   |  11200/    0 |  1088/    0 |
| FastCRC                         |  14648/    0 |  4536/    0 |
+--------------------------------------------------------------+

```

## STM32 Blue Pill

* STM32F103C8, 72 MHz ARM Cortex-M3
* Arduino IDE 1.8.13
* STM32duino 1.9.0

```
+--------------------------------------------------------------+
| functionality                   |  flash/  ram |       delta |
|---------------------------------+--------------+-------------|
| baseline                        |  19176/ 3788 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc8_bit                        |  19236/ 3788 |    60/    0 |
| crc8_nibble                     |  19256/ 3788 |    80/    0 |
| crc8_byte                       |  19472/ 3788 |   296/    0 |
| crc16ccitt_bit                  |  19244/ 3788 |    68/    0 |
| crc16ccitt_nibble               |  19280/ 3788 |   104/    0 |
| crc16ccitt_byte                 |  19740/ 3788 |   564/    0 |
| crc32_bit                       |  19284/ 3788 |   108/    0 |
| crc32_nibble                    |  19316/ 3788 |   140/    0 |
| crc32_byte                      |  20256/ 3788 |  1080/    0 |
|---------------------------------+--------------+-------------|
| CRC32                           |  19348/ 3788 |   172/    0 |
| Arduino_CRC32                   |  20272/ 3788 |  1096/    0 |
| FastCRC                         |  23668/ 3788 |  4492/    0 |
+--------------------------------------------------------------+

```

## ESP8266

* NodeMCU 1.0, 80MHz ESP8266
* Arduino IDE 1.8.13
* ESP8266 Boards 2.7.4

```
+--------------------------------------------------------------+
| functionality                   |  flash/  ram |       delta |
|---------------------------------+--------------+-------------|
| baseline                        | 256984/26812 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc8_bit                        | 257080/26812 |    96/    0 |
| crc8_nibble                     | 257128/26812 |   144/    0 |
| crc8_byte                       | 257320/26812 |   336/    0 |
| crc16ccitt_bit                  | 257096/26812 |   112/    0 |
| crc16ccitt_nibble               | 257176/26812 |   192/    0 |
| crc16ccitt_byte                 | 257608/26812 |   624/    0 |
| crc32_bit                       | 257128/26812 |   144/    0 |
| crc32_nibble                    | 257192/26812 |   208/    0 |
| crc32_byte                      | 258120/26812 |  1136/    0 |
|---------------------------------+--------------+-------------|
| CRC32                           | 257224/26812 |   240/    0 |
| Arduino_CRC32                   | 258120/27836 |  1136/ 1024 |
| FastCRC                         | 261704/26812 |  4720/    0 |
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
| crc8_bit                        | 206809/14564 |   132/    0 |
| crc8_nibble                     | 206829/14564 |   152/    0 |
| crc8_byte                       | 207033/14564 |   356/    0 |
| crc16ccitt_bit                  | 206817/14564 |   140/    0 |
| crc16ccitt_nibble               | 206853/14564 |   176/    0 |
| crc16ccitt_byte                 | 207309/14564 |   632/    0 |
| crc32_bit                       | 206845/14564 |   168/    0 |
| crc32_nibble                    | 206877/14564 |   200/    0 |
| crc32_byte                      | 207817/14564 |  1140/    0 |
|---------------------------------+--------------+-------------|
| CRC32                           | 206949/14572 |   272/    8 |
| Arduino_CRC32                   | 207873/14564 |  1196/    0 |
| FastCRC                         | 211317/14580 |  4640/   16 |
+--------------------------------------------------------------+

```

## Teensy 3.2

* 96 MHz ARM Cortex-M4
* Arduino IDE 1.8.13
* Teensyduino 1.53
* Compiler options: "Faster"

```
+--------------------------------------------------------------+
| functionality                   |  flash/  ram |       delta |
|---------------------------------+--------------+-------------|
| baseline                        |   7696/ 3048 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc8_bit                        |   7764/ 3048 |    68/    0 |
| crc8_nibble                     |   7784/ 3048 |    88/    0 |
| crc8_byte                       |   7996/ 3048 |   300/    0 |
| crc16ccitt_bit                  |   7772/ 3048 |    76/    0 |
| crc16ccitt_nibble               |   7808/ 3048 |   112/    0 |
| crc16ccitt_byte                 |   8268/ 3048 |   572/    0 |
| crc32_bit                       |   7828/ 3048 |   132/    0 |
| crc32_nibble                    |   7836/ 3048 |   140/    0 |
| crc32_byte                      |   8776/ 3048 |  1080/    0 |
|---------------------------------+--------------+-------------|
| CRC32                           |   7872/ 3048 |   176/    0 |
| Arduino_CRC32                   |   8792/ 3048 |  1096/    0 |
| FastCRC                         |   7868/ 3048 |   172/    0 |
+--------------------------------------------------------------+

```

