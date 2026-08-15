#include "cmd_handler.h"
#include "psr.h"

void do_APSR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRS %0, APSR" : "+r" (*val));
#endif
}

void do_CPSR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRS %0, CPSR" : "+r" (*val));
#endif
}

void do_SPSR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRS %0, SPSR" : "+r" (*val));
#endif
}
