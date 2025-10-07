# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Default target
all: collatz

# Build rule
collatz: collatz.c
	$(CC) $(CFLAGS) collatz.c -o collatz -lrt

# Clean rule
clean:
	rm -f collatz