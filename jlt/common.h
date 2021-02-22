#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>

#define GCC_ATTRIBUTE(x) __attribute__ ((x))

#ifndef NORETURN
#define NORETURN GCC_ATTRIBUTE(__noreturn__)
#endif
#ifndef NOINLINE
#define NOINLINE GCC_ATTRIBUTE(__noinline__)
#endif
#ifndef ARG_UNUSED
#define ARG_UNUSED GCC_ATTRIBUTE(__unused__)
#endif
#ifndef ALIGNED
#define ALIGNED(x) GCC_ATTRIBUTE(__aligned__ (x))
#endif
#ifndef PACKED
#define PACKED GCC_ATTRIBUTE(__packed__)
#endif
#ifndef SECTION
#define SECTION(x) GCC_ATTRIBUTE(section(x))
#endif
#ifndef WORD_ALIGNED
#define WORD_ALIGNED ALIGNED(4)
#endif

#ifndef UNUSED
#define UNUSED(x)       ((void)(x))
#endif

#ifndef CTYPEOF
#define CTYPEOF(a)      (__typeof__(a))
#endif

/* Get the size of a member of a struct */
#define MEMBER_SIZE(type, member)       sizeof(((type *)0)->member)


#define SET_NTH_BIT_TYPE(wd,n,type)     ((wd) |= (type)(1 << (n)))
#define CLEAR_NTH_BIT_TYPE(wd,n,type)   ((wd) &= ~((type)(1 << (n))))
#define IS_NTH_BIT_TYPE_SET(wd,n,type)  ((wd) & (type)(1 << (n)))

#define SET_NTH_BIT(wd,n)               ((wd) |= (CTYPEOF((wd)) 1 << (n)))
#define IS_NTH_BIT_SET(wd, n)           ((((wd) >> (n)) & 1) != 0)

#define IS_VALID_PTR(ptr)               (NULL!=(ptr))

#define STRINGIFY(x)                    #x
#define EXPAND_AND_STRINGIFY(x)         STRINGIFY(x)

/**
 * Get address of structure given address of member.
 */
#define STRUCT_FROM_MEMBER(sname, mname, maddr)         ((sname *) ((uintptr_t) (maddr) - offsetof(sname, mname)))

/**
 * Get address of const structure given address of member.
 */
#define STRUCT_FROM_CONST_MEMBER(sname, mname, maddr)   ((const sname *) ((uintptr_t) (maddr) - offsetof(sname, mname)))

#endif /* !__COMMON_H__ */
