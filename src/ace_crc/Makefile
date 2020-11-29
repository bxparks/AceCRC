TARGETS := \
	crc16ccitt_bit.hpp crc16ccitt_bit.cpp \
	crc16ccitt_nibble.hpp crc16ccitt_nibble.cpp \
	crc16ccitt_byte.hpp crc16ccitt_byte.cpp \
	crc32_bit.hpp crc32_bit.cpp \
	crc32_nibble.hpp crc32_nibble.cpp \
	crc32_byte.hpp crc32_byte.cpp

GENERATOR := ../../tools/generate.sh

all: $(TARGETS)

#main.out: $(TARGETS) main.cpp
#	g++ -W -Wall -std=c++11 crc16ccitt_bit.cpp main.cpp -o main.out

#-----------------------------------------------------------------------------
# CRC-16-CCITT
#-----------------------------------------------------------------------------

# bit by bit
crc16ccitt_bit.h: $(GENERATOR)
	$(GENERATOR) --model crc-16-ccitt --algotag bit --header

crc16ccitt_bit.c: $(GENERATOR)
	$(GENERATOR) --model crc-16-ccitt --algotag bit --source

crc16ccitt_bit.hpp: crc16ccitt_bit.h
	$(GENERATOR) --model crc-16-ccitt --algotag bit --header --convert

crc16ccitt_bit.cpp: crc16ccitt_bit.c
	$(GENERATOR) --model crc-16-ccitt --algotag bit --source --convert

# 4-bit table
crc16ccitt_nibble.h: $(GENERATOR)
	$(GENERATOR) --model crc-16-ccitt --algotag nibble --header

crc16ccitt_nibble.c: $(GENERATOR)
	$(GENERATOR) --model crc-16-ccitt --algotag nibble --source

crc16ccitt_nibble.hpp: crc16ccitt_nibble.h
	$(GENERATOR) --model crc-16-ccitt --algotag nibble --header --convert

crc16ccitt_nibble.cpp: crc16ccitt_nibble.c
	$(GENERATOR) --model crc-16-ccitt --algotag nibble --source --convert

# 8-bit table
crc16ccitt_byte.h: $(GENERATOR)
	$(GENERATOR) --model crc-16-ccitt --algotag byte --header

crc16ccitt_byte.c: $(GENERATOR)
	$(GENERATOR) --model crc-16-ccitt --algotag byte --source

crc16ccitt_byte.hpp: crc16ccitt_byte.h
	$(GENERATOR) --model crc-16-ccitt --algotag byte --header --convert

crc16ccitt_byte.cpp: crc16ccitt_byte.c
	$(GENERATOR) --model crc-16-ccitt --algotag byte --source --convert

#-----------------------------------------------------------------------------
# CRC-32
#-----------------------------------------------------------------------------

# bit by bit
crc32_bit.h: $(GENERATOR)
	$(GENERATOR) --model crc-32 --algotag bit --header

crc32_bit.c: $(GENERATOR)
	$(GENERATOR) --model crc-32 --algotag bit --source

crc32_bit.hpp: crc32_bit.h
	$(GENERATOR) --model crc-32 --algotag bit --header --convert

crc32_bit.cpp: crc32_bit.c
	$(GENERATOR) --model crc-32 --algotag bit --source --convert

# 4-bit table
crc32_nibble.h: $(GENERATOR)
	$(GENERATOR) --model crc-32 --algotag nibble --header

crc32_nibble.c: $(GENERATOR)
	$(GENERATOR) --model crc-32 --algotag nibble --source

crc32_nibble.hpp: crc32_nibble.h
	$(GENERATOR) --model crc-32 --algotag nibble --header --convert

crc32_nibble.cpp: crc32_nibble.c
	$(GENERATOR) --model crc-32 --algotag nibble --source --convert

# 8-bit table
crc32_byte.h: $(GENERATOR)
	$(GENERATOR) --model crc-32 --algotag byte --header

crc32_byte.c: $(GENERATOR)
	$(GENERATOR) --model crc-32 --algotag byte --source

crc32_byte.hpp: crc32_byte.h
	$(GENERATOR) --model crc-32 --algotag byte --header --convert

crc32_byte.cpp: crc32_byte.c
	$(GENERATOR) --model crc-32 --algotag byte --source --convert

#-----------------------------------------------------------------------------
# clean up intermediaries
#-----------------------------------------------------------------------------

clean:
	rm -f *.c *.h *.o
