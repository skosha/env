#include "common.h"

void print_block(void *block, size_t num_block_bytes)
{
    uint8_t *ptr = (uint8_t *)block;
    for (uint8_t i = 0; i < num_block_bytes; i++)
    {
        printf("0x%0x, ", ptr[i]);
    }
    printf("\n");
}

void keep_n_bits(void *block, size_t num_bits_set, size_t num_block_bytes)
{
    size_t byte_idx = 0;
    uint8_t *ptr = (uint8_t *)block;
    if (num_bits_set == 0)
    {
        memset(ptr, 0, num_block_bytes);
        return;
    }

    for (byte_idx = 0; byte_idx < num_block_bytes; byte_idx++)
    {
        for (size_t bit_idx = 0; bit_idx < 8; bit_idx++)
        {
            if (num_bits_set == 0)
            {
                CLEAR_NTH_BIT_TYPE(ptr[byte_idx], bit_idx, uint8_t);
            }
            else if (IS_NTH_BIT_SET(ptr[byte_idx], bit_idx))
            {
                num_bits_set--;
            }
        }

        if (num_bits_set == 0)
        {
            break;
        }
    }

    if (++byte_idx < num_block_bytes)
    {
        memset(&ptr[byte_idx], 0, num_block_bytes - byte_idx);
    }
}

void main()
{
    uint8_t array_1[4] = {0xff, 0x0f, 0xf0, 0xff};

    print_block(array_1, 4);
    keep_n_bits(array_1, 14, 4);
    print_block(array_1, 4);
}
