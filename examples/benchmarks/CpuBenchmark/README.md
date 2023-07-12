# CPU Benchmark

The `CPUBenchmark.ino` determines the CPU run time of each of various CRC
algorithms.

**Version**: AceCRC v1.1.1

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
* Arduino IDE 1.8.19, Arduino CLI 0.33.0
* Arduino AVR Boards 1.8.6

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
* Arduino IDE 1.8.19, Arduino CLI 0.33.0
* SparkFun AVR Boards 1.1.13

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |        7832 |
| crc8_nibble                     |        7396 |
| crc8_nibblem                    |        7268 |
| crc8_byte                       |         916 |
|---------------------------------+-------------|
| crc16ccitt_bit                  |       11952 |
| crc16ccitt_nibble               |        5336 |
| crc16ccitt_nibblem              |        5064 |
| crc16ccitt_byte                 |        1492 |
|---------------------------------+-------------|
| crc16modbus_bit                 |       11760 |
| crc16modbus_nibble              |        5264 |
| crc16modbus_nibblem             |        4936 |
| crc16modbus_byte                |        1500 |
|---------------------------------+-------------|
| crc32_bit                       |       18344 |
| crc32_nibble                    |        7660 |
| crc32_nibblem                   |        7144 |
| crc32_byte                      |        2292 |
|---------------------------------+-------------|
| CRC32                           |        7720 |
| Arduino_CRC32                   |        2152 |
| FastCRC32                       |        2184 |
+---------------------------------+-------------+

```

## Seeed Studio XIAO (SAMD21)

* SAMD21, 48 MHz ARM Cortex-M0+
* Arduino IDE 1.8.19, Arduino CLI 0.33.0
* Seeeduino SAMD Boards 1.8.4

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |        2261 |
| crc8_nibble                     |         488 |
| crc8_nibblem                    |         516 |
| crc8_byte                       |         273 |
|---------------------------------+-------------|
| crc16ccitt_bit                  |        2275 |
| crc16ccitt_nibble               |         488 |
| crc16ccitt_nibblem              |         488 |
| crc16ccitt_byte                 |         316 |
|---------------------------------+-------------|
| crc16modbus_bit                 |        2436 |
| crc16modbus_nibble              |         488 |
| crc16modbus_nibblem             |         488 |
| crc16modbus_byte                |         330 |
|---------------------------------+-------------|
| crc32_bit                       |        2324 |
| crc32_nibble                    |         488 |
| crc32_nibblem                   |         531 |
| crc32_byte                      |         274 |
|---------------------------------+-------------|
| CRC32                           |         845 |
| Arduino_CRC32                   |         274 |
| FastCRC32                       |         186 |
+---------------------------------+-------------+

```

### STM32 Blue Pill

* STM32F103C8, 72 MHz ARM Cortex-M3
* Arduino IDE 1.8.19, Arduino CLI 0.33.0
* STM32duino 2.6.0

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |        2261 |
| crc8_nibble                     |         488 |
| crc8_nibblem                    |         516 |
| crc8_byte                       |         273 |
|---------------------------------+-------------|
| crc16ccitt_bit                  |        2275 |
| crc16ccitt_nibble               |         488 |
| crc16ccitt_nibblem              |         488 |
| crc16ccitt_byte                 |         316 |
|---------------------------------+-------------|
| crc16modbus_bit                 |        2436 |
| crc16modbus_nibble              |         488 |
| crc16modbus_nibblem             |         488 |
| crc16modbus_byte                |         330 |
|---------------------------------+-------------|
| crc32_bit                       |        2324 |
| crc32_nibble                    |         488 |
| crc32_nibblem                   |         531 |
| crc32_byte                      |         274 |
|---------------------------------+-------------|
| CRC32                           |         845 |
| Arduino_CRC32                   |         274 |
| FastCRC32                       |         186 |
+---------------------------------+-------------+

```

## Adafruit ItsyBitsy M4 (SAMD51)

* SAMD51, 120 MHz ARM Cortex-M4
* Arduino IDE 1.8.19, Arduino CLI 0.33.0
* Adafruit SAMD 1.7.13

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |         949 |
| crc8_nibble                     |         171 |
| crc8_nibblem                    |         171 |
| crc8_byte                       |          86 |
|---------------------------------+-------------|
| crc16ccitt_bit                  |        1008 |
| crc16ccitt_nibble               |         163 |
| crc16ccitt_nibblem              |         163 |
| crc16ccitt_byte                 |         103 |
|---------------------------------+-------------|
| crc16modbus_bit                 |        1078 |
| crc16modbus_nibble              |         163 |
| crc16modbus_nibblem             |         162 |
| crc16modbus_byte                |         103 |
|---------------------------------+-------------|
| crc32_bit                       |        1019 |
| crc32_nibble                    |         163 |
| crc32_nibblem                   |         163 |
| crc32_byte                      |         103 |
|---------------------------------+-------------|
| CRC32                           |         361 |
| Arduino_CRC32                   |         103 |
| FastCRC32                       |          57 |
+---------------------------------+-------------+

```

### ESP8266

* NodeMCU 1.0, 80MHz ESP8266
* Arduino IDE 1.8.19, Arduino CLI 0.33.0
* ESP8266 Boards 3.0.2

```
+-----------------------------------------------+
| CRC algorithm                   |  micros/kiB |
|---------------------------------+-------------|
| crc8_bit                        |        1513 |
| crc8_nibble                     |         488 |
| crc8_nibblem                    |         270 |
| crc8_byte                       |         246 |
|---------------------------------+-------------|
| crc16ccitt_bit                  |        1820 |
| crc16ccitt_nibble               |         669 |
| crc16ccitt_nibblem              |         283 |
| crc16ccitt_byte                 |         375 |
|---------------------------------+-------------|
| crc16modbus_bit                 |        1937 |
| crc16modbus_nibble              |         642 |
| crc16modbus_nibblem             |         244 |
| crc16modbus_byte                |         375 |
|---------------------------------+-------------|
| crc32_bit                       |        1567 |
| crc32_nibble                    |         591 |
| crc32_nibblem                   |         244 |
| crc32_byte                      |         340 |
|---------------------------------+-------------|
| CRC32                           |         834 |
| Arduino_CRC32                   |         155 |
| FastCRC32                       |         458 |
+---------------------------------+-------------+

```

### ESP32

* ESP32-01 Dev Board, 240 MHz Tensilica LX6
* Arduino IDE 1.8.19, Arduino CLI 0.33.0
* ESP32 Boards 2.0.9

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
| crc16ccitt_nibble               |         134 |
| crc16ccitt_nibblem              |         133 |
| crc16ccitt_byte                 |          83 |
|---------------------------------+-------------|
| crc16modbus_bit                 |         556 |
| crc16modbus_nibble              |         121 |
| crc16modbus_nibblem             |         121 |
| crc16modbus_byte                |          75 |
|---------------------------------+-------------|
| crc32_bit                       |         465 |
| crc32_nibble                    |         112 |
| crc32_nibblem                   |         112 |
| crc32_byte                      |          71 |
|---------------------------------+-------------|
| CRC32                           |         197 |
| Arduino_CRC32                   |          71 |
| FastCRC32                       |          44 |
+---------------------------------+-------------+

```

