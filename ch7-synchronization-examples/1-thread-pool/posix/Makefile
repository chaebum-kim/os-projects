# makefile for thread pool
#

CC=gcc
CFLAGS=-Wall
PTHREADS=-lpthread

all: client.o threadpool.o queue.o
	$(CC) $(CFLAGS) -o example client.o threadpool.o queue.o $(PTHREADS)

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

threadpool.o: threadpool.c threadpool.h
	$(CC) $(CFLAGS) -c threadpool.c $(PTHREADS)

clean:
	rm -rf *.o
	rm -rf example

