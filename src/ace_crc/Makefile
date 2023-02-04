TARGETS := \
	crc8_bit.hpp crc8_bit.cpp \
	crc8_nibble.hpp crc8_nibble.cpp \
	crc8_nibblem.hpp crc8_nibblem.cpp \
	crc8_byte.hpp crc8_byte.cpp \
	crc16ccitt_bit.hpp crc16ccitt_bit.cpp \
	crc16ccitt_nibble.hpp crc16ccitt_nibble.cpp \
	crc16ccitt_nibblem.hpp crc16ccitt_nibblem.cpp \
	crc16ccitt_byte.hpp crc16ccitt_byte.cpp \
	crc16modbus_bit.hpp crc16modbus_bit.cpp \
	crc16modbus_nibble.hpp crc16modbus_nibble.cpp \
	crc16modbus_nibblem.hpp crc16modbus_nibblem.cpp \
	crc16modbus_byte.hpp crc16modbus_byte.cpp \
	crc32_bit.hpp crc32_bit.cpp \
	crc32_nibble.hpp crc32_nibble.cpp \
	crc32_nibblem.hpp crc32_nibblem.cpp \
	crc32_byte.hpp crc32_byte.cpp

GENERATOR := ../../tools/generate.sh

all: $(TARGETS)

#-----------------------------------------------------------------------------
# CRC-8
#-----------------------------------------------------------------------------

# bit by bit
crc8_bit.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-8 --algotag bit --header

crc8_bit.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-8 --algotag bit --source

# 4-bit table in flash memory
crc8_nibble.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-8 --algotag nibble --header

crc8_nibble.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-8 --algotag nibble --source

# 4-bit table in static memory
crc8_nibblem.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-8 --algotag nibblem --header

crc8_nibblem.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-8 --algotag nibblem --source

# 8-bit table
crc8_byte.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-8 --algotag byte --header

crc8_byte.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-8 --algotag byte --source

#-----------------------------------------------------------------------------
# CRC-16-CCITT
#-----------------------------------------------------------------------------

# bit by bit
crc16ccitt_bit.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-ccitt --algotag bit --header

crc16ccitt_bit.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-ccitt --algotag bit --source

# 4-bit table in flash memory
crc16ccitt_nibble.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-ccitt --algotag nibble --header

crc16ccitt_nibble.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-ccitt --algotag nibble --source

# 4-bit table in static memory
crc16ccitt_nibblem.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-ccitt --algotag nibblem --header

crc16ccitt_nibblem.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-ccitt --algotag nibblem --source

# 8-bit table
crc16ccitt_byte.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-ccitt --algotag byte --header

crc16ccitt_byte.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-ccitt --algotag byte --source

#-----------------------------------------------------------------------------
# CRC-16-MODBUS
#-----------------------------------------------------------------------------

# bit by bit
crc16modbus_bit.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-modbus --algotag bit --header

crc16modbus_bit.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-modbus --algotag bit --source

# 4-bit table in flash memory
crc16modbus_nibble.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-modbus --algotag nibble --header

crc16modbus_nibble.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-modbus --algotag nibble --source

# 4-bit table in static memory
crc16modbus_nibblem.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-modbus --algotag nibblem --header

crc16modbus_nibblem.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-modbus --algotag nibblem --source

# 8-bit table
crc16modbus_byte.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-modbus --algotag byte --header

crc16modbus_byte.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-modbus --algotag byte --source

#-----------------------------------------------------------------------------
# CRC-32
#-----------------------------------------------------------------------------

# bit by bit
crc32_bit.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-32 --algotag bit --header

crc32_bit.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-32 --algotag bit --source

# 4-bit table in flash ram
crc32_nibble.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-32 --algotag nibble --header

crc32_nibble.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-32 --algotag nibble --source

# 4-bit table in static ram
crc32_nibblem.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-32 --algotag nibblem --header

crc32_nibblem.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-32 --algotag nibblem --source

# 8-bit table
crc32_byte.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-32 --algotag byte --header

crc32_byte.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-32 --algotag byte --source

#-----------------------------------------------------------------------------
# clean up intermediaries
#-----------------------------------------------------------------------------

clean:
	rm -f *.c *.h *.o
