PACKAGE = $(shell which pkg-config)

CC = gcc
CFLAGS = -g -Wall $(shell $(PACKAGE) --cflags gtk+-3.0)
LDFLAGS = -rdynamic -lGL -lm $(shell $(PACKAGE) --libs gtk+-3.0)

MAIN_DIR = pc-app
SOURCES = $(MAIN_DIR)/main.c cli-util/network/client.c pc-app/utils/utillib.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = main

.PRECIOUS: $(SOURCES)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $(MAIN_DIR)/$@ $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(MAIN_DIR)/$(TARGET) $(MAIN_DIR)/*.glade~
