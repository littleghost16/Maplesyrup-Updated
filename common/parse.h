#ifndef _MS_PARSE_H
#define _MS_PARSE_H

#ifdef __KERNEL__
#include <linux/types.h>
#include <linux/ioctl.h>
#else
#include <stdint.h>
#include <stddef.h>
#include <sys/ioctl.h>
#endif

#include "support.h"

#define MS_MAX_CPUS 8

#define MS_MAGIC 0xB0
#define MS_IOCTL_CO         _IO(MS_MAGIC, 0)
#define MS_IOCTL_MM         _IO(MS_MAGIC, 1)
#define MS_IOCTL_GIC        _IO(MS_MAGIC, 2)
#define MS_IOCTL_TRACE      _IO(MS_MAGIC, 3)
#define MS_IOCTL_DEBUG      _IO(MS_MAGIC, 4)

typedef struct ms_data
{
    unsigned int cpu;
    unsigned int midr;
    unsigned int in1;
    unsigned int in2;
    unsigned long long out64;
    unsigned int out1;
    unsigned int out2;
    unsigned int status;
} ms_data;

typedef struct ms_data_cpu
{
    unsigned int code;
    unsigned int pcpu;
    unsigned int part_number;
    ms_data cpu[MS_MAX_CPUS];
} ms_data_cpu;

#define PARTNUMBER_BITS     5
#define INSTRUCTION_BITS    11
#define FIELD_BITS          16

#define MSCODE_FIELDSHIFT 0
#define MSCODE_INSTRUCTIONSHIFT (MSCODE_FIELDSHIFT + FIELD_BITS)
#define MSCODE_PARTNUMBERSHIFT  (MSCODE_INSTRUCTIONSHIFT + INSTRUCTION_BITS)

#define PARTNUMBER_MASK     ((1U << PARTNUMBER_BITS) - 1U)
#define INSTRUCTION_MASK    ((1U << INSTRUCTION_BITS) - 1U)
#define FIELD_MASK          ((1U << FIELD_BITS) - 1U)

#define MSCODE(partnumber, instruction, field) \
        ((((unsigned int)(partnumber)) << MSCODE_PARTNUMBERSHIFT) | \
         (((unsigned int)(instruction)) << MSCODE_INSTRUCTIONSHIFT) | \
         (((unsigned int)(field)) << MSCODE_FIELDSHIFT))

#define MSCODE_PARTNUMBER(code)     ((((unsigned int)(code)) >> MSCODE_PARTNUMBERSHIFT) & PARTNUMBER_MASK)
#define MSCODE_INSTRUCTION(code)    ((((unsigned int)(code)) >> MSCODE_INSTRUCTIONSHIFT) & INSTRUCTION_MASK)
#define MSCODE_FIELD(code)          ((((unsigned int)(code)) >> MSCODE_FIELDSHIFT) & FIELD_MASK)

#define PARSE_MAX_DESCRIPTION 256
#define PARSE_MAX_BITFIELD 64
#define PARSE_MAX_FUNCTIONAL 64
#define PARSE_MAX_REGISTER 32
#define PARSE_MAX_PARTNUMBER 64
#define PARSE_MAX_ARCHITECTURE 16
#define PARSE_MAX_IMPLEMENTATION 16

typedef struct bitfield_info
{
    unsigned int range;
    int uid;
    unsigned int register_uid;
    unsigned int ppl;
    unsigned int rightshift;
    unsigned int mask;
    char *bitfield;
    char *functional_group;
    char *register_name;
    char *description;
} bitfield_info;

typedef struct bitfield_info_populated
{
    list_element list;
    unsigned int cpu;
    unsigned int epl;
    unsigned int uid;
    unsigned int ioctl;
    unsigned int midr;
    unsigned int status;
    char bitfield[PARSE_MAX_BITFIELD];
    char functional_group[PARSE_MAX_FUNCTIONAL];
    char register_name[PARSE_MAX_REGISTER];
    char description[PARSE_MAX_DESCRIPTION];
    unsigned long long value;
    unsigned long long uvalue;
} bitfield_info_populated;

extern bitfield_info bitfield_info_table[];

