#include "common.h"

#define LIST_SIZE       2

uint32_t *get_list(void)
{
    uint32_t list[LIST_SIZE] = { 0x1, 0x2 };

    return list;
}

void main(void)
{
    uint32_t my_list[LIST_SIZE] = get_list();
    printf("0: %d\n", my_list[0]);
    printf("1: %d\n", my_list[1]);
}
