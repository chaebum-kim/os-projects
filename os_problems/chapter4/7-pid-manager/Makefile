
CC = gcc
CFLAGS = -Wall
PTHREAD = -pthread

all: pid_manager.o test.o
	$(CC) $(CFLAGS) -o test test.o pid_manager.o $(PTHREAD)

pid_manager.o: pid_manager.c pid_manager.h
	$(CC) $(CFLAGS) -c pid_manager.c