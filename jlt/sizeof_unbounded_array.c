#include "common.h"

#define SOME_STR    \
    0x20, 0x02,     \
    0xde, 0xad,     \
    0xbe, 0xef

static uint8_t *get_some_str()
{
    uint8_t a_some_str[] = {
        SOME_STR
    };

    printf("length of SOME_STR: %ld\n", sizeof(a_some_str));
    uint8_t *p_some_str = &a_some_str[0];
    return p_some_str;
}

void main(void)
{
    uint8_t *str = get_some_str();
    printf("length of SOME_STR: %ld\n", sizeof(str));
    printf("length of SOME_STR: %ld\n", sizeof(SOME_STR));
}
