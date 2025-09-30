# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Default target
all: zombie.exe

# Build rule
a.out: zombie.c
	$(CC) $(CFLAGS) zombie.c -o zombie.exe

# Clean rule
clean:
	rm -f a.out