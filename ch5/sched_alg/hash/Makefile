
CC = gcc
CFLAGS = -Wall -g

all : calculate_hash.exe

calculate_hash.exe : calculate_hash.c hash.o
	${CC} ${CFLAGS} calculate_hash.c hash.o -o calculate_hash.exe

hash.o : hash.c
	${CC} ${CFLAGS} -c hash.c