#ifndef _VFPU_H
#define _VFPU_H

#include "cmd_handler.h"

void do_FPEXC_read(retdatatype *val);
void do_FPSCR_read(retdatatype *val);
void do_FPSID_read(retdatatype *val);
void do_MVFR0_read(unsigned int *val);
void do_MVFR1_read(unsigned int *val);
void do_MVFR2_read(unsigned int *val);

#endif
