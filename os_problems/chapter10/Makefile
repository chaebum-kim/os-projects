
CC = gcc
CFLAGS = -Wall

all: main.o fifo.o lru.o opt.o frame.o LinkedList.o main.o
	$(CC) $(CFLAGS) -o main main.o fifo.o lru.o opt.o frame.o LinkedList.o

fifo.o: fifo.c fifo.h
	$(CC) $(CFLAGS) -c fifo.c

lru.o: lru.c fifo.h
	$(CC) $(CFLAGS) -c lru.c

opt.o: opt.c opt.h
	$(CC) $(CFLAGS) -c opt.c
	
frame.o: frame.c frame.h
	$(CC) $(CFLAGS) -c frame.c


