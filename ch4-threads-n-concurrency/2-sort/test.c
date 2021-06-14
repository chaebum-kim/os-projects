
#include <stdio.h>
#include "sort.h"

int main(int argc, char *argv[])
{
    int nums[10] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8};
    int sorted_nums[10];

    // Print out the original number
    printf("Numbers: ");
    for (int i = 0; i < 10; i++)
        printf("%d ", nums[i]);
    printf("\n");

    // Sort the numbers
    sort(nums, sorted_nums, 10);

    // Print out the result
    printf("Sorted numbers: ");
    for (int i = 0; i < 10; i++)
        printf("%d ", sorted_nums[i]);
    printf("\n");

    return 0;
}
