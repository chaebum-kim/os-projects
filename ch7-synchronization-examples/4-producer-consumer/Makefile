CC=gcc
CFLAGS=-Wall
PTHREADS=-lpthread

all: buffer.o main.o
	$(CC) $(CFLAGS) -o main buffer.o main.o $(PTHREADS)

buffer.o: buffer.c buffer.h
	$(CC) $(CFLAGS) -c buffer.c