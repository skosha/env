#include "common.h"

#define DEBUG   (1)

void ArrayChallenge(int arr[], int arrLength)
{
    /* Sort the array */
    for (uint8_t i = 0; i < (arrLength - 1); i++)
    {
        bool swapped = false;
        for (uint8_t j = 0; j < (arrLength - i - 1); j++)
        {
            //printf("iter: [%d][%d]\n", i, j);
            if (arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = true;
            }
        }

        if (!swapped)
        {
            break;
        }
    }

#ifdef DEBUG
    for (uint8_t i = 0; i < arrLength; i++)
    {
        printf("%d, ", arr[i]);
    }
    printf("\n");
#endif

    /* Initialize lcs data */
    uint8_t high_lcs_count = 1;
    uint8_t lcs_count = 1;
    for (uint8_t i = 1; i < arrLength; i++)
    {
        if (arr[i] == arr[i-1])
        {
            /* Ignore duplicates */
        }
        else if (arr[i] == (arr[i-1] + 1))
        {
            lcs_count++;
        }
        else
        {
            lcs_count = 1;
        }
        if (lcs_count > high_lcs_count)
        {
            high_lcs_count = lcs_count;
        }
    }

    printf("%d\n", high_lcs_count);
}

int main(void)
{
    //int A[] = {4, 3, 8, 1, 2, 6, 100, 9};
    int A[] = {11, 6, 6, 5, 7, 10, 1, 2, 3, 12, 9, 8};
    //int A[] = {12, 10, 2, 3, 11, 13, 100, 101, 5};
    //int A[] = {5, 15, 16, 21, 4, 5, 10, 9, 8, 22, 23, 7, 3, 2, 24, 1, 6};
    int arrLength = sizeof(A) / sizeof(*A);
    ArrayChallenge(A, arrLength);
    return 0;
}
