#include "cmd_handler.h"
#include "cp15.h"

void do_ISR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ISR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c12, c1, 0" : "+r" (*val));
#endif
}

void do_MVBAR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c12, c0, 1" : "+r" (*val));
#endif
}

void do_NSACR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c1, c1, 2" : "+r" (*val));
#endif
}

void do_SDER_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c1, c1, 1" : "+r" (*val));
#endif
}

void do_SCR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c1, c1, 0" : "+r" (*val));
#endif
}

void do_VBAR_read(retdatatype *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, VBAR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c12, c0, 0" : "+r" (*val));
#endif
}
