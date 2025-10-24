CC = gcc
CFLAGS = -Wall -g

OBJS = read.o cpu/cpu.o ds/list.o hash/hash.o schedulers/fcfs.o schedulers/sjf.o schedulers/rr.o ds/heap.o

all : scheduler.exe 

scheduler.exe : scheduler.c ${OBJS}
	${CC} ${CFLAGS} scheduler.c ${OBJS} -o scheduler.exe

read.o : read.c task.h
	${CC} ${CFLAGS} -c read.c

cpu/cpu.o : cpu/cpu.c
	${CC} ${CFLAGS} -c cpu/cpu.c -o cpu/cpu.o

ds/list.o : ds/list.c
	${CC} ${CFLAGS} -c ds/list.c -o ds/list.o

hash/hash.o : hash/hash.c 
	${CC} ${CFLAGS} -c hash/hash.c -o hash/hash.o

schedulers/fcfs.o : schedulers/fcfs.c
	${CC} ${CFLAGS} -c schedulers/fcfs.c -o schedulers/fcfs.o

schedulers/sjf.o : schedulers/sjf.c ds/heap.o
	${CC} ${CFLAGS} -c schedulers/sjf.c -o schedulers/sjf.o 

schedulers/rr.o : schedulers/rr.c
	${CC} ${CFLAGS} -c schedulers/rr.c -o schedulers/rr.o

ds/heap.o : ds/heap.c
	${CC} ${CFLAGS} -c ds/heap.c -o ds/heap.o

# schedulers/*.o : 
# 	for f in schedulers/*.c ; do \
# 		${CC} ${CFLAGS} -c "$f" -o "${f%.c}.o" ; \
# 	done