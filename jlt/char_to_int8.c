#include "common.h"

void print_hex(uint8_t char_num)
{
    printf("Your number in hex - 0x%x\n", char_num);
}

void print_int(int8_t int_num)
{
    printf("Your number in int - %d\n", int_num);
}

void main()
{
    bool is_hex;
    int temp;
    printf("Print hex: ");
    scanf("%d", &temp);
    is_hex = (bool)temp;

    if (is_hex)
    {
        int8_t num;
        printf("Enter your int number: ");
        scanf("%hhd", &num);
        print_hex(num);
    }
    else
    {
        uint8_t num;
        printf("Enter your hex number: ");
        scanf("%hhx", &num);
        print_int(num);
    }
}