typedef struct match_info
{
    unsigned int architecture;
    unsigned int implementation;
    unsigned char functional_group[PARSE_MAX_FUNCTIONAL];
    unsigned char register_name[PARSE_MAX_REGISTER];
    unsigned int uid;
    unsigned int pl;
    unsigned int noparse;
    unsigned int cpu;
    unsigned int calc;
    unsigned long long calc_value;
} match_info;

typedef struct results_info
{
    list_element list;
    unsigned int register_uid;
    unsigned int uid;
    unsigned int ppl;
    unsigned int pl;
    unsigned int cpu;
    unsigned int noparse;
    unsigned int part_number;
    unsigned int calc;
    unsigned long long calc_value;
} results_info;

typedef struct used_ioctl
{
    list_element list;
    unsigned int register_uid;
    unsigned int cpu;
    unsigned int partnumber;
} used_ioctl;

typedef struct ioctl_result
{
    list_element list;
    unsigned int register_uid;
    unsigned long long val64;
    unsigned int low;
    unsigned int high;
    unsigned int cpu;
    unsigned int midr;
    unsigned int epl;
    unsigned int status;
} ioctl_result;

typedef struct table_index
{
    list_element list;
    unsigned int index;
} table_index;

enum
{
    MS_SYSREG_PFR0 = 1,
    MS_SYSREG_PFR1,
    MS_SYSREG_DFR0,
    MS_SYSREG_AFR0,
    MS_SYSREG_MMFR0,
    MS_SYSREG_MMFR1,
    MS_SYSREG_MMFR2,
    MS_SYSREG_MMFR3,
    MS_SYSREG_MMFR4,
    MS_SYSREG_ISAR0,
    MS_SYSREG_ISAR1,
    MS_SYSREG_ISAR2,
    MS_SYSREG_ISAR3,
    MS_SYSREG_ISAR4,
    MS_SYSREG_ISAR5,
    MS_SYSREG_REVIDR,
    MS_SYSREG_TLBTR,
    MS_SYSREG_CCSIDR,
    MS_SYSREG_TCMTR,
    MS_SYSREG_AIDR,
    MS_SYSREG_CLIDR,
    MS_SYSREG_CSSELR,
    MS_SYSREG_CTR,
    MS_SYSREG_MIDR,
    MS_SYSREG_MPIDR,
    MS_SYSREG_AA64AFR0,
    MS_SYSREG_AA64AFR1,
    MS_SYSREG_AA64DFR0,
    MS_SYSREG_AA64DFR1,
    MS_SYSREG_AA64ISAR0,
    MS_SYSREG_AA64ISAR1,
    MS_SYSREG_AA64MMFR0,
    MS_SYSREG_AA64MMFR1,
    MS_SYSREG_AA64PFR0,
    MS_SYSREG_AA64PFR1,

    MS_SYSREG_ISR,
    MS_SYSREG_MVBAR,
    MS_SYSREG_NSACR,
    MS_SYSREG_SCR,
    MS_SYSREG_SDER,
    MS_SYSREG_VBAR,

    MS_SYSREG_NMRR,
    MS_SYSREG_PRRR,
    MS_SYSREG_SCTLR,
    MS_SYSREG_TTBCR,
    MS_SYSREG_TTBR0,
    MS_SYSREG_TTBR0LPAE,
    MS_SYSREG_TTBR1,
    MS_SYSREG_TTBR1LPAE,
    MS_SYSREG_CONTEXTIDR,
    MS_SYSREG_AMAIR,
    MS_SYSREG_AMAIR0,
    MS_SYSREG_AMAIR1,
    MS_SYSREG_AMAIR2,
    MS_SYSREG_DACR,
    MS_SYSREG_MAIR,
    MS_SYSREG_MAIR0,
    MS_SYSREG_MAIR1,
    MS_SYSREG_DCZID,
    MS_SYSREG_TCR,

    MS_SYSREG_ACTLR,
    MS_SYSREG_CPACR,
    MS_SYSREG_FCSEIDR,
    MS_SYSREG_RMR,
    MS_SYSREG_RVBAR,

