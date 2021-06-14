/* validator.c
*  A multithreaded program that determines whether the solution to 
*  a 9x9 Sudoku puzzle is valid.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define THREADS 27
#define LENGTH 9

// Structure for passing data to threads
typedef struct
{
    int row;
    int col;
    int box;
} parameters;

// Global variables
int sudoku[LENGTH][LENGTH];
int row_checks[LENGTH] = {0};
int col_checks[LENGTH] = {0};
int box_checks[LENGTH] = {0};

// Worker functions
void *check_row(void *param);
void *check_col(void *param);
void *check_box(void *param);

// Helper function
int load_file(char *argv);
int get_max_row(int box);
int get_max_col(int box);

int main(int args, char *argv[])
{
    pthread_t tids[THREADS] = {0};
    parameters *data[9];

    if (args != 2)
    {
        printf("Usage: ./validator <file name>\n");
        return 1;
    }

    // Load file
    if (load_file(argv[1]) != 0)
        return 1;

    // Print sudoku
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
            printf("%d ", sudoku[i][j]);
        printf("\n");
    }

    // Assingn data and create threads
    for (int i = 0; i < 9; i++)
    {
        data[i] = (parameters *)malloc(sizeof(parameters));
        data[i]->row = i;
        data[i]->col = i;
        data[i]->box = i;

        pthread_create(&(tids[i]), NULL, check_row, data[i]);
        pthread_create(&(tids[i + 9]), NULL, check_col, data[i]);
        pthread_create(&(tids[i + 18]), NULL, check_box, data[i]);
    }

    // Wait for the threads to exit
    for (int i = 0; i < THREADS; i++)
        pthread_join(tids[i], NULL);

    // Free data
    for (int i = 0; i < LENGTH; i++)
        free(data[i]);

    // Check the result
    for (int i = 0; i < LENGTH; i++)
    {
        if (!row_checks[i] || !col_checks[i] || !box_checks[i])
        {
            printf("The sudoku puzzle is not valid.\n");
            return 0;
        }
    }

    printf("The sudoku puzzle is valid.\n");
    return 0;
}

void *check_row(void *param)
{
    parameters *data = (parameters *)param;
    int row = data->row;
    int col;
    int nums[9] = {0};

    for (col = 0; col < 9; col++)
    {
        int num = sudoku[row][col];
        if (nums[num - 1]) // The number is repeated (not valid)
            break;
        else
            nums[num - 1] = 1; // Record the number
    }

    if (col >= 9)
        row_checks[row] = 1;

    pthread_exit(0);
}

void *check_col(void *param)
{
    parameters *data = (parameters *)param;
    int row;
    int col = data->col;
    int nums[9] = {0};

    for (row = 0; row < 9; row++)
    {
        int num = sudoku[row][col];
        if (nums[num - 1]) // The number is repeated (not valid)
            break;
        else
            nums[num - 1] = 1; // Record the number
    }

    if (row >= 9)
        col_checks[col] = 1;

    pthread_exit(0);
}

void *check_box(void *param)
{
    parameters *data = (parameters *)param;
    int box = data->box;
    int max_row = get_max_row(box);
    int max_col = get_max_col(box);
    int row = max_row - 2, col;
    int nums[9] = {0};
    int is_valid = 1;

    while (is_valid && row <= max_row)
    {
        col = max_col - 2;
        while (is_valid && col <= max_col)
        {
            int num = sudoku[row][col];
            if (nums[num - 1]) // The number is repeated (not valid)
                is_valid = 0;
            else
                nums[num - 1] = 1; // Record the number
            col++;
        }
        row++;
    }

    if (is_valid)
        box_checks[box] = 1;

    pthread_exit(0);
}

int get_max_row(int box)
{
    if (box <= 2)
        return 2;
    else if (box <= 5)
        return 5;
    else
        return 8;
}

int get_max_col(int box)
{
    int r = box % 3;
    if (r == 0)
        return 2;
    else if (r == 1)
        return 5;
    else
        return 8;
}

int load_file(char *argv)
{
    FILE *file = fopen(argv, "r");

    if (file == NULL)
        return 1;

    // Save the file to the sudoku array
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            fscanf(file, "%d, ", &(sudoku[row][col]));
            if (sudoku[row][col] == 0)
                return 1;
        }
    }

    fclose(file);

    return 0;
}