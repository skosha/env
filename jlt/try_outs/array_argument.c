#include "common.h"

typedef struct my_struct
{
    uint32_t    val1;
    uint32_t    val2;
} my_struct_t;

#define ARRAY_LEN       (5)

void array_pass_value(my_struct_t args[ARRAY_LEN])
{
    printf("array_pass_value: 0x%lx\n", (intptr_t)args);
}

void array_pass_reference(my_struct_t *args)
{
    printf("array_pass_value: 0x%lx\n", (intptr_t)args);
}

void main(void)
{
    my_struct_t test_array[ARRAY_LEN] = {0};

    printf("test_array: 0x%lx\n", (intptr_t)(&test_array[0]));

    array_pass_value(test_array);
    array_pass_reference(&test_array[0]);
}
