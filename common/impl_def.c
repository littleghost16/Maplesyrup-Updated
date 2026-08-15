#include "cmd_handler.h"
#include "cp15.h"

void do_L2CTLR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, S3_1_C11_C0_2" : "+r" (*val));
#else
    ASM_01("MRC p15, 1, %0, c9, c0, 2" : "+r" (*val));
#endif
}

void do_L2ACTLR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, S3_1_C15_C0_0" : "+r" (*val));
#else
    ASM_01("MRC p15, 1, %0, c15, c0, 0" : "+r" (*val));
#endif
}

void do_L2PFR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 1, %0, c15, c0, 3" : "+r" (*val));
#endif
}

void do_CPUACTLR_read(unsigned long long *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, S3_1_C15_C2_0" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_ACTLR_read(retdatatype *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, ACTLR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c1, c0, 1" : "+r" (*val));
#endif
}

void do_ACTLR2_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 1, %0, c15, c0, 4" : "+r" (*val));
#endif
}

void do_CPUMERRSR_read(retdatatype *val1, unsigned int *val2)
{
    if (val1 == NULL || val2 == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, S3_1_C15_C2_2" : "+r" (*val1));
    *val2 = 0;
#else
    ASM_02("MRRC p15, 0, %0, %1, c15" : "+r" (*val1), "+r" (*val2));
#endif
}

void do_L2MERRSR_read(retdatatype *val1, unsigned int *val2)
{
    if (val1 == NULL || val2 == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, S3_1_C15_C2_3" : "+r" (*val1));
    *val2 = 0;
#else
    ASM_02("MRRC p15, 1, %0, %1, c15" : "+r" (*val1), "+r" (*val2));
#endif
}

void do_L2ECTLR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, S3_1_C11_C0_3" : "+r" (*val));
#else
    ASM_01("MRC p15, 1, %0, c9, c0, 3" : "+r" (*val));
#endif
}

void do_CPUECTLR_read(unsigned long long *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, S3_1_C15_C2_1" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_CBAR_read(retdatatype *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, S3_1_C15_C3_0" : "+r" (*val));
#else
    ASM_01("MRC p15, 4, %0, c15, c0, 0" : "+r" (*val));
#endif
}

void do_IL1DATA0_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c15, c0, 0" : "+r" (*val));
#endif
}

void do_IL1DATA1_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c15, c0, 1" : "+r" (*val));
#endif
}

void do_IL1DATA2_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c15, c0, 2" : "+r" (*val));
#endif
}

void do_IL1DATA3_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c15, c0, 3" : "+r" (*val));
#endif
}

void do_DL1DATA0_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c15, c1, 0" : "+r" (*val));
#endif
}

void do_DL1DATA1_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c15, c1, 1" : "+r" (*val));
#endif
}

void do_DL1DATA2_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c15, c1, 2" : "+r" (*val));
#endif
}

void do_DL1DATA3_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c15, c1, 3" : "+r" (*val));
#endif
}

void do_CDBGDR0_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c15, c0, 0" : "+r" (*val));
#endif
}

void do_CDBGDR1_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c15, c0, 1" : "+r" (*val));
#endif
}

void do_CDBGDR2_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c15, c0, 2" : "+r" (*val));
#endif
}

void do_CDBGDCT_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c15, c0, 3" : "+r" (*val));
#endif
}

void do_CDBGICT_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c15, c0, 4" : "+r" (*val));
#endif
}

void do_CDBGDCD_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c15, c0, 5" : "+r" (*val));
#endif
}

void do_CDBGICD_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c15, c0, 6" : "+r" (*val));
#endif
}

void do_CDBGTD_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 0, %0, c15, c0, 7" : "+r" (*val));
#endif
}
