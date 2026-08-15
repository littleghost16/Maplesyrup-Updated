#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/errno.h>

#include "ms_debug.h"
#include "cmd_handler.h"
#include "device_tree.h"
#include "undef_hook.h"

static long ms_ioctl(
    struct file *file,
    unsigned int cmd,
    unsigned long arg)
{
    long ret = 0;
    (void)file;

    TRACE("IOCTL received: cmd: 0x%x\n", cmd);
    switch (cmd)
    {
        case MS_IOCTL_CO:
            ret = call_cmd((void *)arg, call_func_return_results);
            break;
        case MS_IOCTL_GIC:
            ret = call_cmd((void *)arg, gic_return_results);
            break;
        default:
            ret = -ENOTTY;
            break;
    }
    return ret;
}

static int ms_open(
    struct inode *inode,
    struct file *file)
{
    int result = -1;
    (void)inode;
    (void)file;

    TRACE("Open called\n", 0);

    if (ms_add_undef_instr_hook() != 0)
    {
        TRACE("Failed to add_undef_instr_hook\n", 0);
        goto done;
    }
    TRACE("Added undefined instruction hook\n", 0);
    result = 0;

done:
    return result;
}

static int ms_release(
    struct inode *inode,
    struct file *file)
{
    (void)inode;
    (void)file;

    TRACE("Release called\n", 0);
    ms_del_undef_instr_hook();
    return 0;
}

static const struct file_operations ms_ops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = ms_ioctl,
    .compat_ioctl = ms_ioctl,
    .open = ms_open,
    .release = ms_release,
    .llseek = no_llseek,
};

static struct miscdevice ms_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "maplesyrup",
    .fops = &ms_ops,
    .mode = 0666,
};

static int __init maplesyrup_init(void)
{
    int result = -1;

    if (ms_find_undef_hook() != 0)
    {
        TRACE("Failed to find_undef_hook\n", 0);
        goto done;
    }

    if (ms_init_dt_data() != 0)
    {
        TRACE("Failed to init DT data\n", 0);
    }

    result = misc_register(&ms_device);
    if (result != 0)
    {
        TRACE("Failed to misc_register: %d\n", result);
        ms_cleanup_dt_data();
        goto done;
    }
    pr_info("Registered Maplesyrup device\n");

    result = 0;

done:
    return result;
}

static void __exit maplesyrup_exit(void)
{
    pr_info("Unregistering Maplesyrup device\n");
    misc_deregister(&ms_device);
    ms_cleanup_dt_data();
}

module_init(maplesyrup_init);
module_exit(maplesyrup_exit);

MODULE_AUTHOR("Maplesyrup");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Maplesyrup Register Introspection & Analysis Driver");
MODULE_VERSION("2.0");
