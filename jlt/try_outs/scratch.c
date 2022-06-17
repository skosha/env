#include "common.h"

void scratch( const unsigned int const * const x)
{
    printf("x: %d\n", *x);
}

void main(void)
{
    uint32_t a = 6;
    int b = -20;
    int c = a+b;
    uint32_t d = a+b;

    printf("a+b = %d, c = %d, d = %d, a+b (u) = %u\n", a+b, c, d, a+b);
    (a+b)>6?puts(">6"):puts("<=6");

    scratch(&a);
}
