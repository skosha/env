#include "common.h"

void main(void)
{
    uint64_t bmask = 0;
    for (uint8_t i = 64; i > 0; i--)
    {
        bmask = (1 << i - 1);
        printf("%d: 0x%lx\n", i, bmask);
    }

    printf("0x%lx\n", bmask);
}
