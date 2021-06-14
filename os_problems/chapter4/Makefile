
CC = gcc
CFLAGS = -Wall
PTHREAD = -pthread
LM = -lm
OPENMP = -fopenmp

static: 1-static.c
	$(CC) $(CFLAGS) -o static 1-static.c $(PTHREAD)

prime: 2-prime.c
	$(CC) $(CFLAGS) -o prime 2-prime.c $(PTHREAD)

pi-thread: 3-pi_thread.c
	$(CC) $(CFLAGS) -o pi-thread 3-pi_thread.c $(PTHREAD) $(LM)

pi-openmp: 4-pi_openmp.c
	$(CC) $(CFLAGS) -o pi-openmp 4-pi_openmp.c $(OPENMP) $(LM)

fibonacci: 6-fibonacci.c
	$(CC) $(CFLAGS) -o fibonacci 6-fibonacci.c $(PTHREAD)
