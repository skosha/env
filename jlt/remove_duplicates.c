#include "common.h"

#define NUM_K       (10)

int removeDuplicates(int* nums, int numsSize)
{
    int size = numsSize;
    int prev_num;

    prev_num = nums[0];
    int i = 1;
    while (i < size)
    {
        if (prev_num == nums[i])
        {
            for (int j = i; j < size - 1; j++)
            {
                nums[j] = nums[j+1];
            }
            size--;
        }
        else
        {
            prev_num = nums[i++];
        }
    }

    return size;
}

void main(void)
{
    int num_array[10] = { 1, 2, 4, 4, 5, 6, 6, 8, 8, 9 };

    int new_size = removeDuplicates(num_array, 10);

    printf("Function returned %d. And array: \n", new_size);
    for (int i = 0; i < new_size; i++)
    {
        printf("%d, ", num_array[i]);
    }
    printf("\n");
}