    MS_SYSREG_PMCCFILTR,
    MS_SYSREG_PMCR,
    MS_SYSREG_PMCCNTR,
    MS_SYSREG_PMCEID0,
    MS_SYSREG_PMCEID1,
    MS_SYSREG_PMCNTENSET,
    MS_SYSREG_PMCNTENCLR,
    MS_SYSREG_PMINTENSET,
    MS_SYSREG_PMINTENCLR,
    MS_SYSREG_PMOVSCLR,
    MS_SYSREG_PMOVSR,
    MS_SYSREG_PMOVSSET,
    MS_SYSREG_PMSELR,
    MS_SYSREG_PMSWINC,
    MS_SYSREG_PMUSERENR,
    MS_SYSREG_PMXEVCNTR,
    MS_SYSREG_PMXEVTYPER,

    MS_SYSREG_IFAR,
    MS_SYSREG_IFSR,
    MS_SYSREG_ADFSR,
    MS_SYSREG_AIFSR,
    MS_SYSREG_DFAR,
    MS_SYSREG_DFSR,
    MS_SYSREG_AFSR0,
    MS_SYSREG_AFSR1,
    MS_SYSREG_ESR,
    MS_SYSREG_FAR,

    MS_SYSREG_PAR,

    MS_SYSREG_FPEXC,
    MS_SYSREG_FPSCR,
    MS_SYSREG_FPSID,
    MS_SYSREG_MVFR0,
    MS_SYSREG_MVFR1,
    MS_SYSREG_MVFR2,

    MS_SYSREG_DBGDIDR,
    MS_SYSREG_DBGAUTHSTATUS,
    MS_SYSREG_DBGBCR,
    MS_SYSREG_DBGBVR,
    MS_SYSREG_DBGBXVR,
    MS_SYSREG_DBGCID0,
    MS_SYSREG_DBGCID1,
    MS_SYSREG_DBGCID2,
    MS_SYSREG_DBGCID3,
    MS_SYSREG_DBGCIDSR,
    MS_SYSREG_DBGCLAIMCLR,
    MS_SYSREG_DBGCLAIMSET,
    MS_SYSREG_DBGDEVID,
    MS_SYSREG_DBGDEVID1,
    MS_SYSREG_DBGDEVTYPE,
    MS_SYSREG_DBGDRAR,
    MS_SYSREG_DBGDRCR,
    MS_SYSREG_DBGDSAR,
    MS_SYSREG_DBGDSCCR,
    MS_SYSREG_DBGDSCR,
    MS_SYSREG_DBGDSMCR,
    MS_SYSREG_DBGDTRRX,
    MS_SYSREG_DBGDTRTX,
    MS_SYSREG_DBGEACR,
    MS_SYSREG_DBGECR,
    MS_SYSREG_DBGITCTRL,
    MS_SYSREG_DBGITR,
    MS_SYSREG_DBGLAR,
    MS_SYSREG_DBGLSR,
    MS_SYSREG_DBGOSDLR,
    MS_SYSREG_DBGOSLSR,
    MS_SYSREG_DBGOSSRR,
    MS_SYSREG_DBGPCSR,
    MS_SYSREG_DBGPID0,
    MS_SYSREG_DBGPID1,
    MS_SYSREG_DBGPID2,
    MS_SYSREG_DBGPID3,
    MS_SYSREG_DBGPID4,
    MS_SYSREG_DBGPRCR,
    MS_SYSREG_DBGPRSR,
    MS_SYSREG_DBGVCR,
    MS_SYSREG_DBGVIDSR,
    MS_SYSREG_DBGWCR,
    MS_SYSREG_DBGWFAR,
    MS_SYSREG_DBGWVR,

    MS_SYSREG_JIDR,
    MS_SYSREG_JMCR,
    MS_SYSREG_JOSCR,

    MS_SYSREG_TEECR,
    MS_SYSREG_TEEHBR,

