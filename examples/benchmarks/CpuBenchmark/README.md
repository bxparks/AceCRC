# CPU Benchmark

The `CPUBenchmark.ino` determines the CPU run time of each of various CRC
algorithms.

**Version**: AceCRC v1.1.0

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

**v0.3.2**

I added the performance benchmarks for a number of third-party CRC libraries
just out of curiosity: CRC32, Arduino_CRC32, and FastCRC (see below).

**v0.4**

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

**v1.0**

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

**v1.1.0**

* Upgrade tool chain
    * Various xxx_bit algorithms are significantly slower 10-15% on most
      platforms, don't know why.
    * Other algorithms are about the same.
* Add CRC-16-MODBUS

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
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |        7808 |
| crc8_nibble                     |        7356 |
| crc8_nibblem                    |        7224 |
| crc8_byte                       |         916 |
|---------------------------------+-------------|
| crc16ccitt_bit                  |       11888 |
| crc16ccitt_nibble               |        5296 |
| crc16ccitt_nibblem              |        5040 |
| crc16ccitt_byte                 |        1496 |
|---------------------------------+-------------|
| crc16modbus_bit                 |       11692 |
| crc16modbus_nibble              |        5232 |
| crc16modbus_nibblem             |        4912 |
| crc16modbus_byte                |        1496 |
|---------------------------------+-------------|
| crc32_bit                       |       18248 |
| crc32_nibble                    |        7616 |
| crc32_nibblem                   |        7104 |
| crc32_byte                      |        2272 |
|---------------------------------+-------------|
| CRC32                           |        7688 |
| Arduino_CRC32                   |        2144 |
| FastCRC32                       |        2160 |
+---------------------------------+-------------+

```

### SparkFun Pro Micro

* 16 MHz ATmega32U4
* Arduino IDE 1.8.19
* SparkFun AVR Boards 1.1.13

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |        7852 |
| crc8_nibble                     |        7396 |
| crc8_nibblem                    |        7264 |
| crc8_byte                       |         920 |
|---------------------------------+-------------|
| crc16ccitt_bit                  |       11952 |
| crc16ccitt_nibble               |        5332 |
| crc16ccitt_nibblem              |        5068 |
| crc16ccitt_byte                 |        1528 |
|---------------------------------+-------------|
| crc16modbus_bit                 |       11752 |
| crc16modbus_nibble              |        5268 |
| crc16modbus_nibblem             |        4932 |
| crc16modbus_byte                |        1500 |
|---------------------------------+-------------|
| crc32_bit                       |       18344 |
| crc32_nibble                    |        7664 |
| crc32_nibblem                   |        7140 |
| crc32_byte                      |        2288 |
|---------------------------------+-------------|
| CRC32                           |        7720 |
| Arduino_CRC32                   |        2164 |
| FastCRC32                       |        2180 |
+---------------------------------+-------------+

```

### STM32 Blue Pill

* STM32F103C8, 72 MHz ARM Cortex-M3
* Arduino IDE 1.8.19
* STM32duino 2.4.0

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |        2261 |
| crc8_nibble                     |         502 |
| crc8_nibblem                    |         531 |
| crc8_byte                       |         259 |
|---------------------------------+-------------|
| crc16ccitt_bit                  |        2390 |
| crc16ccitt_nibble               |         573 |
| crc16ccitt_nibblem              |         559 |
| crc16ccitt_byte                 |         302 |
|---------------------------------+-------------|
| crc16modbus_bit                 |        2407 |
| crc16modbus_nibble              |         560 |
| crc16modbus_nibblem             |         574 |
| crc16modbus_byte                |         244 |
|---------------------------------+-------------|
| crc32_bit                       |        2324 |
| crc32_nibble                    |         559 |
| crc32_nibblem                   |         573 |
| crc32_byte                      |         245 |
|---------------------------------+-------------|
| CRC32                           |         846 |
| Arduino_CRC32                   |         246 |
| FastCRC32                       |         188 |
+---------------------------------+-------------+

```

### ESP8266

* NodeMCU 1.0, 80MHz ESP8266
* Arduino IDE 1.8.19
* ESP8266 Boards 3.0.2

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |        1512 |
| crc8_nibble                     |         488 |
| crc8_nibblem                    |         270 |
| crc8_byte                       |         246 |
|---------------------------------+-------------|
| crc16ccitt_bit                  |        1820 |
| crc16ccitt_nibble               |         668 |
| crc16ccitt_nibblem              |         283 |
| crc16ccitt_byte                 |         375 |
|---------------------------------+-------------|
| crc16modbus_bit                 |        1937 |
| crc16modbus_nibble              |         642 |
| crc16modbus_nibblem             |         245 |
| crc16modbus_byte                |         375 |
|---------------------------------+-------------|
| crc32_bit                       |        1567 |
| crc32_nibble                    |         590 |
| crc32_nibblem                   |         244 |
| crc32_byte                      |         340 |
|---------------------------------+-------------|
| CRC32                           |         835 |
| Arduino_CRC32                   |         155 |
| FastCRC32                       |         452 |
+---------------------------------+-------------+

```

### ESP32

* ESP32-01 Dev Board, 240 MHz Tensilica LX6
* Arduino IDE 1.8.19
* ESP32 Boards 2.0.5

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |         521 |
| crc8_nibble                     |         117 |
| crc8_nibblem                    |         117 |
| crc8_byte                       |          52 |
|---------------------------------+-------------|
| crc16ccitt_bit                  |         516 |
| crc16ccitt_nibble               |         135 |
| crc16ccitt_nibblem              |         134 |
| crc16ccitt_byte                 |          83 |
|---------------------------------+-------------|
| crc16modbus_bit                 |         555 |
| crc16modbus_nibble              |         120 |
| crc16modbus_nibblem             |         120 |
| crc16modbus_byte                |          75 |
|---------------------------------+-------------|
| crc32_bit                       |         464 |
| crc32_nibble                    |         113 |
| crc32_nibblem                   |         112 |
| crc32_byte                      |          71 |
|---------------------------------+-------------|
| CRC32                           |         198 |
| Arduino_CRC32                   |          71 |
| FastCRC32                       |          43 |
+---------------------------------+-------------+

```

### Teensy 3.2

* 96 MHz ARM Cortex-M4
* Arduino IDE 1.8.19
* Teensyduino 1.57
* Compiler options: "Faster"

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |        1262 |
| crc8_nibble                     |         193 |
| crc8_nibblem                    |         193 |
| crc8_byte                       |          92 |
|---------------------------------+-------------|
| crc16ccitt_bit                  |        1348 |
| crc16ccitt_nibble               |         193 |
| crc16ccitt_nibblem              |         193 |
| crc16ccitt_byte                 |         140 |
|---------------------------------+-------------|
| crc16modbus_bit                 |        1520 |
| crc16modbus_nibble              |         182 |
| crc16modbus_nibblem             |         183 |
| crc16modbus_byte                |         139 |
|---------------------------------+-------------|
| crc32_bit                       |        1393 |
| crc32_nibble                    |         183 |
| crc32_nibblem                   |         183 |
| crc32_byte                      |         154 |
|---------------------------------+-------------|
| CRC32                           |         429 |
| Arduino_CRC32                   |         155 |
| FastCRC32                       |          23 |
+---------------------------------+-------------+

```

