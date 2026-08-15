#ifndef _MS_SUPPORT_H
#define _MS_SUPPORT_H

#ifdef __KERNEL__
#include <linux/types.h>
#include <linux/stddef.h>
#else
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#endif

typedef struct list_element
{
    struct list_element *next;
} list_element;

typedef struct ms_list_head
{
    list_element *head;
    list_element *tail;
    size_t size;
} ms_list_head;

void ms_list_init(ms_list_head *list);
void ms_list_add(ms_list_head *list, list_element *toadd);
void ms_list_free(ms_list_head *list);

#endif
