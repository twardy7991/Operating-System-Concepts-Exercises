# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Default target
all: client.exe

# Build rule
client: client.c
	$(CC) $(CFLAGS) client.c -o client.exe -lrt

# Clean rule
clean:
	rm -f client.exe