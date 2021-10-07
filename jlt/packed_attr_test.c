#include "common.h"

typedef struct __attribute__((__packed__)) test_factor_row
{
    uint8_t var1;
    uint8_t var2;
    uint8_t var3;
} test_factor_row;

void main()
{
    printf("sizeof test_factor_row - %ld\n", sizeof(test_factor_row));
}
