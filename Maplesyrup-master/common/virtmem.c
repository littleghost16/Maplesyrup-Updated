#include "cmd_handler.h"
#include "cp15.h"

void do_NMRR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c10, c2, 1" : "+r" (*val));
#endif
}

void do_PRRR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c10, c2, 0" : "+r" (*val));
#endif
}

void do_SCTLR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, SCTLR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c1, c0, 0" : "+r" (*val));
#endif
}

void do_TTBCR_read(retdatatype *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, TCR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c2, c0, 2" : "+r" (*val));
#endif
}

void do_TTBR0_read(retdatatype *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, TTBR0_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c2, c0, 0" : "+r" (*val));
#endif
}

void do_TTBR0LPAE_read(unsigned int *low, unsigned int *hi)
{
    if (low == NULL || hi == NULL)
        return;
#ifdef __aarch64__
    *low = 0;
    *hi = 0;
#else
    ASM_02("MRRC p15, 0, %0, %1, c2" : "+r" (*low), "+r" (*hi));
#endif
}

void do_TTBR1_read(retdatatype *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, TTBR1_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c2, c0, 1" : "+r" (*val));
#endif
}

void do_TTBR1LPAE_read(unsigned int *low, unsigned int *hi)
{
    if (low == NULL || hi == NULL)
        return;
#ifdef __aarch64__
    *low = 0;
    *hi = 0;
#else
    ASM_02("MRRC p15, 1, %0, %1, c2" : "+r" (*low), "+r" (*hi));
#endif
}

void do_CONTEXTIDR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, CONTEXTIDR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c13, c0, 1" : "+r" (*val));
#endif
}

void do_DACR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c3, c0, 0" : "+r" (*val));
#endif
}

void do_MAIR_read(unsigned long long *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, MAIR_EL1" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_MAIR0_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c10, c2, 0" : "+r" (*val));
#endif
}

void do_MAIR1_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c10, c2, 1" : "+r" (*val));
#endif
}

void do_AMAIR_read(unsigned long long *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, AMAIR_EL1" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_AMAIR0_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c10, c3, 0" : "+r" (*val));
#endif
}

void do_AMAIR1_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c10, c3, 1" : "+r" (*val));
#endif
}

void do_DCZID_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, DCZID_EL0" : "+r" (*val));
#else
    *val = 0;
#endif
}
