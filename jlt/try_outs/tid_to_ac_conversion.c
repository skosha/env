#include "common.h"

typedef enum ac_params
{
    AC_BK = 0,
    AC_BE = 1,
    AC_VI = 2,
    AC_VO = 3,
    AC_MAX = 4,
} ac_params_t;

char *ac_names[AC_MAX] = {
    "AC_BK",
    "AC_BE",
    "AC_VI",
    "AC_VO",
};

/* TID
 * 0        AC_BE
 * 1        AC_BK
 * 2        AC_BK
 * 3        AC_BE
 * 4        AC_VI
 * 5        AC_VI
 * 6        AC_VO
 * 7        AC_VO
 */
//#define TID_TO_AC_INDEX(p)  ((ac_params_t)((p < 2) ? (p^1) : p))
#define TID_TO_AC_INDEX(p)  (((p < 2) ? (p^1) : (p < 4) ? (p&0x1) : (p>>1)))

int main()
{
    for (uint8_t tid = 0; tid < 8; tid++)
    {
        printf("tid %d, %s\n", tid, ac_names[TID_TO_AC_INDEX(tid)]);
    }

    return 0;
}
