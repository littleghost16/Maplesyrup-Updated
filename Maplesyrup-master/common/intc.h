#ifndef _MS_INTC_H
#define _MS_INTC_H

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include <stdint.h>
#include <stddef.h>
#endif

typedef struct ms_gic_map
{
    void *gicc_phys;
    void *gicc_virt;
    unsigned int gicc_size;

    void *gicd_phys;
    void *gicd_virt;
    unsigned int gicd_size;

    void *gich_phys;
    void *gich_virt;
    unsigned int gich_size;

    void *gicv_phys;
    void *gicv_virt;
    unsigned int gicv_size;
} ms_gic_map;

#endif
