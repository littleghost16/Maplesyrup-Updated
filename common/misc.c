#include "cmd_handler.h"
#include "cp15.h"

void do_TPIDRPRW_read(retdatatype *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, TPIDR_EL1" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c13, c0, 4" : "+r" (*val));
#endif
}

void do_TPIDRURO_read(retdatatype *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, TPIDRRO_EL0" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c13, c0, 3" : "+r" (*val));
#endif
}

void do_TPIDRURW_read(retdatatype *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    ASM_01("MRS %0, TPIDR_EL0" : "+r" (*val));
#else
    ASM_01("MRC p15, 0, %0, c13, c0, 2" : "+r" (*val));
#endif
}
