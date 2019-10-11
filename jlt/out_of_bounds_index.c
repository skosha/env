#include "common.h"

#define MAX_VALUES      5
uint32_t values[MAX_VALUES] =
{
    0x0101,
    0x0102,
    0x0103,
    0x0104,
    0x0105
};

int main()
{
    uint8_t i;
    for (i = 0; i < MAX_VALUES; i++)
    {
        printf("incr i: %d\n", i);
    }

    printf("--> i = %d\n", i);

    for (i = MAX_VALUES - 1; i > 0; --i)
    {
        printf("decr i: %d\n", i);
    }

    printf("--> i = %d\n", i);

    return 0;
}
