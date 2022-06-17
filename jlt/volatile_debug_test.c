#include "common.h"

volatile time_t wlan_task_debug_time[16] = {0};
volatile uint8_t debug_time_index = 0;

void wlan_loop(void)
{
    uint32_t num_loop = 0;
    while (num_loop++ < 20)
    {
        wlan_task_debug_time[debug_time_index++] = time(NULL);
        debug_time_index &= 0xf;
        printf("index: %d\n", debug_time_index);
        sleep(1);
    }
}

void print_debug(void)
{
    for (uint8_t i = 0; i < 16; i++)
    {
        printf("%d: 0x%0lx\n", i, wlan_task_debug_time[i]);
    }
}

void main(void)
{
    wlan_loop();
    print_debug();
}
