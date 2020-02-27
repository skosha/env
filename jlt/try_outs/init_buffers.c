#include "common.h"

typedef struct header
{
    uint8_t     id;
    uint8_t     length;
} header_t;

#define HEADER_SIZE     sizeof(header_t)

typedef struct my_struct
{
    header_t    hdr;
    uint16_t    control;
    uint8_t     data[];
} my_struct_t;

typedef struct data_1
{
    header_t    hdr;
    uint32_t    counter;
} data_1_t;

#define DATA_1_SIZE     (sizeof(data_1_t) - HEADER_SIZE)
#define DATA_1_ID       (0x12)

typedef struct data_2
{
    header_t    hdr;
    uint32_t    mask;
    uint32_t    pos;
} data_2_t;

#define DATA_2_SIZE     (sizeof(data_2_t) - HEADER_SIZE)
#define DATA_2_ID       (0x34)

const data_1 var1 = {
                    .hdr = {
                        .id = DATA_1_ID,
                        .length = DATA_1_SIZE,
                    },
                    .counter = 10,
                    };

const data_1 var2 = {
                    .hdr = {
                        .id = DATA_1_ID,
                        .length = DATA_1_SIZE,
                    },
                    .counter = 0xdead,
                    };

const data_2 var3 = {
                    .hdr = {
                        .id = DATA_2_ID,
                        .length = DATA_2_SIZE,
                    },
                    .mask = 0xf000,
                    .pos = 31,
                    };

#define FRAME_SIZE      (sizeof(my_struct_t) + sizeof(var1) + sizeof(var2) + sizeof(var3))
#define FRAME_LENGTH    (FRAME_SIZE - HEADER_SIZE)

uint8_t frame[FRAME_SIZE] = {0};

void generate_frame()
{
    size_t offset = 0;

    frame[0] = 0x56;    /* id */
    frame[1] = FRAME_LENGTH;
    frame[2] = 0x01;
    frame[3] = 0x00;

}

int main()
{
    generate_frame();
    print_frame();

    return 0;
}
