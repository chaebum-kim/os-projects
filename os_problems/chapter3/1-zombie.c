/* zombie.c
** A program that forks a child process that ultimately becomes a zombie process.
** The zombie process will remain in the system while parent proccess is alive.
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    pid_t pid;

    // Fork a child process
    pid = fork();

    if (pid == 0)
    {
        printf("I am child process %d\n", getpid());
    }
    else if (pid > 0)
    {
        printf("I am parent process %d\n", getpid());
        while (1)
        {
            // Do nothing
        };
    }

    return 0;
}