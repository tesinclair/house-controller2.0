PACKAGE = $(shell which pkg-config)

CC = gcc
CFLAGS = -g -Wall $(shell $(PACKAGE) --cflags gtk+-3.0)
LDFLAGS = -rdynamic -lGL -lm $(shell $(PACKAGE) --libs gtk+-3.0)

SOURCES = main.c utils/utilClient.c utils/utilStack.c utils/utilExit.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = main

.PRECIOUS: $(SOURCES)

build: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

run:
	./main

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET) *.glade~
