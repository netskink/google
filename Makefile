

TARGET = google
CC = gcc

# Debug Flags
#CFLAGS = -g -Wall -pg
#LFLAGS = -g -Wall -pg
#LIBS = -lm

# Profile Flags
CFLAGS = -g -Wall -pg
LFLAGS = -pg 


.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LFLAGS) $(LIBS) 

clean:
	-rm -f *.o
	-rm -f $(TARGET)














