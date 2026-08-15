#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "maplesyrup.h"

#define MAX_ARCH_BUFFER 16
#define MAX_IMPL_BUFFER 16
#define MAX_CALC_BUFFER 32

#define FLAG_SHOW_GROUPS 1
#define FLAG_SHOW_BITFIELDS 2
#define FLAG_SHOW_REGISTERS 3

typedef struct option_wrapper
{
    const struct option *name;
    const char *usage;
} option_wrapper;

static int flag_fb_group = 0;
static int flag_fb_register = 0;
static int flag_fb_bitfield = 0;
static int flag_fb_all = 0;
static int flag_fb_el0 = 0;
static int flag_fb_el1 = 0;
static int flag_fb_show_info = 0;
static int flag_fb_showerrors = 0;
static int flag_fb_noparse = 0;
static int flag_fb_calc = 0;
static int flag_fb_devices = 0;

static const struct option long_options[] =
{
    { "arch", required_argument, 0, 'a' },
    { "impl", required_argument, 0, 'i' },
    { "core", required_argument, 0, 'c' },
    { "calc", required_argument, 0, 'v' },
    { "help", no_argument, 0, 'h' },

    { "group", no_argument, &flag_fb_group, 1 },
    { "register", no_argument, &flag_fb_register, 1 },
    { "bitfield", no_argument, &flag_fb_bitfield, 1 },
    { "all", no_argument, &flag_fb_all, 1 },
    { "noparse", no_argument, &flag_fb_noparse, 1 },
    { "showfail", no_argument, &flag_fb_showerrors, 1 },
    { "el0", no_argument, &flag_fb_el0, 1 },
    { "el1", no_argument, &flag_fb_el1, 1 },
    { "devices", no_argument, &flag_fb_devices, 1 },
    { "show_groups", no_argument, &flag_fb_show_info, FLAG_SHOW_GROUPS },
    { "show_bitfields", no_argument, &flag_fb_show_info, FLAG_SHOW_BITFIELDS },
    { "show_registers", no_argument, &flag_fb_show_info, FLAG_SHOW_REGISTERS },
    { 0, 0, 0, 0 },
};

static void print_usage(void)
{
    size_t i = 0;
    static const option_wrapper usage_struct[] =
    {
        { long_options, "armv7a or armv8a" },
        { long_options, "cortex-a7, cortex-a15, cortex-a53, cortex-a57, or all" },
        { long_options, "core number, or -1 for all cores" },
        { long_options, "supply register value. Use with --register <regname>" },
        { long_options, "show this menu" },

        { long_options, "search by group" },
        { long_options, "search by register" },
        { long_options, "search by bitfield" },
        { long_options, "search all available bitfields" },
        { long_options, "don't parse the results into bitfields" },
        { long_options, "show all results regardless of success" },
        { long_options, "force execution at pl0" },
        { long_options, "force execution at pl1" },
        { long_options, "include memory-mapped devices (memory intensive)" },
        { long_options, "shows all valid functional groups" },
        { long_options, "shows all valid bitfields" },
        { long_options, "shows all valid register" },
    };

    printf("Usage: maplesyrup --<register|group|bitfield|all> <NAME or ID> --arch=<ARCH> --impl=<IMPL or all> [--core=<CORE or -1>] [OTHER OPTIONS]\n\n");

    for (i = 0; i < (sizeof(usage_struct) / sizeof(option_wrapper)); ++i)
    {
        printf("  --%-16s - %s\n", usage_struct[i].name[i].name, usage_struct[i].usage);
    }

    printf("\nExamples:\n");
    printf("  (1) maplesyrup --register MIDR --arch=armv7a --impl=all\n");
    printf("  (2) maplesyrup --all --arch=armv7a --impl=all\n");
    printf("  (3) maplesyrup --register MIDR --arch=armv7a --impl=all --calc=0x410fc073\n");
    printf("\nThe kernel module must be loaded before running.\n");
}

