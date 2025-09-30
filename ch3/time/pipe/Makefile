# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Default target
all: time.exe

# Build rule
time: time.c
	$(CC) $(CFLAGS) time.c -o time.exe -lrt

# Clean rule
clean:
	rm -f time.exe