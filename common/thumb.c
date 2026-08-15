#include "cmd_handler.h"
#include "cp15.h"

void do_TEECR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p14, 0, %0, c0, c0, 0" : "+r" (*val));
#endif
}

void do_TEEHBR_read(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    *val = 0;
#else
    ASM_01("MRC p14, 6, %0, c1, c0, 0" : "+r" (*val));
#endif
}
