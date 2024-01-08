#include "common.h"

typedef enum MyEnum
{
    VAL_1 = 1,
    VAL_2 = 2,
    VAL_MAX,
} MyEnum;

void print(MyEnum val)
{
    printf("%d\n", val);
}

void main(void)
{
    for (uint8_t i = 0; i < 5; i++)
    {
        print(i);
    }
}
