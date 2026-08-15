#ifndef _PSR_H
#define _PSR_H

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include <stdint.h>
#endif

void do_CPSR_read(unsigned int *val);
void do_APSR_read(unsigned int *val);
void do_SPSR_read(unsigned int *val);

#endif
