
CC = gcc
CFLAGS = -Wall
PTHREAD = -pthread

all: test.o sort.o
	$(CC) $(CFLAGS) -o test test.o sort.o  $(PTHREAD)

sort.o: sort.c sort.h
	$(CC) $(CFLAGS) -c sort.c