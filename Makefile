# Makefile for Onitama Game
CC = gcc
CFLAGS = -Wall -std=c99
TARGET = onitama

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
