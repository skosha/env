#include "common.h"

#define MAX_NUM     (5)

void print_array(uint32_t array[MAX_NUM])
{
    printf("Array pointer - 0x%08x\n", (uint32_t)array);
}

void main(void)
{
    uint32_t my_array[MAX_NUM] = {0, 1, 2, 3, 4};

    printf("My Array pointer - 0x%08x\n", (uint32_t)my_array);
    print_array(my_array);
}
