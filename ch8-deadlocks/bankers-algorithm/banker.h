#include <stdio.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 4

int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

void init_available(int argc, char *argv[]);
void init_maximum(char *filename);
void init_need(void);
int request_resources(int customer_num, int request[]);
void release_resources(int customer_num, int release[]);
int is_safe();

int compare_array(int *array1, int *array2, int length);