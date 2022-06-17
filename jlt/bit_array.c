#include "common.h"

uint8_t getBit(char *array, uint8_t bit)
{
    uint8_t byte_index = (bit / 8);
    uint8_t bit_index = 7 - (bit % 8);
    uint8_t mask = 1 << bit_index;
    printf("byte_index: %d, bit_index %d, mask %d, array_byte: 0x%02x\n", byte_index, bit_index, mask, array[byte_index]);
    return (mask & array[byte_index]);
}

uint8_t getBits(char *array, uint8_t start_bit, uint8_t end_bit)
{
    uint8_t start_byte_index = (start_bit / 8);
    uint8_t start_bit_index = 7 - (start_bit % 8);
    uint8_t end_byte_index = (end_bit / 8);
    uint8_t end_bit_index = 7 - (end_bit % 8);
    uint32_t mask = (1 << (end_bit - start_bit + 1)) - 1;

    uint32_t ret = 0;
    for (uint8_t i = start_byte_index; i <= end_byte_index; i++)
    {
        ret <<= 8;
        ret |= array[i];
    }
    printf("ret 0x%08x\n", ret);

    return (ret >> end_bit_index) & mask;
}

void print_byte_in_binary(uint8_t byte, char *prefix)
{
    char b[9];
    b[0] = '\0';

    for (uint8_t i = 128; i > 0; i >>= 1)
    {
        strcat(b, ((byte & i) ? "1" : "0"));
    }

    printf("%s: %s\n", prefix, b);
}

void main(void)
{
    uint8_t array[6] = {0x00, 0x00, 0x02, 0x88, 0x08, 0x13};

    print_byte_in_binary(getBit(array, 47), "47");
    print_byte_in_binary(getBit(array, 46), "46");
    print_byte_in_binary(getBit(array, 45), "45");
    print_byte_in_binary(getBit(array, 44), "44");
    print_byte_in_binary(getBits(array, 43, 44), "[43:44]");
}
