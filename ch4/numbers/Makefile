CC = gcc
CFLAGS = -Wall -g

all : numbers

numbers: numbers.c
	${CC} ${CFLAGS} numbers.c -o numbers -lpthread

clean:
	rm -f numbers