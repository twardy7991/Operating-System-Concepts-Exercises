# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Default target
all: pidmanager.exe

# Build rule
pidmanager: pidmanager.c
	$(CC) $(CFLAGS) pidmanager.c -o pidmanager.exe -lrt

# Clean rule
clean:
	rm -f pidmanager.exe