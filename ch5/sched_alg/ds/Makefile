CC = gcc 
CFLAGS = -Wall -g

all : test_heap.exe

test_heap.exe : test_heap.c heap.o ../read.o
	${CC} ${CFLAGS} test_heap.c heap.o ./read.o -o test_heap.exe

heap.o : heap.c 
	${CC} ${CFLAGS} -c heap.c

../read.o : ../read.c
	${CC} ${CFLAGS} -c ../read.c