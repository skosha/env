#include "common.h"

void print_negative(void)
{
    printf("negative\n");
}

void print_positive(void)
{
    printf("positive\n");
}

void main(void)
{
    int num = -1;

    (num > 0) ? print_positive() : print_negative;
}
