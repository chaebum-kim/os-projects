/* time-shm.c
** A program that determines the amount of time necessary to run a command
** from the command line. This program used shared memory as IPC mechanism.
*/

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    const char *name = "TIME"; // Name of the shared memory object
    const int SIZE = 4096;     // The size (in bytes) of shared memory object

    char *ptr; // Pointer to shared memory object
    int fd;    // Shared memory file descriptor

    pid_t pid;

    struct timeval current, prev;

    double elapsed_time;

    // Create the shared memory object
    fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    // Configure the size of the shard memory object */
    ftruncate(fd, SIZE);

    // Memory map the shared memory object
    ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // Fork a child process
    pid = fork();

    if (pid == 0) // Child process
    {
        // Get timestamp
        gettimeofday(&current, NULL);
        // Write a timestamp to the shared memory object
        memcpy(ptr, &current, sizeof(struct timeval));
        // Execute the command
        execvp(argv[1], argv + 1);
    }
    else if (pid > 0) // Parent process
    {
        wait(NULL);
        // Get timestamp
        gettimeofday(&current, NULL);
        // Read from the shared memory object
        memcpy(&prev, ptr, sizeof(struct timeval));
        // Remove the shared memory object
        shm_unlink(name);
        // Calculate the elapsed time
        elapsed_time = (current.tv_sec + current.tv_usec / 1000000.0) - (prev.tv_sec + prev.tv_usec / 1000000.0);
        // Print the elapsed time
        printf("Elapsed time: %f\n", elapsed_time);
    }

    return 0;
}
