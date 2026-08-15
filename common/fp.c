#include "cmd_handler.h"
#include "vfpu.h"

void do_FPEXC_read(retdatatype *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_FP("VMRS %0, FPEXC" : "+r" (*val));
#endif
}

void do_MVFR0_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, MVFR0_EL1" : "+r" (*val));
#else
    ASM_FP("VMRS %0, MVFR0" : "+r" (*val));
#endif
}

void do_MVFR1_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, MVFR1_EL1" : "+r" (*val));
#else
    ASM_FP("VMRS %0, MVFR1" : "+r" (*val));
#endif
}

void do_MVFR2_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, MVFR2_EL1" : "+r" (*val));
#else
    *val = 0;
#endif
}

void do_FPSID_read(retdatatype *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_FP("VMRS %0, FPSID" : "+r" (*val));
#endif
}

void do_FPSCR_read(retdatatype *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_FP("VMRS %0, FPSCR" : "+r" (*val));
#endif
}
