#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef __KERNEL__
#include <linux/types.h>
#include <linux/printk.h>
#else
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#endif

#ifdef _MS_DEBUG
    #define TRACE(fmt, ...) \
        do { trace(fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__); } while (0)
#else
    #define TRACE(fmt, ...) \
        do { } while (0)
#endif

#ifdef __KERNEL__
    #define PRINTF printk
#else
    #define PRINTF printf
#endif

void trace(const char *format, const char *filename, const char *funcname, unsigned int line, ...);
void hex_dump(const void *ptr, unsigned int len);

#endif
