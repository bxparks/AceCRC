TARGETS := \
	crc8_bit.hpp crc8_bit.cpp \
	crc8_nibble.hpp crc8_nibble.cpp \
	crc8_byte.hpp crc8_byte.cpp \
	crc16ccitt_bit.hpp crc16ccitt_bit.cpp \
	crc16ccitt_nibble.hpp crc16ccitt_nibble.cpp \
	crc16ccitt_byte.hpp crc16ccitt_byte.cpp \
	crc32_bit.hpp crc32_bit.cpp \
	crc32_nibble.hpp crc32_nibble.cpp \
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

# 4-bit table
crc8_nibble.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-8 --algotag nibble --header

crc8_nibble.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-8 --algotag nibble --source

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

# 4-bit table
crc16ccitt_nibble.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-ccitt --algotag nibble --header

crc16ccitt_nibble.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-ccitt --algotag nibble --source

# 8-bit table
crc16ccitt_byte.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-ccitt --algotag byte --header

crc16ccitt_byte.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-16-ccitt --algotag byte --source

#-----------------------------------------------------------------------------
# CRC-32
#-----------------------------------------------------------------------------

# bit by bit
crc32_bit.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-32 --algotag bit --header

crc32_bit.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-32 --algotag bit --source

# 4-bit table
crc32_nibble.hpp: $(GENERATOR)
	$(GENERATOR) --model crc-32 --algotag nibble --header

crc32_nibble.cpp: $(GENERATOR)
	$(GENERATOR) --model crc-32 --algotag nibble --source

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
