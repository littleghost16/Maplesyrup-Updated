#include "cmd_handler.h"
#include "cp15.h"

void do_AIDR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, AIDR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 1, %0, c0, c0, 7" : "+r" (*val));
#endif
}

void do_REVIDR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, REVIDR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c0, c0, 6" : "+r" (*val));
#endif
}

void do_TLBTR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c0, c0, 3" : "+r" (*val));
#endif
}

void do_AFR0_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_AFR0_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c0, c1, 3" : "+r" (*val));
#endif
}

void do_CCSIDR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, CCSIDR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 1, %0, c0, c0, 0" : "+r" (*val));
#endif
}

void do_CLIDR_read(retdatatype *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, CLIDR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 1, %0, c0, c0, 1" : "+r" (*val));
#endif
}

void do_TCM_read(retdatatype *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c0, c0, 2" : "+r" (*val));
#endif
}

void do_CSSELR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, CSSELR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 2, %0, c0, c0, 0" : "+r" (*val));
#endif
}

void do_CTR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, CTR_EL0" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c0, c0, 1" : "+r" (*val));
#endif
}

void do_TCMTR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c0, c0, 2" : "+r" (*val));
#endif
}

void do_MIDR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, MIDR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c0, c0, 0" : "+r" (*val));
#endif
}

void do_MPIDR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, MPIDR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c0, c0, 5" : "+r" (*val));
#endif
}

void do_DFR0_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_DFR0_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c0, c1, 2" : "+r" (*val));
#endif
}

void do_ISAR0_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_ISAR0_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c0, c2, 0" : "+r" (*val));
#endif
}

void do_ISAR1_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_ISAR1_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c0, c2, 1" : "+r" (*val));
#endif
}

void do_ISAR2_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_ISAR2_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c0, c2, 2" : "+r" (*val));
#endif
}

void do_ISAR3_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_ISAR3_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c0, c2, 3" : "+r" (*val));
#endif
}

void do_ISAR4_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_ISAR4_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c0, c2, 4" : "+r" (*val));
#endif
}

void do_ISAR5_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_ISAR5_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c0, c2, 5" : "+r" (*val));
#endif
}

void do_MMFR0_read(retdatatype *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_MMFR0_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c0, c1, 4" : "+r" (*val));
#endif
}

void do_MMFR1_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_MMFR1_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c0, c1, 5" : "+r" (*val));
#endif
}

void do_MMFR2_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_MMFR2_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c0, c1, 6" : "+r" (*val));
#endif
}

void do_MMFR3_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_MMFR3_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c0, c1, 7" : "+r" (*val));
#endif
}

void do_PFR0_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_PFR0_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c0, c1, 0" : "+r" (*val));
#endif
}

void do_PFR1_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ID_PFR1_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c0, c1, 1" : "+r" (*val));
#endif
}
