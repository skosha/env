#include "common.h"

uint8_t g_counter = 0;

uint8_t get_next_count()
{
    return g_counter++;
}

int main()
{
    for (uint16_t i = 0; i < 280; i++)
    {
        printf("%d\n", i);
    }
    return 0;
}
