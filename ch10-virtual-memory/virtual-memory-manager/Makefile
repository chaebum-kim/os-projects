
CC = gcc
CFLAGS = -Wall

all: main.o memory.o page_table.o tlb.o backstore.o fifo.o LinkedList.o
	$(CC) $(CFLAGS) -o main main.o memory.o page_table.o tlb.o backstore.o fifo.o LinkedList.o

memory.o: memory.c memory.h
	$(CC) $(CFLAGS) -c memory.c

page_table.o: page_table.c page_table.h
	$(CC) $(CFLAGS) -c page_table.c

backstore.o: backstore.c backstore.h
	$(CC) $(CFLAGS) -c backstore.c

tlb.o: tlb.c tlb.h
	$(CC) $(CFLAGS) -c tlb.c

fifo.o: fifo.c fifo.h
	$(CC) $(CFLAGS) -c fifo.c

LinkedList.o: LinkedList.c LinkedList.h
	$(CC) $(CFLAGS) -c LinkedList.c





