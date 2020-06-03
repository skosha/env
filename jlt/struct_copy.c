#include "common.h"


typedef struct my_struct_s
{
    uint8_t data1;
    uint8_t data2;
    uint8_t data3;
} my_struct_t;

void copy_default(my_struct_t *ptr)
{
    my_struct_t data = { .data1 = 0x01, .data2 = 0x02, .data3 = 0xf3 };

    *ptr = data;
}

my_struct_t populate_data()
{
    my_struct_t data = {.data1 = 0xf1, .data2 = 0xf2, .data3 = 0x03 };

    return data;
}

int main()
{
    my_struct_t data_out1;
    my_struct_t data_out2 = populate_data();

    copy_default(&data_out1);

    printf("0x%x 0x%x 0x%x\n", data_out1.data1, data_out1.data2, data_out1.data3);
    printf("0x%x 0x%x 0x%x\n", data_out2.data1, data_out2.data2, data_out2.data3);

    return 0;
}
