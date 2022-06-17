#include "common.h"

#define X_NUM       2
#define Y_NUM       3
#define Z_NUM       4

typedef uint8_t my_array_t[X_NUM][Y_NUM][Z_NUM];

void print_3d_array(uint8_t arr[X_NUM][Y_NUM][Z_NUM])
{
    for (uint8_t x = 0; x < X_NUM; x++)
    {
        for (uint8_t y = 0; y < Y_NUM; y++)
        {
            for (uint8_t z = 0; z < Z_NUM; z++)
            {
                printf("%d,%d,%d: %d; ", x, y, z, arr[x][y][z]);
            }
            printf("\n");
        }
    }
}

void populate_3d_array(uint8_t arr[X_NUM][Y_NUM][Z_NUM])
{
    for (uint8_t x = 0; x < X_NUM; x++)
    {
        for (uint8_t y = 0; y < Y_NUM; y++)
        {
            for (uint8_t z = 0; z < Z_NUM; z++)
            {
                arr[x][y][z] = x + y + z;
            }
        }
    }
}

my_array_t my_arr = {0};

void main(void)
{
    my_array_t *ptr = &my_arr;
    populate_3d_array(*ptr);
    print_3d_array(*ptr);
}
