CC = gcc
CFLAGS = -Wall -g

all : server

server : server.c 
	${CC} ${CFLAGS} server.c -o server -pthread

clean :
	rm -r server
