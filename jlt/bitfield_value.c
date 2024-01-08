#include "common.h"

typedef struct PACKED my_struct_t
{
    uint8_t val_4_bits:4;
    bool    bool_val_1:1;
    bool    bool_val_2:1;
    uint8_t val_2_bits_1:2;
} my_struct_t;

enum
{
    VAL_1 = 1,
    VAL_2,
    VAL_3,
    VAL_4,
    VAL_5,
};

void main(void)
{
    my_struct_t a = { .val_4_bits = 5, .val_2_bits_1 = 2, .bool_val_1 = true, .bool_val_2 = false };

    if (a.val_4_bits == VAL_5)
    {
        printf("its 5!!!\n");
    }
    else
    {
        printf("booo!!\n");
    }
}
