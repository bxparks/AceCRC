#!/usr/bin/gawk -f
#
# Usage: 
#   $ cat CpuBenchmark/{board}.txt MemoryBenchmark/{board.txt} | 
#       generate_combined.sh
#
# Takes the combined benchmark files in MemoryBenchmark/*.txt and
# CpuBenchmark/*.txt and generate a summary table of memory and CPU
# usage for each algorithm variant.

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

  # CpuBenchmark/*.txt don't have baseline, so map to labels[] starting with
  # 1-index.
  mode = "cpu"
  record_index = 1
}
{
  # The CpuBenchmark/*.txt files terminate with an "END".
  if ($0 ~ /^END/) {
    # MemoryBenchmark/*.txt map to labels[] starting with 0-index.
    mode = "memory"
    record_index = 0
  } else if (mode == "cpu") {
    u[record_index]["name"] = $1
    u[record_index]["micros"] = $6
    record_index++
  } else if (mode == "memory") {
    u[record_index]["flash"] = $2
    u[record_index]["ram"] = $4
    record_index++
  }
}

END {
  # Calculate the flash and memory deltas from baseline
  base_flash = u[0]["flash"]
  base_ram = u[0]["ram"]
  for (i = 0; i <= NUM_ALGORITHMS; i++) {
    u[i]["d_flash"] = u[i]["flash"] - base_flash
    u[i]["d_ram"] = u[i]["ram"] - base_ram
  }

  printf("+--------------------------------------------------------------+\n")
  printf("| CRC algorithm                   |  flash/  ram |  micros/kiB |\n")
  for (i = 1; i <= NUM_ALGORITHMS; i++) {
    name = labels[i]
    if (name ~ /^crc8_bit/ \
        || name ~ /^crc16ccitt_bit/ \
        || name ~ /^crc16modbus_bit/ \
        || name ~ /^crc32_bit/ \
        || name ~ /^CRC32/) {
      printf("|---------------------------------+--------------+-------------|\n")
    }
    printf("| %-31s | %6d/%5d | %11d |\n",
        name, u[i]["d_flash"], u[i]["d_ram"], u[i]["micros"])
  }
  printf("+--------------------------------------------------------------+\n")
}
