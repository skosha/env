/*
 * Problem:
 * Given an array of integer nums sorted in ascending order, find the starting and ending position of a given target value.
 * If the target is not found in the array, return [-1, -1].
 *
 * Example 1:
 * Input: nums = [5,7,7,8,8,10], target = 8
 * Output: [3,4]
 *
 * Example 2:
 * Input: nums = [5,7,7,8,8,10], target = 6
 * Output: [-1,-1]
 */

#include "common.h"

#define RETURN_ARRAY_SIZE       2
#define START_POS_IDX           0
#define END_POS_IDX             1

int default_return[2] = {-1, -1};

int *searchRange(int *nums, int numSize, int target, int *returnSize)
{
    int *result = malloc(RETURN_ARRAY_SIZE * sizeof(int));
    memcpy(result, default_return, RETURN_ARRAY_SIZE * sizeof(int));

    *returnSize = RETURN_ARRAY_SIZE;

    for (uint32_t i = 0; i < numSize; i++)
    {
        if (nums[i] < target)
        {
            continue;
        }

        if (nums[i] == target)
        {
            if (result[START_POS_IDX] == -1)
            {
                result[START_POS_IDX] = i;
            }
            result[END_POS_IDX] = i;
        }
        else
        {
            break;
        }
    }

    return result;
}

static void print_array(int *nums, int size)
{
    if (size <= 0)
    {
        return;
    }

    printf("[");
    printf("%d", nums[0]);
    for (uint32_t i = 1; i < size; i++)
    {
        printf(", %d", nums[i]);
    }
    printf("]");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("need input array\n");
        return -1;
    }

    int target = atoi(argv[1]);
    int inputSize = argc - 2;
    int *nums = malloc(inputSize * sizeof(int));
    for (uint32_t i = 0; i < inputSize; i++)
    {
        nums[i] = atoi(argv[i+2]);
    }

    int returnSize = 0;
    int *output = searchRange(nums, inputSize, target, &returnSize);

    printf("Input: ");
    print_array(nums, inputSize);
    printf(", target = %d\n", target);
    printf("Output: ");
    print_array(output, returnSize);
    printf("\n");

    free(nums);
    free(output);

    return 0;
}
