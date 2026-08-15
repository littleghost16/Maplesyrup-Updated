#include "cmd_handler.h"
#include "cp15.h"

void do_DBGDIDR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p14, 0, %0, c0, c0, 0" : "+r" (*val));
#endif
}

void do_DBGAUTHSTATUS_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, DBGAUTHSTATUS_EL1" : "+r" (*val));
#else
    ASM_01("MRC p14, 0, %0, c7, c14, 6" : "+r" (*val));
#endif
}

void do_DBGDRAR_read(unsigned long long *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, MDRAR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p14, 0, %0, c1, c0, 0" : "+r" (*val));
#endif
}

void do_DBGDSCR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, MDSCR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p14, 0, %0, c1, c0, 0" : "+r" (*val));
#endif
}
