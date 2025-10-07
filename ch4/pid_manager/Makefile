CC = gcc
CFLAGS = -Wall -g

.PHONY = clean

all : pid

pid : pid.c
	${CC} ${CFLAGS} pid.c -o pid -pthread

clean :
	rm -f pid