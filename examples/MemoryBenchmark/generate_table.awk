#!/usr/bin/gawk -f
#
# Usage: generate_table.sh < ${board}.out
#
# Takes the file generated by collect.sh and generates an ASCII
# table that can be inserted into the README.md.
#

BEGIN {
    labels[0] = "Baseline"
    labels[1] = "crc16ccitt_bit";
    labels[2] = "crc16ccitt_nibble";
    labels[3] = "crc16ccitt_byte";
    labels[4] = "crc32_bit";
    labels[5] = "crc32_nibble";
    labels[6] = "crc32_byte";
}
{
    feature = NR-1
    u[feature]["flash"] = $2
    u[feature]["ram"] = $4
}
END {
    base_flash = u[0]["flash"]
    base_ram = u[0]["ram"]
    for (i = 0; i < NR; i++) {
        flash = u[i]["flash"]
        ram = u[i]["ram"]
        u[i]["d_flash"] = flash - base_flash
        u[i]["d_ram"] = ram - base_ram
    }

    printf("+--------------------------------------------------------------+\n")
    printf("| functionality                   |  flash/  ram |       delta |\n")
    printf("|---------------------------------+--------------+-------------|\n")
    printf("| %-31s | %6d/%5d | %5d/%5d |\n",
        labels[0], u[0]["flash"], u[0]["ram"], u[0]["d_flash"], u[0]["d_ram"])
    printf("|---------------------------------+--------------+-------------|\n")
    for (i = 1; i <= 6; i++) {
        printf("| %-31s | %6d/%5d | %5d/%5d |\n",
            labels[i], u[i]["flash"], u[i]["ram"], u[i]["d_flash"],
            u[i]["d_ram"])
    }
    printf("+--------------------------------------------------------------+\n")
}
