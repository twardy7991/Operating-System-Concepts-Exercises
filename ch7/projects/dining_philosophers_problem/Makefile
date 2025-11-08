CC = gcc
CFLAGS = -Wall -g

all : bad_solution.exe mutex_solution.exe asymmetric_solution.exe max4_solution.exe

bad_solution.exe : bad_solution.c
	${CC} ${CFLAGS} bad_solution.c -o bad_solution.exe -lpthread
	
mutex_solution.exe : semaphore_based_solutions/mutex_solution.c
	${CC} ${CFLAGS} semaphore_based_solutions/mutex_solution.c -o mutex_solution.exe -lpthread

asymmetric_solution.exe : semaphore_based_solutions/asymmetric_solution.c
	${CC} ${CFLAGS} semaphore_based_solutions/asymmetric_solution.c -o asymmetric_solution.exe -lpthread

max4_solution.exe : semaphore_based_solutions/max4_solution.c
	${CC} ${CFLAGS} semaphore_based_solutions/max4_solution.c -o max4_solution.exe -lpthread