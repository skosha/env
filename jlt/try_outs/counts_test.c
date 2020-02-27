#include "common.h"

#define A_START_NUM     5
#define B_START_NUM     1
#define C_START_NUM     3

static uint32_t a_count = A_START_NUM;
static uint32_t b_count = B_START_NUM;
static uint32_t c_count = C_START_NUM;

static uint32_t a_counter = 0;
static uint32_t b_counter = 0;
static uint32_t c_counter = 0;

static uint32_t expected_add_count = 0;
static uint32_t expected_del_count = 0;
static uint32_t expected_tot_count = 0;


static void init_counts()
{
    a_count = A_START_NUM + 1;
    b_count = B_START_NUM + 1;
    c_count = C_START_NUM + 1;

    a_counter = A_START_NUM;
    b_counter = B_START_NUM;
    c_counter = C_START_NUM;

    expected_tot_count = 0;
}

static uint32_t numberOfSetBits(uint32_t num)
{
     num = num - ((num >> 1) & 0x55555555);
     num = (num & 0x33333333) + ((num >> 2) & 0x33333333);
     return (((num + (num >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

static void update_count()
{
    uint32_t tot_count = 0;

    a_count = (a_count > 0) ? a_count - 1 : 0;
    b_count = (b_count > 0) ? b_count - 1 : 0;
    c_count = (c_count > 0) ? c_count - 1 : 0;

    if (a_count > 0)
    {
        a_counter = a_count;
        tot_count++;
    }
    else if (a_counter == 1)
    {
        a_counter = 0;
        tot_count++;
    }

    if (b_count > 0)
    {
        b_counter = b_count;
        tot_count++;
    }
    else if (b_counter == 1)
    {
        b_counter = 0;
        tot_count++;
    }

    if (c_count > 0)
    {
        c_counter = c_count;
        tot_count++;
    }
    else if (c_counter == 1)
    {
        c_counter = 0;
        tot_count++;
    }

    expected_add_count = (tot_count > expected_tot_count) ? tot_count - expected_tot_count : 0;
    expected_del_count = (expected_tot_count > tot_count) ? expected_tot_count - tot_count : 0;
    expected_tot_count = tot_count;
}

static void print_counters()
{
    printf("a_counter: %d\n", a_counter);
    printf("a_count: %d\n", a_count);

    printf("b_counter: %d\n", b_counter);
    printf("b_count: %d\n", b_count);

    printf("c_counter: %d\n", c_counter);
    printf("c_count: %d\n", c_count);

    printf("expected_add_count: %d\n", expected_add_count);
    printf("expected_del_count: %d\n", expected_del_count);
    printf("expected_tot_count: %d\n", expected_tot_count);
}

int main()
{
    init_counts();
    print_counters();
    printf("---------------\n");

    update_count();
    print_counters();
    printf("---------------\n");

    update_count();
    print_counters();
    printf("---------------\n");

    update_count();
    print_counters();
    printf("---------------\n");

    update_count();
    print_counters();
    printf("---------------\n");

    update_count();
    print_counters();
    printf("---------------\n");

    update_count();
    print_counters();
    printf("---------------\n");

    update_count();
    print_counters();
    printf("---------------\n");

    return 0;
}
