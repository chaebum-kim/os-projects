
CC = gcc
CFLAGS = -Wall
LRT = -lrt

zombie: 1-zombie.c
	$(CC) $(CFLAGS) -o zombie 1-zombie.c

time_pipes: 2-time_pipes.c
	$(CC) $(CFLAGS) -o time_pipes 2-time_pipes.c

time_shm: 2-time_shm.c
	$(CC) $(CFLAGS) -o time_shm 2-time_shm.c $(LRT)

collatz: 4-collatz.c
	$(CC) $(CFLAGS) -o collatz 4-collatz.c

collatz_shm: 5-collatz_shm.c
	$(CC) $(CFLAGS) -o collatz_shm 5-collatz_shm.c $(LRT)


