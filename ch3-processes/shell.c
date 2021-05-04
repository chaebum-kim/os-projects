#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define MAX_LINE 80
#define MAX_FILENAME 16
#define READ_END 0
#define WRITE_END 1

/* Fuction Prototypes */
void load_history(char *command, char *history);
int parse(char *command, char *args[]);
void is_redirected(char *args[], char *filename, int *redirect_in, int *redirect_out);
int redirect_input(char *filename);
int redirect_output(char *filename);
void is_piped(char *args[], char *args2[], int *piped);
int create_process(char *args[], char *args2[]);

/* main */
int main(void)
{
    char command[MAX_LINE], history[MAX_LINE], filename[MAX_FILENAME];
    char *args[MAX_LINE / 2 + 1], *args2[MAX_LINE / 2 + 1];
    int should_run = 1, should_wait, redirect_in, redirect_out, piped, n;
    pid_t pid;

    history[0] = 0;

    while (should_run)
    {
        printf("osh>");
        fflush(stdout);
        memset(args, 0, sizeof(args));
        memset(args2, 0, sizeof(args2));
        should_wait = 1;
        redirect_in = 0;
        redirect_out = 0;
        piped = 0;

        // Get user inputs
        fgets(command, MAX_LINE, stdin);
        command[strcspn(command, "\n")] = 0;

        // Exit if user enters "exit"
        if (strcmp(command, "exit") == 0)
        {
            should_run = 0;
            exit(0);
        }

        // Load history if user enters "!!"
        load_history(command, history);

        // Copy command to the history
        strcpy(history, command);

        // Parse the command
        n = parse(command, args);

        // Determine whether or not to wait for the child to exit
        if (strcmp(args[n - 1], "&") == 0)
        {
            should_wait = 0;
            args[n - 1] = NULL;
        }

        // Determine if redirecting input or output is necessary
        is_redirected(args, filename, &redirect_in, &redirect_out);

        // Determine if the command contains pipe character
        is_piped(args, args2, &piped);

        // If piped
        if (piped)
            create_process(args, args2);

        // If not piped
        pid = fork();
        if (pid < 0)
        {
            fprintf(stderr, "Fork Failed");
        }
        if (pid == 0) // Child process
        {
            // Redirect input if necessary
            if (redirect_in)
                redirect_input(filename);

            // Redirect output if necessary
            if (redirect_out)
                redirect_output(filename);

            execvp(args[0], args);

            exit(1);
        }
        else // Parent process
        {
            while (should_wait && wait(NULL) > 0)
                ;
        }
    }
    return 0;
}

/* load_history */
void load_history(char *command, char *history)
{
    if (strcmp(command, "!!") == 0)
    {
        if (history[0] == 0)
        {
            printf("No commands in history\n");
            printf("osh>");
            fgets(command, MAX_LINE, stdin);
        }
        else
        {
            strcpy(command, history);
            printf("%s\n", command);
        }
    }
}

/* parse */
int parse(char *command, char *args[])
{
    int n = 0;
    args[n] = strtok(command, " \n");
    while (args[n] != NULL)
    {
        n++;
        args[n] = strtok(NULL, " \n");
    }

    return n;
}

/* is_redirected */
void is_redirected(char *args[], char *filename, int *redirect_in, int *redirect_out)
{
    int i = 0;
    while (args[i] != NULL)
    {
        if (strcmp(args[i], "<") == 0 || strcmp(args[i], ">") == 0)
        {
            if (strcmp(args[i], "<") == 0)
                *redirect_in = 1;
            else
                *redirect_out = 1;
            strcpy(filename, args[i + 1]);
            args[i] = NULL;
            args[i + 1] = NULL;
            break;
        }
        i++;
    }
}

/* redirect_input */
int redirect_input(char *filename)
{
    int fd;

    // Open file
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Failed");
        return -1;
    }

    dup2(fd, STDIN_FILENO);
    close(fd);

    return 0;
}

/* redirect_output */
int redirect_output(char *filename)
{
    int fd;

    // Open file
    fd = open(filename, O_CREAT | O_WRONLY | O_EXCL, 0666);
    if (fd < 0)
    {
        perror("Failed");
        return -1;
    }

    dup2(fd, STDOUT_FILENO);
    close(fd);

    return 0;
}

/* is_piped */
void is_piped(char *args[], char *args2[], int *piped)
{
    int i = 0, j = 0;
    while (args[i] != NULL)
    {
        if (strcmp(args[i], "|") == 0)
        {
            *piped = 1;
            args[i] = NULL;
            i++;
            while (args[i] != NULL)
            {
                args2[j] = args[i];
                args[i] = NULL;
                i++;
                j++;
            }
            args2[j] = NULL;
            break;
        }
        i++;
    }
}

int create_process(char *args[], char *args2[])
{
    pid_t pid;
    int fd[2];

    pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    if (pid == 0) // Child process
    {
        // Create the pipe
        if (pipe(fd) == -1)
        {
            fprintf(stderr, "Pipe Failed\n");
            return 1;
        }

        // Fork a child process
        pid = fork();
        if (pid < 0)
        {
            fprintf(stderr, "Fork Failed\n");
            return 1;
        }
        if (pid == 0) // Child process
        {
            dup2(fd[WRITE_END], STDOUT_FILENO);
            close(fd[READ_END]);
            close(fd[WRITE_END]);
            execvp(args[0], args);
            fprintf(stderr, "Execution Failed1\n");
            exit(1);
        }
        else // Parent process
        {
            dup2(fd[READ_END], STDIN_FILENO);
            close(fd[READ_END]);
            close(fd[WRITE_END]);
            execvp(args2[0], args2);
            fprintf(stderr, "Execution Failed2\n");
            exit(1);
        }
    }
    else
    {
        wait(NULL);
    }
    return 0;
}