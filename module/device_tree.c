#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/io.h>

#include "device_tree.h"
#include "intc.h"
#include "ms_debug.h"

ms_gic_map gic_map;

static const char * const g_supported_gic[] =
{
    "arm,cortex-a15-gic",
    "arm,cortex-a7-gic",
    "arm,cortex-a9-gic",
    "arm,gic-400",
};

static int ms_find_gic_devices(void)
{
    int result = -1;
    size_t i = 0;
    struct device_node *ic_node = NULL;
    struct resource res;

    for (i = 0; i < (sizeof(g_supported_gic) / sizeof(const char *)); ++i)
    {
        ic_node = of_find_compatible_node(NULL, NULL, g_supported_gic[i]);
        if (ic_node != NULL)
        {
            TRACE("Found device: %s (%s compatible)\n", ic_node->name, g_supported_gic[i]);
            break;
        }
    }

    if (ic_node == NULL)
    {
        TRACE("No supported gics found\n", 0);
        goto done;
    }

    if (of_address_to_resource(ic_node, 0, &res) != 0)
    {
        TRACE("Failed to get address of GICD\n", 0);
        goto done;
    }
    gic_map.gicd_phys = (void *)(uintptr_t)res.start;
    gic_map.gicd_size = (unsigned int)resource_size(&res);

    if (of_address_to_resource(ic_node, 1, &res) != 0)
    {
        TRACE("Failed to get address of GICC\n", 0);
        goto done;
    }
    gic_map.gicc_phys = (void *)(uintptr_t)res.start;
    gic_map.gicc_size = (unsigned int)resource_size(&res);

    if (of_address_to_resource(ic_node, 2, &res) == 0)
    {
        gic_map.gich_phys = (void *)(uintptr_t)res.start;
        gic_map.gich_size = (unsigned int)resource_size(&res);
    }

    if (of_address_to_resource(ic_node, 3, &res) == 0)
    {
        gic_map.gicv_phys = (void *)(uintptr_t)res.start;
        gic_map.gicv_size = (unsigned int)resource_size(&res);
    }

    result = 0;

done:
    if (ic_node != NULL)
    {
        of_node_put(ic_node);
    }
    return result;
}

static int ms_remap_gic(void)
{
    int result = -1;
    void __iomem *mapped_addr = NULL;

    if (gic_map.gicd_phys != NULL)
    {
        mapped_addr = ioremap((phys_addr_t)(uintptr_t)gic_map.gicd_phys, gic_map.gicd_size);
        if (mapped_addr == NULL)
        {
            TRACE("Failed to map GICD\n", 0);
            goto done;
        }
        gic_map.gicd_virt = (void *)mapped_addr;
        TRACE("Remapped GICD %p to %p (size: 0x%x)\n", gic_map.gicd_phys, gic_map.gicd_virt, gic_map.gicd_size);
    }
    else
    {
        goto done;
    }

    if (gic_map.gicc_phys != NULL)
    {
        mapped_addr = ioremap((phys_addr_t)(uintptr_t)gic_map.gicc_phys, gic_map.gicc_size);
        if (mapped_addr == NULL)
        {
            TRACE("Failed to map GICC\n", 0);
            goto done;
        }
        gic_map.gicc_virt = (void *)mapped_addr;
        TRACE("Remapped GICC %p to %p (size: 0x%x)\n", gic_map.gicc_phys, gic_map.gicc_virt, gic_map.gicc_size);
    }
    else
    {
        goto done;
    }

    if (gic_map.gich_phys != NULL)
    {
        mapped_addr = ioremap((phys_addr_t)(uintptr_t)gic_map.gich_phys, gic_map.gich_size);
        if (mapped_addr == NULL)
        {
            TRACE("Failed to map GICH\n", 0);
            goto done;
        }
        gic_map.gich_virt = (void *)mapped_addr;
        TRACE("Remapped GICH %p to %p (size: 0x%x)\n", gic_map.gich_phys, gic_map.gich_virt, gic_map.gich_size);
    }

    if (gic_map.gicv_phys != NULL)
    {
        mapped_addr = ioremap((phys_addr_t)(uintptr_t)gic_map.gicv_phys, gic_map.gicv_size);
        if (mapped_addr == NULL)
        {
            TRACE("Failed to map GICV\n", 0);
            goto done;
        }
        gic_map.gicv_virt = (void *)mapped_addr;
        TRACE("Remapped GICV %p to %p (size: 0x%x)\n", gic_map.gicv_phys, gic_map.gicv_virt, gic_map.gicv_size);
    }

    result = 0;

done:
    return result;
}

static int ms_populate_gic_map(void)
{
    int result = -1;

    if (ms_find_gic_devices() != 0)
    {
        TRACE("Failed to find a gic device\n", 0);
        goto done;
    }

    if (ms_remap_gic() != 0)
    {
        TRACE("Failed to remap to kernel space\n", 0);
        goto done;
    }

    TRACE("GIC map translated successfully\n", 0);
    result = 0;

done:
    return result;
}

static void ms_cleanup_gic(void)
{
    if (gic_map.gicc_virt != NULL)
    {
        iounmap((void __iomem *)gic_map.gicc_virt);
        gic_map.gicc_virt = NULL;
    }
    if (gic_map.gicd_virt != NULL)
    {
        iounmap((void __iomem *)gic_map.gicd_virt);
        gic_map.gicd_virt = NULL;
    }
    if (gic_map.gich_virt != NULL)
    {
        iounmap((void __iomem *)gic_map.gich_virt);
        gic_map.gich_virt = NULL;
    }
    if (gic_map.gicv_virt != NULL)
    {
        iounmap((void __iomem *)gic_map.gicv_virt);
        gic_map.gicv_virt = NULL;
    }
}

int ms_init_dt_data(void)
{
    int result = -1;

    memset(&gic_map, 0, sizeof(ms_gic_map));

    if (ms_populate_gic_map() != 0)
    {
        TRACE("Unable to get interrupt controller data\n", 0);
        goto done;
    }

    result = 0;

done:
    return result;
}

void ms_cleanup_dt_data(void)
{
    ms_cleanup_gic();
}
