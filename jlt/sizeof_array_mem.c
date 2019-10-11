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

    frame1.frame = malloc(128);
    frame_array[0].frame = malloc(128);

    printf("sizeof frame_array[0]: %ld\n", sizeof(frame_array[0]));
    printf("sizeof frame1: %ld\n", sizeof(frame1));

    return 0;
}
