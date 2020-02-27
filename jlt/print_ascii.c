/* Example to print ascii values from char */

#include "common.h"

int main()
{
    uint8_t code[3] = {0x47, 0x42, '\0'};

    printf("%c%c\t%x%x\n", code[0], code[1], code[0], code[1]);
    printf("%s\n", code);
    return 0;
}
