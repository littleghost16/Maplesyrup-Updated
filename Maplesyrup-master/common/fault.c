#include "cmd_handler.h"
#include "cp15.h"

void do_ADFSR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, AFSR0_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c5, c1, 0" : "+r" (*val));
#endif
}

void do_AIFSR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, AFSR1_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c5, c1, 1" : "+r" (*val));
#endif
}

void do_IFAR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c6, c0, 2" : "+r" (*val));
#endif
}

void do_IFSR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c5, c0, 1" : "+r" (*val));
#endif
}

void do_DFAR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c6, c0, 0" : "+r" (*val));
#endif
}

void do_DFSR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ESR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c5, c0, 0" : "+r" (*val));
#endif
}

void do_AFSR0_read(unsigned int *val1)
{
    if (val1 == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, AFSR0_EL1" : "+r" (*val1));
#else
    ASM_01("MRC p15, 0, %0, c5, c1, 0" : "+r" (*val1));
#endif
}

void do_AFSR1_read(unsigned int *val1)
{
    if (val1 == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, AFSR1_EL1" : "+r" (*val1));
#else
    ASM_01("MRC p15, 0, %0, c5, c1, 1" : "+r" (*val1));
#endif
}

void do_ESR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ESR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c5, c0, 0" : "+r" (*val));
#endif
}

void do_FAR_read(unsigned long long *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, FAR_EL1" : "+r" (*val));
#else
    *val = 0;
#endif
}
