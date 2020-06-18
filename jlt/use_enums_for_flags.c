#include "common.h"

typedef enum
{
    FLAG_POS_1  = 0x01,
    FLAG_POS_2  = 0x02,
    FLAG_POS_3  = 0x04,
    FLAG_POS_4  = 0x08,
    FLAG_POS_5  = 0x10,
} flag_enum_t;


int main()
{
    uint8_t my_flag = FLAG_POS_1 | FLAG_POS_3 | FLAG_POS_5;

    flag_enum_t flags = (flag_enum_t) my_flag;
    flag_enum_t flags_2 = FLAG_POS_2 | FLAG_POS_4;

    printf("my_flag: 0x%0x, flags: 0x%0x, flags_2: 0x%02x\n", my_flag, flags, flags_2);

    return 0;
}
