

CC=gcc
CFLAGS= `pkg-config --cflags --libs gtk+-3.0`
SOURCES=tp_fan_control.c
EXECUTABLE=window


all: 
	$(CC) -o $(EXECUTABLE) $(SOURCES) $(CFLAGS)

clean:
	-rm -f *.o *~
