CC = gcc
CFLAGS = -g -Wall -O0

all : test_mutex.exe

test_mutex.exe : test_mutex.c my_mutex.o
	${CC} ${CFLAGS} test_mutex.c my_mutex.o -o test_mutex.exe -lpthread

my_mutex.o : my_mutex.c
	${CC} ${CFLAGS} -c my_mutex.c -o my_mutex.o

