# AceCRC

Various CRC algorithms generated from `pycrc` (https://pycrc.org), then
auto-converted to Arduino C++ format, and exported as an Arduino library.

Currently supported algorithms are:

* CRC-16-CCITT
* CRC-32

The following namespaces are defined:

* `ace_crc::crc16ccitt_bit`
* `ace_crc::crc16ccitt_nibble`
* `ace_crc::crc16ccitt_byte`
* `ace_crc::crc32_bit`
* `ace_crc::crc32_nibble`
* `ace_crc::crc32_byte`

Additional algorithms from `pycrc` can be generated if needed.

**Version**: 0.1 (2020-11-29)

**Changelog**: [CHANGELOG.md](CHANGELOG.md)

<a name="Installation"></a>
## HelloCrc

Here is the sample program from [examples/HelloCrc](examples/HelloCrc) that uses
the `CRC-16-CCITT` algorithm using a 4-bit lookup table (16 elements):

```C++
#include <Arduino.h>
#include <AceCRC.h>

using namespace ace_crc::crc16ccitt_nibble;

static const char CHECK_STRING[] = "123456789";
static const size_t LENGTH = sizeof(CHECK_STRING) - 1;

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait - Leonardo/Micro

  crc_t crc = crc_init();
  crc = crc_update(crc, CHECK_STRING, LENGTH);
  crc = crc_finalize(crc);

  Serial.print("0x");
  Serial.println((unsigned long) crc, 16);
}

void loop() {
}
```

This prints the hexadecimal number `0xE5CC` as expected.

<a name="Installation"></a>
## Installation

The latest stable release is (will be) available in the Arduino IDE Library
Manager.

The development version can be installed by cloning the git repo:

* AceCRC (https://github.com/bxparks/AceCRC)

You can copy over the contents to the `./libraries` directory used by the
Arduino IDE. (The result is a directory named `./libraries/AceCRC`). Or you can
create symlinks from `./libraries` to these directories.

The `develop` branch contains the latest development.
The `master` branch contains the stable releases.

<a name="Dependencies"></a>
### Dependencies

This library has no external dependencies to use.

* To regenerate and rebuild the source code, you need pycrc
  (https://pycrc.org/).
* To run the unit tests under `tests`, you need AUnit
  (https://github.com/bxparks/AUnit)
* To run the unit tests under Linux or MacOS, you need UnixHostDuino
  (https://github.com/bxparks/UnixHostDuino)

<a name="Documentation"></a>
## Documentation

* [README.md](README.md) - this file
* [Doxygen docs](https://bxparks.github.io/AceCRC/html) hosted on GitHub Pages

<a name="Usage"></a>
## Usage

<a name="Headers"></a>
### Headers and Namespaces

Only a single header file `AceCRC.h` is required to use this library.

```C++
#include <AceCRC.h>
```

Then select the namespace of the algorithm that you want to use. For example,
to use the version of `crc32` which uses a 4-bit table (16 entries), use the
following:

```C++
using namespace ace_crc::crc32_nibble;
```

To use the 8-bit table: use:

```C++
using namespace ace_crc::crc32_byte;
```

<a name="CoreFunctions"></a>
### Core CRC Functions

All algorithms and their variants are placed in separate C++ namespaces so they
do not collide, and you can use multiple CRC algorithms in a single program
without worrying about name collision.

The `crc_t` typedef, the function names, and their signatures from the
underlying generated code from `pycrc` remain unchanged. For reference, the
principle functions are:

* `crc_t crc_init(void);`
* `crc_t crc_update(crc_t crc, const void *data, size_t data_len);`
* `crc_t crc_finalize(crc_t crc);`

Here is a sample code that shows how to use these functions:

```C++
crc_t calculateCRC(const char* str) {
  crc_t crc = crc_init();
  crc = crc_update(crc, str, strlen(str));
  crc = crc_finalize(crc);
  return crc;
}
```

<a name="SystemRequirements"></a>
## System Requirements

### Tool Chain

* [Arduino IDE 1.8.13](https://www.arduino.cc/en/Main/Software)
* [Arduino AVR Boards 1.8.3](https://github.com/arduino/ArduinoCore-avr)
* [Arduino SAMD Boards 1.8.9](https://github.com/arduino/ArduinoCore-samd)
* [SparkFun AVR Boards 1.1.13](https://github.com/sparkfun/Arduino_Boards)
* [SparkFun SAMD Boards 1.8.1](https://github.com/sparkfun/Arduino_Boards)
* [ESP8266 Arduino 2.7.4](https://github.com/esp8266/Arduino)
* [ESP32 Arduino 1.0.4](https://github.com/espressif/arduino-esp32)
* [Teensydino 1.53](https://www.pjrc.com/teensy/td_download.html)

### Hardware

The library is extensively tested on the following boards:

* Arduino Nano clone (16 MHz ATmega328P)
* SparkFun Pro Micro clone (16 MHz ATmega32U4)
* WeMos D1 Mini clone (ESP-12E module, 80 MHz ESP8266)
* ESP32 dev board (ESP-WROOM-32 module, 240 MHz dual core Tensilica LX6)
* SAMD21 M0 Mini (48 MHz ARM Cortex-M0+) (compatible with Arduino Zero) (See
  notes in the [USER_GUIDE.md](USER_GUIDE.md) for some potential issues.)

I will occasionally test on the following hardware as a sanity check:

* Teensy 3.2 (72 MHz ARM Cortex-M4)
* Mini Mega 2560 (Arduino Mega 2560 compatible, 16 MHz ATmega2560)

### Operating System

I use Ubuntu 18.04 and 20.04 for the vast majority of my development. I expect
that the library will work fine under MacOS and Windows, but I have not tested
them.

The generator script in `./tools/generate.sh` has only been tested under Ubuntu
20.04.

<a name="License"></a>
## License

[MIT License](https://opensource.org/licenses/MIT)

<a name="Bugs"></a>
## Bugs and Limitations

* v0.1 places the lookup table for the `nibble` and `byte` variants in static
  RAM instead of `PROGMEM`. This will be fixed soon.

<a name="Feedback"></a>
## Feedback and Support

If you have any questions, comments, bug reports, or feature requests, please
file a GitHub ticket instead of emailing me unless the content is sensitive.
(The problem with email is that I cannot reference the email conversation when
other people ask similar questions later.) I'd love to hear about how this
software and its documentation can be improved. I can't promise that I will
incorporate everything, but I will give your ideas serious consideration.

<a name="Authors"></a>
## Authors

Created by Brian T. Park (brian@xparks.net).
