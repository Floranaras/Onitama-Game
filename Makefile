# Makefile for Onitama with Enhanced Console UI

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = -lncurses

# Program names
ORIGINAL_TARGET = onitama_original
ENHANCED_TARGET = onitama_enhanced

# Default target
all: enhanced

# Enhanced version with arrow keys
enhanced: $(ENHANCED_TARGET)

# Original console version
original: $(ORIGINAL_TARGET)

# Build both versions
both: enhanced original

# Enhanced version (ncurses)
$(ENHANCED_TARGET): onitama_ncurses.c onitama.h
	$(CC) $(CFLAGS) onitama_ncurses.c -o $(ENHANCED_TARGET) $(LDFLAGS)

# Original version
$(ORIGINAL_TARGET): main.c onitama.h
	$(CC) $(CFLAGS) main.c -o $(ORIGINAL_TARGET)

# Clean
clean:
	rm -f $(ENHANCED_TARGET) $(ORIGINAL_TARGET) *.o

# Run enhanced version
run: $(ENHANCED_TARGET)
	./$(ENHANCED_TARGET)

# Run original version
run-original: $(ORIGINAL_TARGET)
	./$(ORIGINAL_TARGET)

.PHONY: all enhanced original both clean run run-original
