CC = gcc
CFLAGS = -Wall
PTHREADS = -pthread

test: test.o barrier.o
	$(CC) $(CFLAGS) -o test test.o barrier.o $(PTHREADS)

barrier.o: barrier.h