static void show_banner(unsigned int val1,
                        unsigned int valid_elements,
                        unsigned int elements)
{
    printf("\n============================\n");
    printf("|| Maplesyrup 2.0         ||\n");
#ifdef __gnu_linux__
    printf("||    -linux              ||\n");
#endif
#ifdef __ANDROID__
    printf("||    -android            ||\n");
#endif
#ifdef __aarch64__
    printf("||    -aarch64            ||\n");
#else
    printf("||    -aarch32            ||\n");
#endif

    if (val1)
    {
        printf("============================\n\n\t--help for options\n");
    }
    else
    {
        printf("||                        ||\n");
        printf("|| %06u/%06u entries  ||\n", valid_elements, elements);
        printf("============================\n");
    }
}

static int get_ppl_from_flag(unsigned int el0, unsigned int el1)
{
    if (el0 > 0 && el1 == 0)
        return NS_PRIVILEGE_LEVEL_0;
    if (el0 == 0 && el1 > 0)
        return NS_PRIVILEGE_LEVEL_1;
    if (el0 > 0 && el1 > 0)
        return (NS_PRIVILEGE_LEVEL_0 | NS_PRIVILEGE_LEVEL_1);
    return PREFERRED_PL;
}

static int no_results(ms_bitfield_info *output)
{
    int elements = 0;
    int i = 0;
    int valid_elements = 0;

    if (output == NULL)
        return -1;

    elements = ms_get_size(output);
    for (i = 0; i < elements; ++i)
    {
        if (ms_get_status(output, i) == 0)
            ++valid_elements;
    }

    if (valid_elements > 0 || flag_fb_showerrors == 1)
    {
        show_banner(0, (unsigned int)valid_elements, (unsigned int)elements);
        return 0;
    }

    printf("No results\n");
    return -1;
}

static void show_results(ms_bitfield_info *output)
{
    int elements = 0;
    int i = 0;

    if (output == NULL)
        return;

    elements = ms_get_size(output);
    if (no_results(output) != 0 && flag_fb_showerrors == 0)
        return;

    for (i = 0; i < elements; ++i)
    {
        if (ms_get_status(output, i) == 0 || flag_fb_showerrors == 1)
        {
            printf("[cpu%d/%s/%s/%d/%s/%s/%s/%s]: 0x%llx (%s) (%d)\n",
                   ms_get_cpu(output, i),
                   ms_get_partnumber_string(output, i),
                   ms_get_decode_string(output, i),
                   ms_get_epl(output, i),
                   ms_get_group_string(output, i),
                   ms_get_register_string(output, i),
                   ms_get_stamp(output, i),
                   ms_get_bitfield_string(output, i),
                   ms_get_value(output, i),
                   ms_get_description_string(output, i),
                   ms_get_status(output, i));
        }
    }
}

