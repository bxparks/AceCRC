#!/usr/bin/gawk -f
#
# Usage: generate_table.awk < ${board}.txt
#
# Takes the file generated by collect.sh and generates an ASCII
# table that can be inserted into the README.md.

BEGIN {
  NUM_ACE_CRC_ALGORITHMS = 16
  NUM_ALGORITHMS = 19
  labels[0] = "baseline"
  labels[1] = "crc8_bit";
  labels[2] = "crc8_nibble";
  labels[3] = "crc8_nibblem";
  labels[4] = "crc8_byte";
  labels[5] = "crc16ccitt_bit";
  labels[6] = "crc16ccitt_nibble";
  labels[7] = "crc16ccitt_nibblem";
  labels[8] = "crc16ccitt_byte";
  labels[9] = "crc16modbus_bit";
  labels[10] = "crc16modbus_nibble";
  labels[11] = "crc16modbus_nibblem";
  labels[12] = "crc16modbus_byte";
  labels[13] = "crc32_bit";
  labels[14] = "crc32_nibble";
  labels[15] = "crc32_nibblem";
  labels[16] = "crc32_byte";
  labels[17] = "CRC32";
  labels[18] = "Arduino_CRC32";
  labels[19] = "FastCRC";
  record_index = 0
}
{
  u[record_index]["flash"] = $2
  u[record_index]["ram"] = $4
  record_index++
}
END {
  # Calculate the flash and memory deltas from baseline
  base_flash = u[0]["flash"]
  base_ram = u[0]["ram"]
  for (i = 0; i <= NUM_ALGORITHMS; i++) {
    u[i]["d_flash"] = u[i]["flash"]- base_flash
    u[i]["d_ram"] = u[i]["ram"]- base_ram
  }

  printf("+--------------------------------------------------------------+\n")
  printf("| functionality                   |  flash/  ram |       delta |\n")
  printf("|---------------------------------+--------------+-------------|\n")
  for (i = 0; i <= NUM_ALGORITHMS; i++) {
    name = labels[i]
    if (name ~ /^crc8_bit/ \
        || name ~ /^crc16ccitt_bit/ \
        || name ~ /^crc16modbus_bit/ \
        || name ~ /^crc32_bit/ \
        || name ~ /^CRC32/) {
      printf("|---------------------------------+--------------+-------------|\n")
    }
    printf("| %-31s | %6d/%5d | %5d/%5d |\n",
        name, u[i]["flash"], u[i]["ram"], u[i]["d_flash"], u[i]["d_ram"])
  }
  printf("+--------------------------------------------------------------+\n")
}
