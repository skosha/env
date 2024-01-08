#include "common.h"

void play_with_const_ptr(const uint32_t *ptr_in)
{
    if (ptr_in)
    {
        const uint32_t *local_ptr = ptr_in;
    }
    else
    {
        const uint32_t *local_ptr = NULL;
    }

    if (local_ptr)
    {
        printf("val: 0x%x\n", *local_ptr);
    }
}

void main(void)
{
    uint32_t some_var = 0x80808080;
    const uint32_t *p_some_var = &some_var;

    play_with_const_ptr(p_some_var);
}
