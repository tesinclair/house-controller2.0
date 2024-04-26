PACKAGE = $(shell which pkg-config)

CC = gcc
CFLAGS = -g -Wall $(shell $(PACKAGE) --cflags gtk+-3.0)
LDFLAGS = -rdynamic -lGL -lm $(shell $(PACKAGE) --libs gtk+-3.0)
SOURCES = main.c network/client.c utils/utillib.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = main

.PRECIOUS: $(SOURCES)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET) *.glade~
