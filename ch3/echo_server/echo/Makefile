# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Default target
all: echo.exe

# Build rule
echo: echo.c
	$(CC) $(CFLAGS) echo.c -o echo.exe -lrt

# Clean rule
clean:
	rm -f echo.exe