#include "common.h"

void main()
{
    time_t t;
    srand((unsigned) time(&t));
    uint16_t mask = 0;

    for (uint8_t i = 0; i < 10; i++)
    {
        uint8_t num = 0;
        while (((1 << num) & mask) != 0)
        {
            num = rand() % 10;
        }
        mask |= (1 << num);
        printf("%d: %d\n", i, num);
    }
}
