#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/smp.h>
#include <linux/cpu.h>
#include <linux/spinlock.h>
#include <linux/io.h>

#include "device_tree.h"
#include "cmd_handler.h"
#include "ms_debug.h"
#include "parse.h"
#include "intc.h"
#include "maplesyrup.h"
#include "ms_error.h"

extern ms_gic_map gic_map;

static void gic_bar_read(void *result_out)
{
    unsigned int cpu_index = 0;
    ms_data *co15_result_entry = NULL;
    co15_result_cpu_wrapper *result_out_cast = NULL;
    unsigned int value = 0;

    if (result_out == NULL)
    {
        TRACE("param error\n", 0);
        return;
    }
    result_out_cast = (co15_result_cpu_wrapper *)result_out;

    if (result_out_cast->base_addr == NULL)
    {
        TRACE("No GIC base address\n", 0);
        return;
    }

#ifdef CONFIG_SMP
    cpu_index = get_cpu();
#else
    cpu_index = 0;
#endif

    if (cpu_index >= MS_MAX_CPUS)
    {
#ifdef CONFIG_SMP
        put_cpu();
#endif
        return;
    }

    co15_result_entry = &result_out_cast->results.cpu[cpu_index];

    co15_result_entry->out64 = 0;
    co15_result_entry->out1 = 0;
    co15_result_entry->out2 = 0;
    co15_result_entry->cpu = cpu_index;

    value = readl_relaxed((const volatile void __iomem *)((uintptr_t)result_out_cast->base_addr +
                          (uintptr_t)MSCODE_FIELD(result_out_cast->results.code)));
    TRACE("Reading: %p + 0x%x: 0x%x\n", result_out_cast->base_addr, MSCODE_FIELD(result_out_cast->results.code), value);

    co15_result_entry->out1 = value;
    co15_result_entry->status = MS_ERROR_SUCCESS;

#ifdef CONFIG_SMP
    put_cpu();
#endif
}

int gic_return_results(ms_data_cpu *result_out)
{
    int result = -1;
    co15_result_cpu_wrapper local_result;

    if (result_out == NULL)
    {
        return -EINVAL;
    }
    memset(&local_result, 0, sizeof(co15_result_cpu_wrapper));

    if (unpack_result_wrapper(result_out, &local_result) != 0)
    {
        TRACE("Failed to unpack\n", 0);
        goto done;
    }

    switch (result_out->part_number)
    {
        case GICC_V2:
            local_result.base_addr = gic_map.gicc_virt;
            break;
        case GICD_V2:
            local_result.base_addr = gic_map.gicd_virt;
            break;
        case GICH_V2:
            local_result.base_addr = gic_map.gich_virt;
            break;
        case GICV_V2:
            local_result.base_addr = gic_map.gicv_virt;
            break;
        default:
            goto done;
    }

    if (local_result.base_addr == NULL)
    {
        TRACE("Requested GIC interface is not mapped\n", 0);
        goto done;
    }

    if (on_each_cpu_kick(gic_bar_read, &local_result) != 0)
    {
        TRACE("Failed on_each_cpu_kick\n", 0);
        goto done;
    }

    if (repack_result_wrapper(&local_result, result_out) != 0)
    {
        TRACE("Failed to repack results\n", 0);
        goto done;
    }
    TRACE("Function called successfully and results saved\n", 0);

    result = 0;

done:
    return result;
}
