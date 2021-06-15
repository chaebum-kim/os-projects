
CC = gcc
CFLAGS = -Wall

all: main.o banker.o
	$(CC) $(CFLAGS) -o main main.o banker.o

banker.o: banker.c banker.h
	$(CC) $(CFLAGS) -c banker.c