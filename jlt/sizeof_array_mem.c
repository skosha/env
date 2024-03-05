#include "common.h"

typedef struct data_s
{
    bool is_valid :1;
    uint8_t *frame;
} data_t;

int main()
{
    data_t frame_array[5];
    data_t frame1;
    uint64_t array[3] = {0, 0, 0};

    frame1.frame = malloc(128);
    frame_array[0].frame = malloc(128);

    printf("sizeof frame_array[0]: %ld\n", sizeof(frame_array[0]));
    printf("sizeof frame1: %ld\n", sizeof(frame1));
    printf("sizeof array: %ld\n", sizeof(array));

    return 0;
}
