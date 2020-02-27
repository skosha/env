#include "common.h"

#define COUNTER_START       1

uint8_t get_next_count()
{
    static uint8_t counter = COUNTER_START - 1;
    return (++counter < COUNTER_START) ? ++counter : counter;
}

int main()
{
    for (uint16_t i = 0; i < 260; i++)
    {
        printf("%d\n", get_next_count());
    }

    return 0;
}
