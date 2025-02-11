--issue_remarks
--rom_model
--arg_size=0x100
--heap_size=0x1000000
--stack_size=0x1000000
--map_file=x264-dsp.map
#define DSP_CORE

/* modified from
 * /opt/ccstudio/ccs/ccs_base/c6000/include/DM6467.cmd
 *
 * https://e2e.ti.com/support/tools/code-composer-studio-group/ccs/f/code-composer-studio-forum/353583/workaround-for-zero-initialization-of-global-variables-for-coff
 * */

MEMORY
{
#ifndef DSP_CORE   /* ARM exclusive memory regions */

    ARM_IRAM:     o = 0x00000000  l = 0x00008000  /* 32kB Internal ARM instruction RAM */
    ARM_IROM:     o = 0x00008000  l = 0x00008000  /* 32kB Internal ARM instruction ROM */
    ARM_DRAM:     o = 0x00010000  l = 0x00008000  /* 32kB Internal ARM data RAM */
    ARM_DROM:     o = 0x00018000  l = 0x00008000  /* 32kB Internal ARM data ROM */

#endif
#ifdef DSP_CORE    /* DSP exclusive memory regions */

    DSP_L2:       o = 0x00818000  l = 0x00020000  /* 128kB DSP L2 RAM/CACHE */
    DSP_L1P:      o = 0x00E00000  l = 0x00008000  /* 32kB DSP L1 Program RAM/CACHE */
    DSP_L1D:      o = 0x00F00000  l = 0x00008000  /* 32kB DSP L1 Data RAM/CACHE */
    SH_ARM_DRAM:  o = 0x10010000  l = 0x00008000  /* 32kB Shared Internal ARM data RAM */
    SH_ARM_DROM:  o = 0x10018000  l = 0x00008000  /* 32kB Shared Internal ARM data ROM */

#endif
    SH_DSP_L2:    o = 0x11818000  l = 0x00020000  /* 128kB Shared DSP L2 RAM/CACHE */
    SH_DSP_L1P:   o = 0x11E00000  l = 0x00008000  /* 32kB Shared DSP L1 Program RAM/CACHE */
    SH_DSP_L1D:   o = 0x11F00000  l = 0x00008000  /* 32kB Shared DSP L1 Data RAM/CACHE */
    PCI_DATA:     o = 0x30000000  l = 0x10000000  /* 256MB PCI Data */
    EMIFA_CS2:    o = 0x42000000  l = 0x02000000  /* 32MB EMIFA CS2 */
    EMIFA_CS3:    o = 0x44000000  l = 0x02000000  /* 32MB EMIFA CS3 */
    EMIFA_CS4:    o = 0x46000000  l = 0x02000000  /* 32MB EMIFA CS4 */
    EMIFA_CS5:    o = 0x48000000  l = 0x02000000  /* 32MB EMIFA CS5 */
    VLYNQ_DATA:   o = 0x4C000000  l = 0x04000000  /* 64MB VLYNQ data */
    DDR2:         o = 0x80000000  l = 0x20000000  /* 512MB of external DDR */
}

SECTIONS
{
    .text          >  DDR2
    .stack         >  DDR2
    .bss fill = 0  >  DDR2
    .cio           >  DDR2
    .const         >  DDR2
    .data          >  DDR2
    .switch        >  DDR2
    .sysmem        >  DDR2
    .far           >  DDR2
    .args          >  DDR2
    .ppinfo        >  DDR2
    .ppdata        >  DDR2

    /* TI-ABI or COFF sections */
    .pinit         >  DDR2
    .cinit         >  DDR2

    /* EABI sections */
    .binit         >  DDR2
    .init_array    >  DDR2
    .neardata      >  DDR2
    .fardata       >  DDR2
    .rodata        >  DDR2
    .c6xabi.exidx  >  DDR2
    .c6xabi.extab  >  DDR2
}
