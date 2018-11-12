CC = g++
CFLAGS = -Wall
EXEC_NAME = mqtt_client
INCLUDES =
LIBS = -lmosquitto -lmosquittopp
OBJ_FILES = main.o mqtt.o

all : $(EXEC_NAME)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.c
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean :
	rm $(EXEC_NAME) $(OBJ_FILES)
