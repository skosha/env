#include "common.h"

typedef struct gap_struct
{
    uint8_t      param1;
    uint16_t     param2;
    uint8_t      param3;
} gap_struct;

typedef struct gap_struct_node
{
    uint8_t     dummy;
    gap_struct  var1;
    uint32_t    dummy_2;
} gap_struct_node;

#define NUM_LIST    (5)

gap_struct get_new_struct(uint8_t param1, uint16_t param2, uint8_t param3)
{
    gap_struct local_var = {.param1 = param1,
                            .param2 = param2,
                            .param3 = param3};

    return local_var;
}

void create_var_list(gap_struct_node *list, uint8_t instance)
{
    for (uint8_t i = 0; i < NUM_LIST; i++)
    {
        uint8_t base = i + instance;
        gap_struct temp = get_new_struct(base, base << 8, base+1);
        list[i].dummy = base;
        list[i].var1 = temp;
        list[i].dummy_2 = 1 << i;
    }
}

void main(void)
{
    gap_struct_node *list1 = malloc(sizeof(gap_struct_node) * NUM_LIST);
    gap_struct_node *list2 = malloc(sizeof(gap_struct_node) * NUM_LIST);

    int result = memcmp(list1, list2, sizeof(gap_struct_node) * NUM_LIST);

    printf("result: %d\n", result);
}
