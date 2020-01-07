#include "common.h"

typedef struct example_s
{
    uint16_t var1;
    uint16_t var2;
    uint32_t var3;
} example_t;

#define compare_val(t1, t2, type, member)       \
    do                                          \
    {                                           \
        typeof((t1)->member) t1_var = *(typeof((t1)->member) *)((char *)t1 + offsetof(type, member));    \
        typeof((t1)->member) t2_var = *(typeof((t1)->member) *)((char *)t2 + offsetof(type, member));    \
        if (t1_var == t2_var)                                                               \
            printf("t1 (%d) == t2 (%d)\n", t1_var, t2_var);                                                             \
        else if (t1_var > t2_var)                                                           \
            printf("t1 (%d) > t2 (%d)\n", t1_var, t2_var);                                                              \
        else                                                                                \
            printf("t1 (%d) < t2 (%d)\n", t1_var, t2_var);                                                              \
    } while(0)

int main()
{
    example_t t1 = {1, 2, 3541926};
    example_t t2 = {3, 2, 541926};

    compare_val(&t1, &t2, example_t, var1);
    compare_val(&t1, &t2, example_t, var2);
    compare_val(&t1, &t2, example_t, var3);

    return 0;
}
