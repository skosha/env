#include "common.h"

enum
{
    MAC_BASIC_RATE11A_06MBPS_MASK                                                    = 0x0001,
    MAC_BASIC_RATE11A_09MBPS_MASK                                                    = 0x0002,
    MAC_BASIC_RATE11A_12MBPS_MASK                                                    = 0x0004,
    MAC_BASIC_RATE11A_18MBPS_MASK                                                    = 0x0008,
    MAC_BASIC_RATE11A_24MBPS_MASK                                                    = 0x0010,
    MAC_BASIC_RATE11A_36MBPS_MASK                                                    = 0x0020,
    MAC_BASIC_RATE11A_48MBPS_MASK                                                    = 0x0040,
    MAC_BASIC_RATE11A_54MBPS_MASK                                                    = 0x0080,
    MAC_BASIC_RATE11B_01MBPS_MASK                                                    = 0x0100,
    MAC_BASIC_RATE11B_02MBPS_MASK                                                    = 0x0200,
    MAC_BASIC_RATE11B_5M5BPS_CCK_MASK                                                = 0x0400,
    MAC_BASIC_RATE11B_11MBPS_CCK_MASK                                                = 0x0800
};

#define MAC_BASIC_RATE11A_ALL \
    (MAC_BASIC_RATE11A_06MBPS_MASK | \
     MAC_BASIC_RATE11A_09MBPS_MASK | \
     MAC_BASIC_RATE11A_12MBPS_MASK | \
     MAC_BASIC_RATE11A_18MBPS_MASK | \
     MAC_BASIC_RATE11A_24MBPS_MASK | \
     MAC_BASIC_RATE11A_36MBPS_MASK | \
     MAC_BASIC_RATE11A_48MBPS_MASK | \
     MAC_BASIC_RATE11A_54MBPS_MASK)


#define O_11_MBPS (MAC_BASIC_RATE11A_12MBPS_MASK      | \
                   MAC_BASIC_RATE11A_18MBPS_MASK      | \
                   MAC_BASIC_RATE11A_24MBPS_MASK      | \
                   MAC_BASIC_RATE11A_36MBPS_MASK      | \
                   MAC_BASIC_RATE11A_48MBPS_MASK      | \
                   MAC_BASIC_RATE11A_54MBPS_MASK      | \
                   MAC_BASIC_RATE11B_11MBPS_CCK_MASK)


#define O_12_MBPS (MAC_BASIC_RATE11A_12MBPS_MASK      | \
                   MAC_BASIC_RATE11A_18MBPS_MASK      | \
                   MAC_BASIC_RATE11A_24MBPS_MASK      | \
                   MAC_BASIC_RATE11A_36MBPS_MASK      | \
                   MAC_BASIC_RATE11A_48MBPS_MASK      | \
                   MAC_BASIC_RATE11A_54MBPS_MASK)


#define O_13_MBPS (MAC_BASIC_RATE11A_18MBPS_MASK      | \
                   MAC_BASIC_RATE11A_24MBPS_MASK      | \
                   MAC_BASIC_RATE11A_36MBPS_MASK      | \
                   MAC_BASIC_RATE11A_48MBPS_MASK      | \
                   MAC_BASIC_RATE11A_54MBPS_MASK)

#define O_14_MBPS (MAC_BASIC_RATE11A_18MBPS_MASK      | \
                   MAC_BASIC_RATE11A_24MBPS_MASK      | \
                   MAC_BASIC_RATE11A_36MBPS_MASK      | \
                   MAC_BASIC_RATE11A_48MBPS_MASK      | \
                   MAC_BASIC_RATE11A_54MBPS_MASK)

#define STA_BASIC_RATE_6_MBPS       (MAC_BASIC_RATE11A_ALL              | \
                                     MAC_BASIC_RATE11B_5M5BPS_CCK_MASK  | \
                                     MAC_BASIC_RATE11B_11MBPS_CCK_MASK)
#define STA_BASIC_RATE_GT_13_MBPS   (MAC_BASIC_RATE11A_18MBPS_MASK      | \
                                     MAC_BASIC_RATE11A_24MBPS_MASK      | \
                                     MAC_BASIC_RATE11A_36MBPS_MASK      | \
                                     MAC_BASIC_RATE11A_48MBPS_MASK      | \
                                     MAC_BASIC_RATE11A_54MBPS_MASK)
#define STA_BASIC_RATE_12_MBPS      (STA_BASIC_RATE_GT_13_MBPS | MAC_BASIC_RATE11A_12MBPS_MASK)
#define STA_BASIC_RATE_11_MBPS      (STA_BASIC_RATE_12_MBPS | MAC_BASIC_RATE11B_11MBPS_CCK_MASK)

int main()
{
    printf("6mbps - 0x%04x\n", STA_BASIC_RATE_6_MBPS);
    printf("11mbps - 0x%04x\n", STA_BASIC_RATE_11_MBPS);
    printf("12mbps - 0x%04x\n", STA_BASIC_RATE_12_MBPS);
    printf("13mbps - 0x%04x\n", STA_BASIC_RATE_GT_13_MBPS);


    printf("11 - 0x%04x\n", O_11_MBPS);
    printf("12 - 0x%04x\n", O_12_MBPS);
    printf("13 - 0x%04x\n", O_13_MBPS);
    printf("14 - 0x%04x\n", O_14_MBPS);

    return 0;
}
