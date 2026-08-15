#include "cmd_handler.h"
#include "cp15.h"

void do_CPACR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, CPACR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c1, c0, 2" : "+r" (*val));
#endif
}

void do_FCSEIDR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c13, c0, 0" : "+r" (*val));
#endif
}

void do_RMR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, RMR_EL1" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_RVBAR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, RVBAR_EL1" : "+r" (*val));
#else
    *val = 0;
#endif
}
