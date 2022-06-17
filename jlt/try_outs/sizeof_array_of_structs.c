#include "common.h"

typedef struct my_struct_s
{
    uint32_t    val1;
    uint32_t    val2;
    uint16_t    val3;
    bool        flag1;
} my_struct_t;

my_struct_t shared_data[11] = {0};

void main()
{
    printf("size of shared_data: %ld\n", sizeof(shared_data));
    printf("num of shared_data: %ld\n", sizeof(shared_data)/sizeof(my_struct_t));
}
