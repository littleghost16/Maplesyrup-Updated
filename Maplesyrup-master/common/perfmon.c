#include "cmd_handler.h"
#include "cp15.h"

void do_PMCCFILTR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, PMCCFILTR_EL0" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_PMCCNTR_read(retdatatype *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, PMCCNTR_EL0" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c9, c13, 0" : "+r" (*val));
#endif
}

void do_PMCEID0_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, PMCEID0_EL0" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c9, c12, 6" : "+r" (*val));
#endif
}

void do_PMCEID1_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, PMCEID1_EL0" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c9, c12, 7" : "+r" (*val));
#endif
}

void do_PMCNTENSET_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, PMCNTENSET_EL0" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c9, c12, 1" : "+r" (*val));
#endif
}

void do_PMCNTENCLR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, PMCNTENCLR_EL0" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c9, c12, 2" : "+r" (*val));
#endif
}

void do_PMCR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, PMCR_EL0" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c9, c12, 0" : "+r" (*val));
#endif
}

void do_PMSELR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, PMSELR_EL0" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c9, c12, 5" : "+r" (*val));
#endif
}

void do_PMXEVTYPER_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, PMXEVTYPER_EL0" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c9, c13, 2" : "+r" (*val));
#endif
}

void do_PMXEVCNTR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, PMXEVCNTR_EL0" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c9, c13, 1" : "+r" (*val));
#endif
}

void do_PMUSERENR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, PMUSERENR_EL0" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c9, c14, 0" : "+r" (*val));
#endif
}

void do_PMOVSR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c9, c12, 3" : "+r" (*val));
#endif
}

void do_PMINTENCLR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, PMINTENCLR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c9, c14, 1" : "+r" (*val));
#endif
}

void do_PMINTENSET_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, PMINTENSET_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c9, c14, 1" : "+r" (*val));
#endif
}

void do_PMOVSCLR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, PMOVSCLR_EL0" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_PMOVSSET_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, PMOVSSET_EL0" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c9, c14, 3" : "+r" (*val));
#endif
}

void do_PMSWINC_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, PMSWINC_EL0" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c9, c12, 4" : "+r" (*val));
#endif
}
