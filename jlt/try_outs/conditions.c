/* Check complex boolean conditions outcomes */

#include "common.h"

#define BOOL_2_NUM(val)     ((val) ? 1 : 0)

int main()
{
    bool a;
    bool b;
    bool c;

    printf("c = !(!a && b)\n");
    printf("a\tb\tc\n");
    for (uint8_t i = 0; i < 4; i++)
    {
        a = (i & 0x1) != 0;
        b = (i & 0x2) != 0;
        c = !(!a && b);
        printf("%d\t%d\t%d\n", BOOL_2_NUM(a), BOOL_2_NUM(b), BOOL_2_NUM(c));
    }
    printf("\n\n");

    printf("c = (a && !b)\n");
    printf("a\tb\tc\n");
    for (uint8_t i = 0; i < 4; i++)
    {
        a = (i & 0x1) != 0;
        b = (i & 0x2) != 0;
        c = (a && !b);
        printf("%d\t%d\t%d\n", BOOL_2_NUM(a), BOOL_2_NUM(b), BOOL_2_NUM(c));
    }
    printf("\n\n");

    printf("c = (a || !b)\n");
    printf("a\tb\tc\n");
    for (uint8_t i = 0; i < 4; i++)
    {
        a = (i & 0x1) != 0;
        b = (i & 0x2) != 0;
        c = (a && !b);
        printf("%d\t%d\t%d\n", BOOL_2_NUM(a), BOOL_2_NUM(b), BOOL_2_NUM(c));
    }
    printf("\n\n");

    return 0;
}
