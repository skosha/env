#include "common.h"

typedef struct some_data
{
    uint32_t    param_1;
    uint32_t    param_2;
} some_data_t;

#define MAX_DATA_NODES  (3)

some_data_t data_set_1 = {0x0101, 0x1010};
some_data_t data_set_2 = {0x0202, 0x2020};
static some_data_t *ptr_array[MAX_DATA_NODES] = {&data_set_1, &data_set_2, NULL};

void main(void)
{
    some_data_t *ptrs[] = &ptr_array;

    for (uint8_t i = 0; i < MAX_DATA_NODES; i++)
    {
        if ((ptrs)[i] != NULL)
        {
            printf("val1: %d, val2: %d\n", (ptrs)[i]->param_1, (ptrs)[i]->param_2);
        }
    }
}
