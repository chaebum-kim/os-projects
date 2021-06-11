#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define MAX_LINE 80
#define READ_END 0
#define WRITE_END 1

/* Fuction Prototypes */
int load_history(char *command, char *history);
int parse(char *command, char *args[]);
void identify_operators(int argc, char *args[]);
int redirect_input(char *filename);
int redirect_output(char *filename);
int pipe_commands(char *args[], char *args2[]);

// Global variables
enum Mode
{
    redirect_in,
    redirect_out,
    piped,
    none
} mode = none;

enum Wait
{
    True,
    False
} wait_child;

char *file_name;
char **args2;

/* main */
int main(void)
{
    char command[MAX_LINE], history[MAX_LINE];
    char *args[MAX_LINE / 2 + 1];
    int should_run = 1, n;
    pid_t pid;

    history[0] = 0;
    wait_child = True;

    while (should_run)
    {
        printf("osh>");
        fflush(stdout);
        memset(args, 0, sizeof(args));

        // Get user inputs
        fgets(command, MAX_LINE, stdin);
        command[strcspn(command, "\n")] = 0;

        // Exit if user enters "exit"
        if (strcmp(command, "exit") == 0)
        {
            should_run = 0;
            continue;
        }

        // Load history if user enters "!!"
        if (strcmp(command, "!!") == 0)
            if (load_history(command, history) < 0)
                continue;

        // Copy command to the history
        strcpy(history, command);

        // Parse the command
        n = parse(command, args);

        // Identify operators
        identify_operators(n, args);

        // If not piped
        pid = fork();
        if (pid < 0)
        {
            fprintf(stderr, "Fork Failed");
        }
        if (pid == 0) // Child process
        {
            // Redirect input
            if (mode == redirect_in)
            {
                redirect_input(file_name);
                execvp(args[0], args);
            }

            // Redirect output
            else if (mode == redirect_out)
            {
                redirect_output(file_name);
                execvp(args[0], args);
            }

            // Pipe commands
            else if (mode == piped)
                pipe_commands(args, args2);

            // Default
            else
                execvp(args[0], args);
        }
        else // Parent process
        {
            if (wait_child == True)
                wait(NULL);
        }
    }

    return 0;
}

/* load_history */
int load_history(char *command, char *history)
{
    if (history[0] == 0)
    {
        printf("No commands in history\n");
        return -1;
    }

    strcpy(command, history);
    printf("%s\n", command);

    return 0;
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

/* identify_operators */
void identify_operators(int argc, char *args[])
{
    for (int i = 0; i < argc; i++)
    {
        if (args[i][0] == '>')
        {
            mode = redirect_out;
            args[i] = NULL;
            file_name = args[i + 1];
            break;
        }
        if (args[i][0] == '<')
        {
            mode = redirect_in;
            args[i] = NULL;
            file_name = args[i + 1];
            break;
        }
        if (args[i][0] == '|')
        {
            mode = piped;
            args[i] = NULL;
            args2 = args + (i + 1);
            break;
        }
        if (args[i][0] == '&')
        {
            wait_child = False;
            args[i] = NULL;
            break;
        }
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
        perror("Failed to open input file");
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
        perror("Failed to create output file");
        return -1;
    }

    dup2(fd, STDOUT_FILENO);
    close(fd);

    return 0;
}

int pipe_commands(char *args[], char *args2[])
{
    pid_t pid;
    int fd[2];

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
        fprintf(stderr, "First Execution Failed\n");
        exit(1);
    }
    else // Parent process
    {
        dup2(fd[READ_END], STDIN_FILENO);
        close(fd[READ_END]);
        close(fd[WRITE_END]);
        execvp(args2[0], args2);
        fprintf(stderr, "Second Execution Failed\n");
        exit(1);
    }
}