    MS_SYSREG_CPUMERRSR,
    MS_SYSREG_L2MERRSR,
    MS_SYSREG_IL1DATA0,
    MS_SYSREG_IL1DATA1,
    MS_SYSREG_IL1DATA2,
    MS_SYSREG_IL1DATA3,
    MS_SYSREG_DL1DATA0,
    MS_SYSREG_DL1DATA1,
    MS_SYSREG_DL1DATA2,
    MS_SYSREG_DL1DATA3,
    MS_SYSREG_L2ACTLR,
    MS_SYSREG_L2CTLR,
    MS_SYSREG_L2ECTLR,
    MS_SYSREG_L2PFR,
    MS_SYSREG_ACTLR2,
    MS_SYSREG_CDBGDR0,
    MS_SYSREG_CDBGDR1,
    MS_SYSREG_CDBGDR2,
    MS_SYSREG_CDBGDCT,
    MS_SYSREG_CDBGICT,
    MS_SYSREG_CDBGDCD,
    MS_SYSREG_CDBGICD,
    MS_SYSREG_CDBGTD,
    MS_SYSREG_CBAR,
    MS_SYSREG_CPUACTLR,
    MS_SYSREG_CPUECTLR,

    MS_SYSREG_NOP01,
    MS_SYSREG_NOP02,
    MS_SYSREG_TPIDRPRW,
    MS_SYSREG_TPIDRURO,
    MS_SYSREG_TPIDRURW,
    MS_SYSREG_HTPIDR,

    MS_SYSREG_APSR,
    MS_SYSREG_CPSR,
    MS_SYSREG_SPSR,

    MS_SYSREG_CURRENTEL,
    MS_SYSREG_DAIF,
    MS_SYSREG_FPCR,
    MS_SYSREG_FPSR,
    MS_SYSREG_NZCV,
    MS_SYSREG_SPSEL,
};

#define MS_GIC_GICC_CTLR            0x0
#define MS_GIC_GICC_PMR             0x4
#define MS_GIC_GICC_BPR             0x8
#define MS_GIC_GICC_IAR             0xC
#define MS_GIC_GICC_EOIR            0x10
#define MS_GIC_GICC_RPR             0x14
#define MS_GIC_GICC_HPPIR           0x18
#define MS_GIC_GICC_ABPR            0x1C
#define MS_GIC_GICC_AIAR            0x20
#define MS_GIC_GICC_AEOIR           0x24
#define MS_GIC_GICC_AHPPIR          0x28
#define MS_GIC_GICC_RESERVED_00     0x2C
#define MS_GIC_GICC_IMPL_DEF_00     0x40
#define MS_GIC_GICC_APR             0xD0
#define MS_GIC_GICC_NSAPR           0xE0
#define MS_GIC_GICC_RESERVED_01     0xF0
#define MS_GIC_GICC_IIDR            0xFC
#define MS_GIC_GICC_DIR             0x1000

#define MS_GIC_GICD_CTLR            0x0
#define MS_GIC_GICD_TYPER           0x4
#define MS_GIC_GICD_IIDR            0x8
#define MS_GIC_GICD_RESERVED_00     0xC
#define MS_GIC_GICD_IMP_DEF_00      0x20
#define MS_GIC_GICD_RESERVED_01     0x40
#define MS_GIC_GICD_IGROUPR         0x80
#define MS_GIC_GICD_ISENABLER       0x100
#define MS_GIC_GICD_ISPENDR         0x200
#define MS_GIC_GICD_ICPENDR         0x280
#define MS_GIC_GICD_ISACTIVER       0x300
#define MS_GIC_GICD_ICACTIVER       0x380
#define MS_GIC_GICD_IPRIORITYR      0x400
#define MS_GIC_GICD_RESERVED_02     0x7FC
#define MS_GIC_GICD_ITARGETSR       0x800
#define MS_GIC_GICD_RESERVED_03     0xBFC
#define MS_GIC_GICD_ICFGR           0xC00
#define MS_GIC_GICD_IMP_DEF_01      0xD00
#define MS_GIC_GICD_NSACR           0xE00
#define MS_GIC_GICD_SGIR            0xF00
#define MS_GIC_GICD_RESERVED_04     0xF04
#define MS_GIC_GICD_CPENDSGIR       0xF10
#define MS_GIC_GICD_SPENDSGIR       0xF20
#define MS_GIC_GICD_RESERVED_05     0xF30
#define MS_GIC_GICD_IDENT           0xFD0
#define MS_GIC_GICD_ICPIDR2         0xFE8

#endif
