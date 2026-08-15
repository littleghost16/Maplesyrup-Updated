#ifdef __KERNEL__
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/ctype.h>
#else
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#endif

#include "ms_debug.h"

void trace(
    const char *format,
    const char *filename,
    const char *funcname,
    unsigned int line,
    ...)
{
    char buffer[256];
    va_list argptr;

#ifdef __KERNEL__
    (void)filename;
#endif

    if (format == NULL || funcname == NULL
#ifndef __KERNEL__
        || filename == NULL
#endif
    )
    {
        return;
    }

    va_start(argptr, line);
    vsnprintf(buffer, sizeof(buffer), format, argptr);
    va_end(argptr);

#ifdef __KERNEL__
    PRINTF(KERN_INFO "Maplesyrup [%s] [%u]: %s", funcname, line, buffer);
#else
    PRINTF("Maplesyrup [%s] [%s] [%u]: %s", filename, funcname, line, buffer);
#endif
}

void hex_dump(
    const void *ptr,
    unsigned int len)
{
    unsigned int i = 0;
    const unsigned char *pBuffer = NULL;

    if (ptr == NULL || len == 0)
    {
        return;
    }

    PRINTF("=======================================\n");
    PRINTF("Dumping %u bytes @ %p\n", len, ptr);
    PRINTF("=======================================\n");

    pBuffer = (const unsigned char *)ptr;
    for (i = 0; i < len; i++)
    {
        PRINTF("%02x", pBuffer[i]);

        if (((i + 1) % 4) == 0)
        {
            PRINTF(" ");
        }
        if (((i + 1) % 32) == 0)
        {
            PRINTF(" (+0x%x)\n", i - 0x1FU);
        }
    }

    PRINTF("\n\n\n");
    pBuffer = (const unsigned char *)ptr;
    for (i = 0; i < len; ++i)
    {
        if (isprint(pBuffer[i]))
        {
            PRINTF("%c ", pBuffer[i]);
        }
        else
        {
            PRINTF(". ");
        }
        if (((i + 1) % 4) == 0)
        {
            PRINTF(" ");
        }
        if (((i + 1) % 32) == 0)
        {
            PRINTF(" (+0x%x)\n", i - 0x1FU);
        }
    }

    PRINTF("\n");
    PRINTF("=======================================\n");
}
