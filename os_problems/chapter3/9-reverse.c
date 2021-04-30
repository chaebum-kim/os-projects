/* 9-reverse.c
** A program in which one process sends a string message to a second process,
** and the second process reverseds the case of each character in the message
** and sends it back to the first process.
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define READ_END 0
#define WRITE_END 1
#define BUF_SIZE 32

// Function Prototype
void reverse(char *message);

int main(int argc, char *argv[])
{
    int fd1[2], fd2[2];
    pid_t pid;
    char write_msg[BUF_SIZE] = "Hi There";
    char read_msg[BUF_SIZE];

    // Create the pipe
    if (pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        fprintf(stderr, "Pipe Failed.");
        return 1;
    }

    // Fork a child process
    pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    if (pid == 0) // Child process
    {
        // Read the original message from the pipe1
        close(fd1[WRITE_END]);
        read(fd1[READ_END], read_msg, BUF_SIZE);
        close(fd1[READ_END]);

        // Reverse the case of each character in the message
        reverse(read_msg);

        // Write reversed message to the pipe2
        close(fd2[READ_END]);
        write(fd2[WRITE_END], read_msg, strlen(read_msg) + 1);
        close(fd2[WRITE_END]);
    }
    else // Parent process
    {
        // Write the original message to the pipe1
        close(fd1[READ_END]);
        write(fd1[WRITE_END], write_msg, strlen(write_msg) + 1);
        close(fd1[WRITE_END]);

        // Wait until the child process is done
        wait(NULL);

        // Read the reversed message from the pipe2
        close(fd2[WRITE_END]);
        read(fd2[READ_END], read_msg, BUF_SIZE);
        close(fd2[READ_END]);
        // Print the reversed message
        printf("%s\n", read_msg);
    }
}

void reverse(char *message)
{
    for (int i = 0, n = strlen(message); i < n; i++)
    {
        if (islower(message[i]))
        {
            message[i] = toupper(message[i]);
        }
        else if (isupper(message[i]))
        {
            message[i] = tolower(message[i]);
        }
    }
}