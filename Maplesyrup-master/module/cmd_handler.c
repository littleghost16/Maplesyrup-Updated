#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/smp.h>
#include <linux/cpu.h>
#include <linux/spinlock.h>
#include <linux/errno.h>

#include "cmd_handler.h"
#include "parse.h"
#include "undef_hook.h"
#include "ms_debug.h"
#include "ms_error.h"

extern unsigned int g_undef_flag;
extern spinlock_t g_undef_flag_lock;

int unpack_result_wrapper(
    ms_data_cpu *userin,
    co15_result_cpu_wrapper *kernelout)
{
    unsigned int i = 0;
    int result = -1;

    if (userin == NULL || kernelout == NULL)
    {
        TRACE("param error\n", 0);
        goto done;
    }

    for (i = 0; i < MS_MAX_CPUS; ++i)
    {
        kernelout->results.cpu[i].in1 = userin->cpu[i].in1;
        kernelout->results.cpu[i].in2 = userin->cpu[i].in2;
        kernelout->results.cpu[i].out64 = userin->cpu[i].out64;
        kernelout->results.cpu[i].out1 = userin->cpu[i].out1;
        kernelout->results.cpu[i].out2 = userin->cpu[i].out2;
        kernelout->results.cpu[i].cpu = userin->cpu[i].cpu;
        kernelout->results.cpu[i].midr = userin->cpu[i].midr;
        kernelout->results.cpu[i].status = userin->cpu[i].status;
    }
    kernelout->pcpu = userin->pcpu;
    kernelout->results.code = userin->code;
    kernelout->results.part_number = userin->part_number;

    result = 0;

done:
    return result;
}

int repack_result_wrapper(
    co15_result_cpu_wrapper *kernelin,
    ms_data_cpu *userout)
{
    int result = -1;
    unsigned int i = 0;

    if (kernelin == NULL || userout == NULL)
    {
        TRACE("param error\n", 0);
        goto done;
    }

    for (i = 0; i < MS_MAX_CPUS; ++i)
    {
        userout->cpu[i].in1 = kernelin->results.cpu[i].in1;
        userout->cpu[i].in2 = kernelin->results.cpu[i].in2;
        userout->cpu[i].out64 = kernelin->results.cpu[i].out64;
        userout->cpu[i].out1 = kernelin->results.cpu[i].out1;
        userout->cpu[i].out2 = kernelin->results.cpu[i].out2;
        userout->cpu[i].cpu = kernelin->results.cpu[i].cpu;
        userout->cpu[i].midr = kernelin->results.cpu[i].midr;
        userout->cpu[i].status = kernelin->results.cpu[i].status;
    }
    userout->pcpu = kernelin->pcpu;
    userout->code = kernelin->results.code;
    userout->part_number = kernelin->results.part_number;

    result = 0;

done:
    return result;
}

static int find_function_index(
    unsigned int ioctl,
    unsigned int *index_out)
{
    int result = -1;
    int i = 0;
    int table_size = return_table_size();

    if (index_out == NULL)
    {
        return -EINVAL;
    }

    for (i = 0; i < table_size; i++)
    {
        if (ioctl == func_table[i].code)
        {
            TRACE("Found function!: ioctl: 0x%x, entry: %d/%d\n",
                  func_table[i].code, i, table_size);
            *index_out = (unsigned int)i;
            result = 0;
            break;
        }
    }

    if (result != 0)
    {
        TRACE("Could not find function ptr\n", 0);
    }

    return result;
}

static void get_midr(unsigned int *val)
{
    if (val == NULL)
        return;
#ifdef __aarch64__
    asm volatile("MRS %0, MIDR_EL1" : "+r" (*val));
#else
    asm volatile("MRC p15, 0, %0, c0, c0, 0" : "+r" (*val));
#endif
}

static void call_func_ptr(void *result_out)
{
    unsigned int cpu_index = 0;
    unsigned int func_index = 0;
    ms_data *co15_result_entry = NULL;
    co15_result_cpu_wrapper *result_out_cast = NULL;
    unsigned int midr_result = 0;
    unsigned long long cmd_result_64 = 0;
    unsigned int cmd_result_1 = 0;
    unsigned int cmd_result_2 = 0;

    if (result_out == NULL)
    {
        TRACE("param error\n", 0);
        return;
    }
    result_out_cast = (co15_result_cpu_wrapper *)result_out;

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

    func_index = result_out_cast->found_index;
    co15_result_entry = &result_out_cast->results.cpu[cpu_index];

    co15_result_entry->out64 = 0;
    co15_result_entry->out1 = 0;
    co15_result_entry->out2 = 0;
    co15_result_entry->cpu = cpu_index;

    get_midr(&midr_result);
    co15_result_entry->midr = midr_result;

    switch (func_table[func_index].function_prototype)
    {
        case FUNCTYPE_OUT_1:
            switch (func_table[func_index].data_size)
            {
                case FUNCTYPE_BITS_32:
                    ((func_ptr_32_01)(func_table[func_index].func_ptr))(&cmd_result_1);
                    co15_result_entry->out1 = cmd_result_1;
                    set_undef_flag(co15_result_entry);
                    break;
                case FUNCTYPE_BITS_64:
                    ((func_ptr_64_01)(func_table[func_index].func_ptr))(&cmd_result_64);
                    co15_result_entry->out64 = cmd_result_64;
                    set_undef_flag(co15_result_entry);
                    break;
                case FUNCTYPE_BITS_ARCH:
#ifdef __aarch64__
                    ((func_ptr_arch_01)(func_table[func_index].func_ptr))(&cmd_result_64);
                    co15_result_entry->out64 = cmd_result_64;
#else
                    ((func_ptr_arch_01)(func_table[func_index].func_ptr))(&cmd_result_1);
                    co15_result_entry->out1 = cmd_result_1;
#endif
                    set_undef_flag(co15_result_entry);
                    break;
                default:
                    co15_result_entry->status = MS_ERROR_TABLE;
                    break;
            }
            break;

        case FUNCTYPE_OUT_2:
            switch (func_table[func_index].data_size)
            {
                case FUNCTYPE_BITS_32:
                    ((func_ptr_32_02)(func_table[func_index].func_ptr))(&cmd_result_1, &cmd_result_2);
                    co15_result_entry->out1 = cmd_result_1;
                    co15_result_entry->out2 = cmd_result_2;
                    set_undef_flag(co15_result_entry);
                    break;

                case FUNCTYPE_BITS_ARCH:
#ifdef __aarch64__
                    ((func_ptr_arch_02)(func_table[func_index].func_ptr))(&cmd_result_64, &cmd_result_2);
                    co15_result_entry->out64 = cmd_result_64;
#else
                    ((func_ptr_arch_02)(func_table[func_index].func_ptr))(&cmd_result_1, &cmd_result_2);
                    co15_result_entry->out1 = cmd_result_1;
#endif
                    co15_result_entry->out2 = cmd_result_2;
                    set_undef_flag(co15_result_entry);
                    break;

                default:
                    co15_result_entry->status = MS_ERROR_TABLE;
                    break;
            }
            break;

        default:
            co15_result_entry->status = MS_ERROR_TABLE;
            break;
    }

#ifdef CONFIG_SMP
    put_cpu();
#endif
}

