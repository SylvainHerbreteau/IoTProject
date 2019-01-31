CC=gcc
CXX=g++

SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=%.o)

SRCPP=$(wildcard *.cpp)
OBJPP=$(SRCPP:%.cpp=%.o)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CFLAGS)

.PHONY: all
all: $(OBJ) $(OBJPP)

.PHONY: clean
clean:
	rm *.o
