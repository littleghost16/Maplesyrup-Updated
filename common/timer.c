#include "cmd_handler.h"
#include "cp15.h"

void do_CNTFRQ_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, CNTFRQ_EL0" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c14, c0, 0" : "+r" (*val));
#endif
}

void do_CNTHCTL_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p15, 4, %0, c14, c1, 0" : "+r" (*val));
#endif
}

void do_CNTHP_CTL_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    *val = 0;
#endif
}

void do_CNTHP_CVAL_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    *val = 0;
#endif
}

void do_CNTHP_TVAL_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    *val = 0;
#endif
}

void do_CNTKCTL_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, CNTKCTL_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c14, c1, 0" : "+r" (*val));
#endif
}

void do_CNTP_CTL_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, CNTP_CTL_EL0" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c14, c2, 1" : "+r" (*val));
#endif
}

void do_CNTP_CVAL_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    *val = 0;
#endif
}

void do_CNTP_TVAL_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    *val = 0;
#endif
}

void do_CNTPCT_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    *val = 0;
#endif
}

void do_CNTV_CTL_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    *val = 0;
#endif
}

void do_CNTV_CVAL_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    *val = 0;
#endif
}

void do_CNTV_TVAL_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    *val = 0;
#endif
}

void do_CNTVCT_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    *val = 0;
#endif
}

void do_CNTVOFF_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    *val = 0;
#endif
}
