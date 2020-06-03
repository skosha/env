#include "common.h"

typedef struct bitfields_s
{
    uint8_t use_1:1;
    uint8_t use_2:1;
} bitfields_t;

typedef struct composite_s
{
    union
    {
        bitfields_t     uses;
        uint8_t         bits;
    } u;
} composite_t;

bitfields_t default_val = { true, false };

void main(void)
{
    bitfields_t compare_val_1 = { true, false };
    bitfields_t compare_val_2 = { true, compare_val_1.use_2 == true};

    if ((uint8_t)*(uint8_t *)&compare_val_1 == (uint8_t)*(uint8_t *)&default_val)
    {
        printf("val 1 is defined\n");
    }

    if ((uint8_t)*(uint8_t *)&compare_val_2 == (uint8_t)*(uint8_t *)&default_val)
    {
        printf("val 2 is defined\n");
    }
}
