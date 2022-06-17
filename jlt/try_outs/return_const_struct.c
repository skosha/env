#include "common.h"

typedef struct mac_addr
{
    uint16_t  lo;
    uint16_t  mid;
    uint16_t  hi;
} mac_addr_t;

mac_addr_t mac_addr_zero = {0x1, 0x2, 0x3};

mac_addr_t get_zero_mac_addr(void)
{
    return mac_addr_zero;
}

void main(void)
{
    mac_addr_t addr = get_zero_mac_addr();

    printf("lo: 0x%04x, mid: 0x%04x, hi: 0x%04x\n", addr.lo, addr.mid, addr.hi);

}
