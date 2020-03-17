#include "common.h"

#define _JOIN_2(x, y)       x ## y
#define _JOIN_2b(x, y)      _JOIN_2(x, y)

#define MAKE_ROW_NAME(s)    _JOIN_2b(s, Table_row)
#define MAKE_FN_NAME(s)     _JOIN_2b(getrow_, s)
#define MAKE_ROW_MEM(s)     _JOIN_2b(_JOIN_2b(row, .), s)

#define test_string(s)      \
    do                      \
    {                       \
        MAKE_ROW_NAME(s) row = { 0 };   \
        MAKE_FN_NAME(s)(&row);  \
        printf("row val: %d\n", row. ## s); \
    } while(0)

typedef struct firstTable_row
{
    uint32_t    first;
} firstTable_row;

typedef struct secondTable_row
{
    uint32_t    second;
} secondTable_row;

void getrow_first(firstTable_row *row)
{
    row->first = 0xdead;
    printf("this is table row first\n");
}

void getrow_second(secondTable_row *row)
{
    row->second = 0xbeef;
    printf("this is table row second\n");
}

int main()
{
    test_string(first);
    test_string(second);

    return 0;
}
