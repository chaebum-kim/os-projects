
CC = gcc
CFLAGS = -Wall

all: main.o memory.o page_table.o  tlb.o
	$(CC) $(CFLAGS) -o main main.o memory.o page_table.o tlb.o

memory.o: memory.c memory.h
	$(CC) $(CFLAGS) -c memory.c

page_table_o: page_table.c page_table.h
	$(CC) $(CFLAGS) -c page_table.c

tlb.o: tlb.c tlb.h
	$(CC) $(CFLAGS) -c tlb.c



