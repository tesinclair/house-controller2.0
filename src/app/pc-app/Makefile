PACKAGE = $(shell which pkg-config)

CC = gcc
CFLAGS = -g -Wall $(shell $(PACKAGE) --cflags gtk+-3.0 lights-dsl)
LDFLAGS = -rdynamic -lm $(shell $(PACKAGE) --libs gtk+-3.0 lights-dsl)

SOURCES = main.c utils/utilClient.c utils/utilStack.c utils/utilError.c utils/utilLight.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = main

.PRECIOUS: $(SOURCES)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c clean
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(TARGET) *.glade~
