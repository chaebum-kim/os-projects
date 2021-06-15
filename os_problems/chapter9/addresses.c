/* addresses.c
*  A prgram that is passed a virtual address in decimal on the comand line
*  and have it ouput the page number and offset for the given address.
*/

#include <stdlib.h>
#include <stdio.h>

#define PAGE_SIZE 4096

typedef unsigned long ulong;

int main(int argc, char *argv[])
{
    ulong address, page_num, offset;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./addresses <virtual address>\n");
        return 1;
    }

    // Get command line argument
    address = strtoul(argv[1], NULL, 0);

    // Get the page number
    page_num = address / PAGE_SIZE;

    // Get the offset
    offset = address % PAGE_SIZE;

    // Output the result
    printf("The address %lu contains:\npage number = %lu\noffset = %lu\n", address, page_num, offset);

    return 0;
}