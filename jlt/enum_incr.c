#include "common.h"

typedef enum
{
    VALUE_1 = 1,
    VALUE_2 = 2,
    VALUE_3 = 3,
    VALUE_4 = 4,
    VALUE_MAX
} value_t;

int main()
{
    for (value_t i = VALUE_1; i < VALUE_MAX; i++)
    {
        printf("value of i: %d\n", i);
    }

    return 0;
}
