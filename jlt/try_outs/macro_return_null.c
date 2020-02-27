#include "common.h"

typedef struct my_struct
{
    uint8_t   len;
    uint8_t   control;
    uint8_t   data[];
} my_struct_t;

#define IS_DATA_PRESENT(attr)       (attr->len > (sizeof(__typeof__(*attr)) - sizeof(uint8_t)))
#define GET_DATA_PTR(attr)          (IS_DATA_PRESENT(attr) ? (attr)->data : NULL)

int main()
{
    my_struct_t *my_attr = malloc(sizeof(my_struct_t) + sizeof(uint8_t) * 4);

    my_attr->len = sizeof(my_struct_t) + sizeof(uint8_t) * 4 - sizeof(uint8_t);

    uint8_t buffer[4] = {0x12, 0x34, 0x56, 0x78};
    memcpy(my_attr->data, buffer, 4);

    printf("%s\n", IS_DATA_PRESENT(my_attr) ? "true" : "false");
    printf("%d %ld\n", my_attr->len, sizeof(__typeof__(*my_attr)));

    uint8_t *ptr = GET_DATA_PTR(my_attr);
    printf("my_attr->data: 0x%08x ptr: 0x%08x\n", (uint32_t)(my_attr->data), (uint32_t)ptr);
    printf("0x%02x\n", (ptr) ? *ptr : 0x00);

    free(my_attr);

    return 0;
}
