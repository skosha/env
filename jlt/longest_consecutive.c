#include "common.h"

void ArrayChallenge(int arr[], int arrLength)
{
    struct {
        int last_val;
        int stream_len;
    } consecutive_arr[arrLength]; // max of arrLength streams can be there
    int num_streams = 0;

    consecutive_arr[num_streams].last_val = arr[0];
    consecutive_arr[num_streams].stream_len = 1;
    num_streams++;
    for (int i = 1; i < arrLength; i++)
    {
        bool stream_matched = false;
        for (int j = 0; j < num_streams; j++)
        {
            if (arr[i] == consecutive_arr[j].last_val+1 || arr)
        }

    }

    printf("%d", longest);
}

int main(void)
{
    // keep this function call here
    int A[] = [4, 3, 8, 1, 2, 6, 100, 9];
    int arrLength = sizeof(A) / sizeof(*A);
    ArrayChallenge(A, arrLength);
    return 0;
}
