#include <Arduino.h>
#include <AceCRC.h>

using namespace ace_crc::crc16ccitt::bit;

static const char str[] = "123456789";

void setup() {
#if ! defined(UNIX_HOST_DUINO)
  delay(1000);
#endif
  SERIAL_PORT_MONITOR.begin(115200);
  while (!SERIAL_PORT_MONITOR); // Wait - Leonardo/Micro

  crc_t crc = crc_init();
  crc = crc_update(crc, (unsigned char *)str, sizeof(str) - 1);
  crc = crc_finalize(crc);

  SERIAL_PORT_MONITOR.println((unsigned long)crc, 16);

#if defined(UNIX_HOST_DUINO)
  exit(0);
#endif
}

void loop() {
}