int main(int argc, char **argv)
{
    int c = 0;
    int result = -1;
    int i = 0;
    char arg_arch[MAX_ARCH_BUFFER];
    char arg_impl[MAX_IMPL_BUFFER];
    char arg_calc[MAX_CALC_BUFFER];
    ms_bitfield_info *output = NULL;
    ms_bitfield_info *toshow = NULL;
    int arg_core = -1;
    int option_index = 0;
    int ppl = 0;

    memset(arg_arch, 0, sizeof(arg_arch));
    memset(arg_impl, 0, sizeof(arg_impl));
    memset(arg_calc, 0, sizeof(arg_calc));

    if (argc == 1)
    {
        show_banner(1, 0, 0);
        return 0;
    }

    while ((c = getopt_long(argc, argv, "t:a:i:c:v:h", long_options, &option_index)) != -1)
    {
        switch (c)
        {
            case 0:
                break;
            case 'a':
                strncpy(arg_arch, optarg, sizeof(arg_arch) - 1);
                arg_arch[sizeof(arg_arch) - 1] = '\0';
                break;
            case 'i':
                strncpy(arg_impl, optarg, sizeof(arg_impl) - 1);
                arg_impl[sizeof(arg_impl) - 1] = '\0';
                break;
            case 'c':
                arg_core = atoi(optarg);
                break;
            case 'v':
                strncpy(arg_calc, optarg, sizeof(arg_calc) - 1);
                arg_calc[sizeof(arg_calc) - 1] = '\0';
                flag_fb_calc = 1;
                break;
            case '?':
            case 'h':
                print_usage();
                return 0;
            default:
                show_banner(1, 0, 0);
                return -1;
        }
    }

    if (flag_fb_show_info)
    {
        switch (flag_fb_show_info)
        {
            case FLAG_SHOW_GROUPS:
                ms_get_groups(&toshow, flag_fb_devices);
                no_results(toshow);
                for (i = 0; i < ms_get_size(toshow); ++i)
                {
                    printf("%s\n", ms_get_group_string(toshow, i));
                }
                ms_free_result(&toshow);
                break;
            case FLAG_SHOW_BITFIELDS:
                ms_get_bitfields(&toshow, flag_fb_devices);
                no_results(toshow);
                for (i = 0; i < ms_get_size(toshow); ++i)
                {
                    printf("0x%08x (%s.%s.%s)\n",
                           ms_get_uid(toshow, i),
                           ms_get_decode_string(toshow, i),
                           ms_get_register_string(toshow, i),
                           ms_get_bitfield_string(toshow, i));
                }
                ms_free_result(&toshow);
                break;
            case FLAG_SHOW_REGISTERS:
                ms_get_registers(&toshow, flag_fb_devices);
                no_results(toshow);
                for (i = 0; i < ms_get_size(toshow); ++i)
                {
                    printf("%s\n", ms_get_register_string(toshow, i));
                }
                ms_free_result(&toshow);
                break;
            default:
                break;
        }
        return 0;
    }

    ppl = get_ppl_from_flag((unsigned int)flag_fb_el0, (unsigned int)flag_fb_el1);

    if (flag_fb_bitfield)
    {
        if (optind < argc)
        {
            unsigned int bf_id = (unsigned int)strtoul(argv[optind], NULL, 0);
            if (ms_find_by_bitfield(arg_arch,
                                    arg_impl,
                                    bf_id,
                                    arg_core,
                                    (unsigned int)ppl,
                                    (unsigned int)flag_fb_noparse,
                                    flag_fb_devices,
                                    &output) != 0)
            {
                goto done;
            }
        }
    }
    else if (flag_fb_group)
    {
        if (optind < argc)
        {
            if (ms_find_by_group(arg_arch,
                                 arg_impl,
                                 argv[optind],
                                 arg_core,
                                 (unsigned int)ppl,
                                 (unsigned int)flag_fb_noparse,
                                 flag_fb_devices,
                                 &output) != 0)
            {
                goto done;
            }
        }
    }
    else if (flag_fb_register)
    {
        if (optind < argc)
        {
            if (ms_find_by_register(arg_arch,
                                    arg_impl,
                                    argv[optind],
                                    arg_core,
                                    (unsigned int)ppl,
                                    (unsigned int)flag_fb_noparse,
                                    flag_fb_calc ? arg_calc : NULL,
                                    flag_fb_devices,
                                    &output) != 0)
            {
                goto done;
            }
        }
    }
    else if (flag_fb_all)
    {
        ms_get_groups(&toshow, flag_fb_devices);
        for (i = 0; i < ms_get_size(toshow); ++i)
        {
            if (ms_find_by_group(arg_arch,
                                 arg_impl,
                                 ms_get_group_string(toshow, i),
                                 arg_core,
                                 (unsigned int)ppl,
                                 (unsigned int)flag_fb_noparse,
                                 flag_fb_devices,
                                 &output) != 0)
            {
                goto done;
            }
            show_results(output);
            ms_free_result(&output);
        }
        result = 0;
        goto done;
    }
    else
    {
        goto done;
    }

    show_results(output);
    result = 0;

done:
    ms_free_result(&toshow);
    ms_free_result(&output);
    return result;
}
