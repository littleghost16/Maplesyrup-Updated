#include "cmd_handler.h"
#include "aarch64.h"

void do_AA64AFR0_read(unsigned long long *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_AA64AFR0_EL1" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_AA64AFR1_read(unsigned long long *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_AA64AFR1_EL1" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_AA64DFR0_read(unsigned long long *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_AA64DFR0_EL1" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_AA64DFR1_read(unsigned long long *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_AA64DFR1_EL1" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_AA64ISAR0_read(unsigned long long *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_AA64ISAR0_EL1" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_AA64ISAR1_read(unsigned long long *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_AA64ISAR1_EL1" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_AA64MMFR0_read(unsigned long long *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_AA64MMFR0_EL1" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_AA64MMFR1_read(unsigned long long *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_AA64MMFR1_EL1" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_AA64PFR0_read(unsigned long long *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_AA64PFR0_EL1" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_AA64PFR1_read(unsigned long long *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_AA64PFR1_EL1" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_CURRENTEL_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, CurrentEL" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_DAIF_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, DAIF" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_FPCR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, FPCR" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_FPSR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, FPSR" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_NZCV_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, NZCV" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_SPSEL_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, SPSEL" : "+r" (*val));
#else
    *val = 0;
#endif
}
