/* 2-time_pipes.c
** A program that determines the amount of time necessary to run a command
** from the command line. This program used pipes as IPC mechanism.
*/

#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[])
{
    int fd[2];
    pid_t pid;
    struct timeval current, prev;
    double elapsed_time;

    // Create the pipe
    if (pipe(fd) == -1)
    {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    // Fork a child process
    pid = fork();

    if (pid < 0)
    { // Error occured
        fprintf(stderr, "Fork Failed");
        return 1;
    }

    if (pid == 0) // Child process
    {
        // Close the unused end of the pipe
        close(fd[READ_END]);
        // Get timestamp
        gettimeofday(&current, NULL);
        // Write to the pipe
        write(fd[WRITE_END], &current, sizeof(struct timeval));
        // Close the write end of the pipe
        close(fd[WRITE_END]);
        // Execute the command
        execvp(argv[1], argv + 1);
    }
    else // Parent process
    {
        wait(NULL);
        // Close the unsed end of the pipe
        close(fd[WRITE_END]);
        // Get timestamp
        gettimeofday(&current, NULL);
        // Read from the pipe
        read(fd[READ_END], &prev, sizeof(struct timeval));
        // Calcuate the elapsed time
        elapsed_time = (current.tv_sec + current.tv_usec / 1000000.0) - (prev.tv_sec + prev.tv_usec / 1000000.0);
        // Print the elapsed time
        printf("Elapsed time: %lf\n", elapsed_time);
        // Close the read end of the pipe
        close(fd[READ_END]);
    }

    return 0;
}