static int cpu_online_wrapper(
    unsigned int cpu,
    void (*threadfn)(void *data),
    void *data)
{
    int result = -1;
    co15_result_cpu_wrapper *data_cast = NULL;
    ms_data *entry = NULL;

    if (threadfn == NULL || data == NULL)
    {
        TRACE("param error\n", 0);
        goto done;
    }

    data_cast = (co15_result_cpu_wrapper *)data;

    if (cpu >= MS_MAX_CPUS)
    {
        TRACE("CPU index too large: %u\n", cpu);
        goto done;
    }

    entry = &data_cast->results.cpu[cpu];

#ifdef CONFIG_SMP
    if (!cpu_online(cpu))
    {
        entry->status = MS_ERROR_SMP;
        goto done;
    }

    if (smp_call_function_single((int)cpu, threadfn, data, 1) != 0)
    {
        TRACE("Function call fail on CPU %u\n", cpu);
        entry->status = MS_ERROR_SMP_SINGLE;
        goto done;
    }
#else
    threadfn(data);
#endif

    result = 0;

done:
    return result;
}

int on_each_cpu_kick(
    void (*funcptr)(void *funcdata),
    co15_result_cpu_wrapper *data)
{
    unsigned int i = 0;
    int status = -1;

    if (data == NULL || funcptr == NULL)
    {
        return -EINVAL;
    }

    if (data->pcpu == MS_CPU_ALL)
    {
        for (i = 0; i < MS_MAX_CPUS; ++i)
        {
            if (cpu_online_wrapper(i, funcptr, (void *)data) != 0)
            {
                TRACE("Problem calling function on cpu %u\n", i);
            }
        }
    }
    else
    {
        if (data->pcpu >= MS_MAX_CPUS)
        {
            TRACE("CPU index error: %u\n", data->pcpu);
            goto done;
        }

        if (cpu_online_wrapper(data->pcpu, funcptr, (void *)data) != 0)
        {
            TRACE("Problem calling function on cpu %u\n", data->pcpu);
        }
    }
    status = 0;

done:
    return status;
}

int call_func_return_results(ms_data_cpu *result_out)
{
    int result = -1;
    unsigned int index_out = 0;
    co15_result_cpu_wrapper local_result;

    if (result_out == NULL)
    {
        return -EINVAL;
    }
    memset(&local_result, 0, sizeof(co15_result_cpu_wrapper));
    TRACE("Command received: 0x%x\n", result_out->code);

    if (find_function_index(result_out->code, &index_out) != 0)
    {
        TRACE("Failed to find function\n", 0);
        goto done;
    }
    TRACE("Found function\n", 0);

    if (unpack_result_wrapper(result_out, &local_result) != 0)
    {
        TRACE("Failed to unpack\n", 0);
        goto done;
    }
    local_result.found_index = index_out;

    if (on_each_cpu_kick(call_func_ptr, &local_result) != 0)
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

int call_cmd(
    void *buffer,
    int (*pcall)(ms_data_cpu *result_out))
{
    int result = -1;
    unsigned long flags;
    ms_data_cpu *user_buffer = NULL;
    ms_data_cpu user_buffer_local;

    if (buffer == NULL || pcall == NULL)
    {
        TRACE("param error\n", 0);
        return -EINVAL;
    }
    user_buffer = (ms_data_cpu *)buffer;

    spin_lock_irqsave(&g_undef_flag_lock, flags);
    g_undef_flag = 0;
    spin_unlock_irqrestore(&g_undef_flag_lock, flags);

    memset(&user_buffer_local, 0, sizeof(ms_data_cpu));

    if (copy_from_user(&user_buffer_local, user_buffer, sizeof(ms_data_cpu)) != 0)
    {
        TRACE("Could not get data from userspace\n", 0);
        return -EFAULT;
    }

    if (pcall(&user_buffer_local) != 0)
    {
        TRACE("Could not call function & get results\n", 0);
        goto done;
    }

    if (copy_to_user(user_buffer, &user_buffer_local, sizeof(ms_data_cpu)) != 0)
    {
        TRACE("Could not send data back to userspace\n", 0);
        return -EFAULT;
    }

    result = 0;

done:
    return result;
}
