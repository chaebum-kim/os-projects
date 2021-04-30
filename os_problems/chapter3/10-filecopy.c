/* 10-filecopy.c
**  A file-copying program using ordinary pipes.
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#define READ_END 0
#define WRITE_END 1
#define BUF_SIZE 8192

int main(int arg, char *argv[])
{
    int src, dst, in, fd[2];
    pid_t pid;
    char buffer[BUF_SIZE];

    // Open files
    src = open(argv[1], O_RDONLY);
    if (src < 0)
    {
        perror("Failed");
        return 1;
    }
    dst = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, 0666);
    if (dst < 0)
    {
        perror("Failed");
        return 1;
    }

    // Create the pipe
    if (pipe(fd) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    // Fork a child process
    pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    if (pid > 0) // Parent process
    {
        // Write to the pipe
        close(fd[READ_END]);
        while ((in = read(src, buffer, BUF_SIZE)) > 0)
        {
            write(fd[WRITE_END], buffer, in);
        }
        close(fd[WRITE_END]);
        close(src);
    }
    else // Child process
    {
        // Read from the pipe
        close(fd[WRITE_END]);
        while ((in = read(fd[READ_END], buffer, BUF_SIZE)) > 0)
        {
            write(dst, buffer, in);
        }
        close(fd[READ_END]);
        close(dst);
    }
}