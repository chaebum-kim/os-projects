CC = gcc
CFLAGS = -Wall -pthread

test: test.o barrier.o
	$(CC) $(CFLAGS) -o test test.o barrier.o

barrier.o: barrier.h
