#include "common.h"

#define A_CONST_VAL         (50)

static uint16_t get_const_val()
{
    return A_CONST_VAL;
}

void main(void)
{
    int16_t my_val = 40;
    printf("%d\n", (int)(my_val - get_const_val()));
    printf("%d\n", (my_val - (int16_t)get_const_val()));
}
