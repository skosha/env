#include "common.h"

typedef struct commonData_s
{
    uint32_t data;
} commonData_t;

commonData_t g_data = {0xdeadbeef};

bool fn_callback(void *data)
{
    commonData_t *p_data = *(commonData_t **)data;

    if (p_data == NULL)
    {
        printf("Null data\n");
        return false;
    }
    else
    {
        printf("Data: 0x%08x\n", p_data->data);
    }

    return true;
}

int main()
{
    commonData_t *ptr_common_data = &g_data;

    fn_callback(&ptr_common_data);

    ptr_common_data = NULL;

    fn_callback(&ptr_common_data);

    return 0;
}
