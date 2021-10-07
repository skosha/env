#include "common.h"

typedef enum
{
    ENUM_VAL_INVALID = 0,
    ENUM_VAL_1       = 1,
    ENUM_VAL_2       = 2,
    ENUM_VAL_3       = 3,
    ENUM_VAL_4       = 4,
    ENUM_VAL_5       = 5,
    ENUM_VAL_6       = 6,
    ENUM_VAL_7       = 7,
    ENUM_VAL_8       = 8,
    ENUM_VAL_9       = 9,
    ENUM_VAL_10       = 10,
} ENUM_TEST;

void main(void)
{
    ENUM_TEST code = 100;

    printf("enum code: %d\n", code);
}
