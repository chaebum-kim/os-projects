
CC = gcc
CFLAGS = -Wall

all: main.o cma.o LinkedList.o
	$(CC) $(CFLAGS) -o allocator main.o cma.o LinkedList.o

cma.o: cma.c cma.h
	$(CC) $(CFLAGS) -c cma.c
