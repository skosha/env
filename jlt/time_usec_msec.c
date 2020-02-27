#include "common.h"

#define MICROSECOND (1L)
#define MILLISECOND (1000L * MICROSECOND)
#define SECOND      (1000L * MILLISECOND)

int main()
{
    uint16_t ttl_sec = 5;
    uint32_t ttl_usec = ttl_sec * SECOND;

    printf("sec: %d, usec: %d\n", ttl_sec, ttl_usec);

    return 0;
}
