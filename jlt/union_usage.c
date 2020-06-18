#include "common.h"

typedef struct test_s
{
    union {
        struct {
            uint8_t data1;
            uint8_t data2;
        } data;
        uint32_t value;
    } u;
    uint8_t id;
} test_t;

void print(test_t *pr)
{
    if (pr->id == 4)
    {
        printf("data1 - %d, data2 - %d\n", pr->u.data.data1, pr->u.data.data2);
    }
    else
    {
        printf("value - %d\n", pr->u.value);
    }
}

int main()
{
    test_t ex_1 = { .u.data.data1 = 1, .u.data.data2 = 2, .id = 4 };
    test_t ex_2 = { .u.value = 1010, .id = 6 };

    print(&ex_1);
    print(&ex_2);

    return 0;
}
