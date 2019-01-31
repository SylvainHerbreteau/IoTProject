CFLAGS=-I../../lib/lmic
LDFLAGS=-lwiringPi
CC=g++
abp: abp.cpp
	cd ../../lib/lmic && $(MAKE)
	$(CC) $(CFLAGS) -o abp abp.cpp ../../lib/lmic/*.o $(LDFLAGS)

	
all: abp

.PHONY: clean

clean:
	rm -f *.o abp
