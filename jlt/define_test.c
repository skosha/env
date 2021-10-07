#include "common.h"

void main(void)
{
#if defined MACRO_1 || defined MACRO_2
    printf("either of macro_1 or macro_2 defined\n");
#endif

#if !defined MACRO_1 && !defined MACRO_2
    printf("neither of macro_1 or macro_2 defined\n");
#endif

#if defined MACRO_1 && defined MACRO_2
    printf("both of macro_1 or macro_2 defined\n");
#endif

#if defined MACRO_1 && !defined MACRO_2
    printf("Only macro_1 defined\n");
#endif
}
