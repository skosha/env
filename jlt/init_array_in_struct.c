#include "common.h"

typedef struct PACKED misc_tag_s
{
    uint8_t tag[11];
} misc_tag_t;

#define TAG_1           (0x11)
#define TAG_2           (0x22)

void print_tag(misc_tag_t *in_tag)
{
    if (in_tag->tag[0] == TAG_1)
    {
        printf("It is tag 1\n");
    }
    else if (in_tag->tag[0] == TAG_2)
    {
        printf("It is tag 2\n");
    }
    else
    {
        printf("Error tag %d\n", in_tag->tag[0]);
    }
}

int main()
{
    misc_tag_t tag_1 = { .tag = TAG_1 };
    misc_tag_t tag_2 = { .tag = TAG_2 };
    misc_tag_t tag_3 = { .tag = 9 };

    print_tag(&tag_1);
    print_tag(&tag_2);
    print_tag(&tag_3);

    return 0;
}
