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

**Version**: AceCRC v1.1.0

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

## Algorithms

* 0 Baseline: A program that does (almost) nothing
* 1 `crc8_bit`
* 2 `crc8_nibble`
* 3 `crc8_nibblem`
* 4 `crc8_byte`
* 5 `crc16ccitt_bit`
* 6 `crc16ccitt_nibble`
* 7 `crc16ccitt_nibblem`
* 8 `crc16ccitt_byte`
* 9 `crc16modbus_bit`
* 10 `crc16modbus_nibble`
* 11 `crc16modbus_nibblem`
* 12 `crc16modbus_byte`
* 13 `crc32_bit`
* 14 `crc32_nibble`
* 15 `crc32_nibblem`
* 16 `crc32_byte`
* 17 - CRC32 library (https://github.com/arduino-libraries/Arduino_CRC32)
* 18 - Arduino_CRC32 library (https://github.com/bakercp/CRC32)
* 19 - FastCRC library (https://github.com/FrankBoesing/FastCRC)

## Library Size Changes

**v1.0**

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

The `nibblem` variant is exactly the same as the `nibble` variant, except that
`PROGMEM` keyword is not used for the lookup `crc_table`, so that it is placed
in static memory instead of flash memory. This improves the speed of the
algorithm on AVR and ESP8266 processors because accessing static memory is
faster than flash memory on those processors.

**v1.1.0**

* Upgrade tool chain
* Remove SAMD21 board which I can no longer test.
* Add CRC-16-MODBUS algorithm.

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
| functionality                   |  flash/  ram |       delta |
|---------------------------------+--------------+-------------|
| baseline                        |    684/   21 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc8_bit                        |    748/   21 |    64/    0 |
| crc8_nibble                     |    814/   21 |   130/    0 |
| crc8_nibblem                    |    818/   37 |   134/   16 |
| crc8_byte                       |    976/   21 |   292/    0 |
|---------------------------------+--------------+-------------|
| crc16ccitt_bit                  |    768/   21 |    84/    0 |
| crc16ccitt_nibble               |    818/   21 |   134/    0 |
| crc16ccitt_nibblem              |    822/   53 |   138/   32 |
| crc16ccitt_byte                 |   1246/   21 |   562/    0 |
|---------------------------------+--------------+-------------|
| crc16modbus_bit                 |    804/   21 |   120/    0 |
| crc16modbus_nibble              |    816/   21 |   132/    0 |
| crc16modbus_nibblem             |    818/   53 |   134/   32 |
| crc16modbus_byte                |   1246/   21 |   562/    0 |
|---------------------------------+--------------+-------------|
| crc32_bit                       |    872/   21 |   188/    0 |
| crc32_nibble                    |    888/   21 |   204/    0 |
| crc32_nibblem                   |    892/   85 |   208/   64 |
| crc32_byte                      |   1790/   21 |  1106/    0 |
|---------------------------------+--------------+-------------|
| CRC32                           |    892/   21 |   208/    0 |
| Arduino_CRC32                   |   1796/ 1045 |  1112/ 1024 |
| FastCRC                         |   4946/   21 |  4262/    0 |
+--------------------------------------------------------------+

```

### SparkFun Pro Micro

* 16 MHz ATmega32U4
* Arduino IDE 1.8.19
* SparkFun AVR Boards 1.1.13

```
+--------------------------------------------------------------+
| functionality                   |  flash/  ram |       delta |
|---------------------------------+--------------+-------------|
| baseline                        |   3610/  161 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc8_bit                        |   3674/  161 |    64/    0 |
| crc8_nibble                     |   3740/  161 |   130/    0 |
| crc8_nibblem                    |   3744/  177 |   134/   16 |
| crc8_byte                       |   3902/  161 |   292/    0 |
|---------------------------------+--------------+-------------|
| crc16ccitt_bit                  |   3694/  161 |    84/    0 |
| crc16ccitt_nibble               |   3744/  161 |   134/    0 |
| crc16ccitt_nibblem              |   3748/  193 |   138/   32 |
| crc16ccitt_byte                 |   4172/  161 |   562/    0 |
|---------------------------------+--------------+-------------|
| crc16modbus_bit                 |   3730/  161 |   120/    0 |
| crc16modbus_nibble              |   3742/  161 |   132/    0 |
| crc16modbus_nibblem             |   3744/  193 |   134/   32 |
| crc16modbus_byte                |   4172/  161 |   562/    0 |
|---------------------------------+--------------+-------------|
| crc32_bit                       |   3798/  161 |   188/    0 |
| crc32_nibble                    |   3814/  161 |   204/    0 |
| crc32_nibblem                   |   3818/  225 |   208/   64 |
| crc32_byte                      |   4716/  161 |  1106/    0 |
|---------------------------------+--------------+-------------|
| CRC32                           |   3818/  161 |   208/    0 |
| Arduino_CRC32                   |   4722/ 1185 |  1112/ 1024 |
| FastCRC                         |   7872/  161 |  4262/    0 |
+--------------------------------------------------------------+

```

### STM32 Blue Pill

* STM32F103C8, 72 MHz ARM Cortex-M3
* Arduino IDE 1.8.19
* STM32duino 2.4.0

```
+--------------------------------------------------------------+
| functionality                   |  flash/  ram |       delta |
|---------------------------------+--------------+-------------|
| baseline                        |  21436/ 3556 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc8_bit                        |  21504/ 3556 |    68/    0 |
| crc8_nibble                     |  21516/ 3556 |    80/    0 |
| crc8_nibblem                    |  21516/ 3556 |    80/    0 |
| crc8_byte                       |  21732/ 3556 |   296/    0 |
|---------------------------------+--------------+-------------|
| crc16ccitt_bit                  |  21520/ 3556 |    84/    0 |
| crc16ccitt_nibble               |  21540/ 3556 |   104/    0 |
| crc16ccitt_nibblem              |  21540/ 3556 |   104/    0 |
| crc16ccitt_byte                 |  22000/ 3556 |   564/    0 |
|---------------------------------+--------------+-------------|
| crc16modbus_bit                 |  21556/ 3556 |   120/    0 |
| crc16modbus_nibble              |  21540/ 3556 |   104/    0 |
| crc16modbus_nibblem             |  21540/ 3556 |   104/    0 |
| crc16modbus_byte                |  22000/ 3556 |   564/    0 |
|---------------------------------+--------------+-------------|
| crc32_bit                       |  21552/ 3556 |   116/    0 |
| crc32_nibble                    |  21576/ 3556 |   140/    0 |
| crc32_nibblem                   |  21576/ 3556 |   140/    0 |
| crc32_byte                      |  22516/ 3556 |  1080/    0 |
|---------------------------------+--------------+-------------|
| CRC32                           |  21604/ 3556 |   168/    0 |
| Arduino_CRC32                   |  22532/ 3556 |  1096/    0 |
| FastCRC                         |  25924/ 3556 |  4488/    0 |
+--------------------------------------------------------------+

```

### ESP8266

* NodeMCU 1.0, 80MHz ESP8266
* Arduino IDE 1.8.19
* ESP8266 Boards 3.0.2

```
+--------------------------------------------------------------+
| functionality                   |  flash/  ram |       delta |
|---------------------------------+--------------+-------------|
| baseline                        | 260389/27936 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc8_bit                        | 260517/27936 |   128/    0 |
| crc8_nibble                     | 260533/27936 |   144/    0 |
| crc8_nibblem                    | 260501/27952 |   112/   16 |
| crc8_byte                       | 260725/27936 |   336/    0 |
|---------------------------------+--------------+-------------|
| crc16ccitt_bit                  | 260517/27936 |   128/    0 |
| crc16ccitt_nibble               | 260549/27936 |   160/    0 |
| crc16ccitt_nibblem              | 260533/27968 |   144/   32 |
| crc16ccitt_byte                 | 260997/27936 |   608/    0 |
|---------------------------------+--------------+-------------|
| crc16modbus_bit                 | 260549/27936 |   160/    0 |
| crc16modbus_nibble              | 260549/27936 |   160/    0 |
| crc16modbus_nibblem             | 260517/27968 |   128/   32 |
| crc16modbus_byte                | 260997/27936 |   608/    0 |
|---------------------------------+--------------+-------------|
| crc32_bit                       | 260533/27936 |   144/    0 |
| crc32_nibble                    | 260565/27936 |   176/    0 |
| crc32_nibblem                   | 260549/28000 |   160/   64 |
| crc32_byte                      | 261493/27936 |  1104/    0 |
|---------------------------------+--------------+-------------|
| CRC32                           | 260613/27936 |   224/    0 |
| Arduino_CRC32                   | 261509/28960 |  1120/ 1024 |
| FastCRC                         | 265093/27936 |  4704/    0 |
+--------------------------------------------------------------+

```

### ESP32

* ESP32-01 Dev Board, 240 MHz Tensilica LX6
* Arduino IDE 1.8.19
* ESP32 Boards 2.0.5

```
+--------------------------------------------------------------+
| functionality                   |  flash/  ram |       delta |
|---------------------------------+--------------+-------------|
| baseline                        | 211169/16056 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc8_bit                        | 211313/16056 |   144/    0 |
| crc8_nibble                     | 211321/16056 |   152/    0 |
| crc8_nibblem                    | 211321/16056 |   152/    0 |
| crc8_byte                       | 211525/16056 |   356/    0 |
|---------------------------------+--------------+-------------|
| crc16ccitt_bit                  | 211321/16056 |   152/    0 |
| crc16ccitt_nibble               | 211349/16056 |   180/    0 |
| crc16ccitt_nibblem              | 211349/16056 |   180/    0 |
| crc16ccitt_byte                 | 211801/16056 |   632/    0 |
|---------------------------------+--------------+-------------|
| crc16modbus_bit                 | 211365/16056 |   196/    0 |
| crc16modbus_nibble              | 211341/16056 |   172/    0 |
| crc16modbus_nibblem             | 211341/16056 |   172/    0 |
| crc16modbus_byte                | 211793/16056 |   624/    0 |
|---------------------------------+--------------+-------------|
| crc32_bit                       | 211345/16056 |   176/    0 |
| crc32_nibble                    | 211369/16056 |   200/    0 |
| crc32_nibblem                   | 211369/16056 |   200/    0 |
| crc32_byte                      | 212305/16056 |  1136/    0 |
|---------------------------------+--------------+-------------|
| CRC32                           | 211409/16056 |   240/    0 |
| Arduino_CRC32                   | 212361/16056 |  1192/    0 |
| FastCRC                         | 215781/16056 |  4612/    0 |
+--------------------------------------------------------------+

```

### Teensy 3.2

* 96 MHz ARM Cortex-M4
* Arduino IDE 1.8.19
* Teensyduino 1.57
* Compiler options: "Faster"

```
+--------------------------------------------------------------+
| functionality                   |  flash/  ram |       delta |
|---------------------------------+--------------+-------------|
| baseline                        |   7032/ 3048 |     0/    0 |
|---------------------------------+--------------+-------------|
| crc8_bit                        |   7108/ 3048 |    76/    0 |
| crc8_nibble                     |   7120/ 3048 |    88/    0 |
| crc8_nibblem                    |   7120/ 3048 |    88/    0 |
| crc8_byte                       |   7332/ 3048 |   300/    0 |
|---------------------------------+--------------+-------------|
| crc16ccitt_bit                  |   7120/ 3048 |    88/    0 |
| crc16ccitt_nibble               |   7144/ 3048 |   112/    0 |
| crc16ccitt_nibblem              |   7144/ 3048 |   112/    0 |
| crc16ccitt_byte                 |   7604/ 3048 |   572/    0 |
|---------------------------------+--------------+-------------|
| crc16modbus_bit                 |   7168/ 3048 |   136/    0 |
| crc16modbus_nibble              |   7148/ 3048 |   116/    0 |
| crc16modbus_nibblem             |   7148/ 3048 |   116/    0 |
| crc16modbus_byte                |   7600/ 3048 |   568/    0 |
|---------------------------------+--------------+-------------|
| crc32_bit                       |   7168/ 3048 |   136/    0 |
| crc32_nibble                    |   7172/ 3048 |   140/    0 |
| crc32_nibblem                   |   7172/ 3048 |   140/    0 |
| crc32_byte                      |   8112/ 3048 |  1080/    0 |
|---------------------------------+--------------+-------------|
| CRC32                           |   7208/ 3048 |   176/    0 |
| Arduino_CRC32                   |   8128/ 3048 |  1096/    0 |
| FastCRC                         |   7204/ 3048 |   172/    0 |
+--------------------------------------------------------------+

```

