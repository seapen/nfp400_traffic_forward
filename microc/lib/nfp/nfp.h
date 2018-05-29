/*
 * Copyright (C) 2008-2015 Netronome Systems, Inc.  All rights reserved.
 */

/* NFP definitions */

#ifndef __NFP_H__
#define __NFP_H__

#ifndef NFP_LIB_ANY_NFCC_VERSION
    #if (!defined(__NFP_TOOL_NFCC) ||                       \
        (__NFP_TOOL_NFCC < NFP_SW_VERSION(5, 0, 0, 0)) ||   \
        (__NFP_TOOL_NFCC > NFP_SW_VERSION(6, 0, 2, 255)))
        #error "This standard library is not supported for the version of the SDK currently in use."
    #endif
#endif

/*
 * convenience macros
 */

#define __atomic        __declspec(atomic)
#define __sram          __declspec(sram)
#define __imem          __declspec(imem)
#define __imem_n(x)     __declspec(imem##x)
#define __emem          __declspec(emem)
#define __emem_n(x)     __declspec(emem##x)
#define __dram          __declspec(dram)
#define __mem           __declspec(mem)
#define __cls           __declspec(cls)
#define __cls_n(x)      __declspec(cls##x)
#define __ctm           __declspec(ctm)
#define __ctm_n(x)      __declspec(ctm##x)
#define __lmem          __declspec(local_mem)
#define __export        __declspec(export)
#define __import        __declspec(import)
#define __shared        __declspec(shared)
#define __visible       __declspec(visible)
#define __remote        __declspec(remote)
#define __addr40        __declspec(addr40)
#define __addr32        __declspec(addr32)
#define __xread         __declspec(read_reg)
#define __xwrite        __declspec(write_reg)
#define __xrw           __declspec(read_write_reg)
#define __gpr           __declspec(gp_reg)
#define __nnr           __declspec(nn_local_reg)

#define __align(x)      __declspec(aligned(x))
#define __align2        __declspec(aligned(2))
#define __align4        __declspec(aligned(4))
#define __align8        __declspec(aligned(8))
#define __align16       __declspec(aligned(16))
#define __align32       __declspec(aligned(32))
#define __align64       __declspec(aligned(64))
#define __align128      __declspec(aligned(128))
#define __align256      __declspec(aligned(256))
#define __align512      __declspec(aligned(512))
#define __align1K       __declspec(aligned(SZ_1K))
#define __align2K       __declspec(aligned(SZ_2K))
#define __align4K       __declspec(aligned(SZ_4K))
#define __align8K       __declspec(aligned(SZ_8K))
#define __align16K      __declspec(aligned(SZ_16K))
#define __align32K      __declspec(aligned(SZ_32K))
#define __align64K      __declspec(aligned(SZ_64K))
#define __align128K     __declspec(aligned(SZ_128K))
#define __align256K     __declspec(aligned(SZ_256K))
#define __align512K     __declspec(aligned(SZ_512K))
#define __align1M       __declspec(aligned(SZ_1M))
#define __align2M       __declspec(aligned(SZ_2M))
#define __align4M       __declspec(aligned(SZ_4M))
#define __align8M       __declspec(aligned(SZ_8M))
#define __align16M      __declspec(aligned(SZ_16M))
#define __align32M      __declspec(aligned(SZ_32M))
#define __align64M      __declspec(aligned(SZ_64M))
#define __align128M     __declspec(aligned(SZ_128M))
#define __align256M     __declspec(aligned(SZ_256M))
#define __align512M     __declspec(aligned(SZ_512M))
#define __align1G       __declspec(aligned(SZ_1G))
#define __align2G       __declspec(aligned(SZ_2G))
#define __packed        __declspec(packed)
#define __packed_bits   __declspec(packed_bits)


#if (defined(NFP_STDLIB_ENABLE_CMD_INTRINSICS) || defined(NFP_STDLIB_LEGACY))
#include <nfp_legacy.h>
#else

/*
 * generic definitions
 */

#if !defined(offsetof)
#define offsetof(s,m)  ((size_t)&(((s *)0)->m))
#endif

#define SZ_512          (1U <<  9)
#define SZ_1K           (1U << 10)
#define SZ_2K           (1U << 11)
#define SZ_4K           (1U << 12)
#define SZ_8K           (1U << 13)
#define SZ_16K          (1U << 14)
#define SZ_32K          (1U << 15)
#define SZ_64K          (1U << 16)
#define SZ_128K         (1U << 17)
#define SZ_256K         (1U << 18)
#define SZ_512K         (1U << 19)
#define SZ_1M           (1U << 20)
#define SZ_2M           (1U << 21)
#define SZ_4M           (1U << 22)
#define SZ_8M           (1U << 23)
#define SZ_16M          (1U << 24)
#define SZ_32M          (1U << 25)
#define SZ_64M          (1U << 26)
#define SZ_128M         (1U << 27)
#define SZ_256M         (1U << 28)
#define SZ_512M         (1U << 29)
#define SZ_1G           (1U << 30)
#define SZ_2G           (1U << 31)

#define __is_log2(val)  ((((val)-1)&(val))==0)

#define __log2(val)          \
    ((val) >= SZ_2G   ? 31 : \
     (val) >= SZ_1G   ? 30 : \
     (val) >= SZ_512M ? 29 : \
     (val) >= SZ_256M ? 28 : \
     (val) >= SZ_128M ? 27 : \
     (val) >= SZ_64M  ? 26 : \
     (val) >= SZ_32M  ? 25 : \
     (val) >= SZ_16M  ? 24 : \
     (val) >= SZ_8M   ? 23 : \
     (val) >= SZ_4M   ? 22 : \
     (val) >= SZ_2M   ? 21 : \
     (val) >= SZ_1M   ? 20 : \
     (val) >= SZ_512K ? 19 : \
     (val) >= SZ_256K ? 18 : \
     (val) >= SZ_128K ? 17 : \
     (val) >= SZ_64K  ? 16 : \
     (val) >= SZ_32K  ? 15 : \
     (val) >= SZ_16K  ? 14 : \
     (val) >= SZ_8K   ? 13 : \
     (val) >= SZ_4K   ? 12 : \
     (val) >= SZ_2K   ? 11 : \
     (val) >= SZ_1K   ? 10 : \
     (val) >= 512     ?  9 : \
     (val) >= 256     ?  8 : \
     (val) >= 128     ?  7 : \
     (val) >= 64      ?  6 : \
     (val) >= 32      ?  5 : \
     (val) >= 16      ?  4 : \
     (val) >= 8       ?  3 : \
     (val) >= 4       ?  2 : \
     (val) >= 2       ?  1 : \
     (val) >= 1       ?  0 : -1)

#define __is_aligned(base,align)  ((((unsigned)(base))&((align)-1))==0)


/*
 * architecture-related
 */

#define __nfp3216  0x20000
#define __nfp3240  0x40000
#define __nfp3200  (__nfp3216|__nfp3240)
#define __nfp32xx  __nfp3200

#define __nfp6000  0x80000
#define __nfp6xxx  __nfp6000

#define __nfp_stepping(major,minor)  (((major-'A')<<4)|minor&0xf)
#define __REVISION_A0  __nfp_stepping('A', 0)
#define __REVISION_A1  __nfp_stepping('A', 1)
#define __REVISION_B0  __nfp_stepping('B', 0)
#define __REVISION_C0  __nfp_stepping('C', 0)

/*
 * inline assembler attributes
 */

#define ASM_HAS_JUMP            0x0001
#define LITERAL_ASM             0x0002
#define LITERAL_ASM_HAS_JUMP    0x0003


/*
 * intrinsic aliases
 */

#define __is_read_write_reg(p)  (__is_read_reg(p)&&__is_write_reg(p))
#define __is_in_mem  __is_in_dram

#define free_write_buffer(a)    __free_write_buffer(a)
#define global_label(a)         __global_label(a)
#define LoadTimeConstant(a)     __LoadTimeConstant(a)
#define ctx()                   __ctx()
#define n_ctx()                 __n_ctx()
#define nctx_mode()             __nctx_mode()
#define wait_for_any            __wait_for_any
#define wait_for_any_single     __wait_for_any_single
#define wait_for_all            __wait_for_all
#define wait_for_all_single     __wait_for_all_single
#define lmpt_reserve            __lmpt_reserve


#define __MEID    __LoadTimeConstant("__UENGINE_ID")
#define __MENUM   __LoadTimeConstant("__menum")
#define __ISLAND  __LoadTimeConstant("__island")


/*
 * type definitions
 */

typedef int SIGNAL_MASK;

typedef __declspec(signal) int SIGNAL;

typedef __declspec(signal_pair) struct SIGNAL_PAIR {
    int even;
    int odd;
} SIGNAL_PAIR;

typedef enum {
    sig_done,
    ctx_swap
} sync_t;

typedef enum {
    kill,
    voluntary,
    bpt
} signal_t;

typedef enum {
    swpack_none,
    swpack_lmem,
    swpack_auto,
    swpack_1,
    swpack_2,
    swpack_3,
    swpack_4,
    swpack_5,
    swpack_6,
    swpack_7,
    swpack_8
} swpack_t;

typedef enum {
    local_csr_ustore_address                = 0x000,
    local_csr_ustore_data_lower             = 0x001,
    local_csr_ustore_data_upper             = 0x002,
    local_csr_ustore_error_status           = 0x003,
    local_csr_alu_out                       = 0x004,
    local_csr_ctx_arb_cntl                  = 0x005,
    local_csr_ctx_enables                   = 0x006,
    local_csr_cc_enable                     = 0x007,
    local_csr_csr_ctx_pointer               = 0x008,
    local_csr_pc_breakpoint_0               = 0x009,
    local_csr_pc_breakpoint_1               = 0x00a,
    local_csr_pc_breakpoint_status          = 0x00b,
    local_csr_lm_register_error_status      = 0x00c,
    local_csr_lm_error_status               = 0x00d,
    local_csr_lm_error_mask                 = 0x00e,
    local_csr_indirect_ctx_sts              = 0x010,
    local_csr_active_ctx_sts                = 0x011,
    local_csr_indirect_ctx_sig_events       = 0x012,
    local_csr_active_ctx_sig_events         = 0x013,
    local_csr_indirect_ctx_wakeup_events    = 0x014,
    local_csr_active_ctx_wakeup_events      = 0x015,
    local_csr_indirect_ctx_future_count     = 0x016,
    local_csr_active_ctx_future_count       = 0x017,
    local_csr_byte_index                    = 0x01c,
    local_csr_t_index                       = 0x01d,
    local_csr_indirect_future_count_signal  = 0x01e,
    local_csr_active_future_count_signal    = 0x01f,
    local_csr_nn_put                        = 0x020,
    local_csr_nn_get                        = 0x021,
    local_csr_indirect_lm_addr_0            = 0x018,
    local_csr_active_lm_addr_0              = 0x019,
    local_csr_indirect_lm_addr_1            = 0x01a,
    local_csr_active_lm_addr_1              = 0x01b,
    local_csr_indirect_lm_addr_2            = 0x024,
    local_csr_active_lm_addr_2              = 0x025,
    local_csr_indirect_lm_addr_3            = 0x026,
    local_csr_active_lm_addr_3              = 0x027,
    local_csr_indirect_lm_addr_0_byte_index = 0x038,
    local_csr_active_lm_addr_0_byte_index   = 0x039,
    local_csr_indirect_lm_addr_1_byte_index = 0x03a,
    local_csr_active_lm_addr_1_byte_index   = 0x03b,
    local_csr_indirect_lm_addr_2_byte_index = 0x028,
    local_csr_active_lm_addr_2_byte_index   = 0x029,
    local_csr_indirect_lm_addr_3_byte_index = 0x02a,
    local_csr_active_lm_addr_3_byte_index   = 0x02b,
    local_csr_indirect_predicate_cc         = 0x02c,
    local_csr_t_index_byte_index            = 0x03d,
    local_csr_timestamp_low                 = 0x030,
    local_csr_timestamp_high                = 0x031,
    local_csr_next_neighbor_signal          = 0x040,
    local_csr_prev_neighbor_signal          = 0x041,
    local_csr_same_me_signal                = 0x042,
    local_csr_crc_remainder                 = 0x050,
    local_csr_profile_count                 = 0x051,
    local_csr_pseudo_random_number          = 0x052,
    local_csr_misc_control                  = 0x058,
    pc_breakpoint_0_mask                    = 0x059,
    pc_breakpoint_1_mask                    = 0x05a,
    local_csr_mailbox0                      = 0x05c,
    local_csr_mailbox1                      = 0x05d,
    local_csr_mailbox2                      = 0x05e,
    local_csr_mailbox3                      = 0x05f,
    local_csr_mailbox_0                     = 0x05c,
    local_csr_mailbox_1                     = 0x05d,
    local_csr_mailbox_2                     = 0x05e,
    local_csr_mailbox_3                     = 0x05f,
    local_csr_cmd_indirect_ref0             = 0x064,
    local_csr_cmd_indirect_ref1             = 0x065,
    local_csr_cmd_indirect_ref_0            = 0x064,
    local_csr_cmd_indirect_ref_1            = 0x065,
    local_csr_reserved                      = 0x0ff
} local_csr_t;


/*
 * compiler intrinsic functions
 */

   long long __LoadTimeConstant();
   unsigned long long __alloc_resource();
   void __assign_relative_register();
/* LEGACY __associate_dram_read_write_reg_pair_no_spill */
   void __associate_read_write_reg_pair_no_spill();
/* LEGACY __associate_sram_read_write_reg_pair_no_spill */
   void __critical_path();
   void __ct_Qperfinfo();
   void __ct_assert();
   unsigned int __ctx();
/* UNPROT __disam_assert_on_no_overlap */
/* UNPROT __disam_assert_on_overlap */
   int __elem_size();
   void __free_write_buffer();
   void __global_label();
/* UNPROT __gp_reg_number */
   void __implicit_read();
   void __implicit_undef();
   void __implicit_write();
   void __impossible_path();
/* UNPROT __index_xfer */
   void __intrinsic_begin();
   void __intrinsic_end();
   int __is_ct_const();
/* LEGACY __is_dram_read_reg */
/* LEGACY __is_dram_reg */
/* LEGACY __is_dram_write_reg */
   int __is_in_cls();
   int __is_in_ctm();
   int __is_in_dram();
   int __is_in_emem();
   int __is_in_emem_cache();
   int __is_in_imem();
   int __is_in_lmem();
   int __is_in_reg();
   int __is_in_reg_or_lmem();
/* LEGACY __is_in_scratch */
   int __is_in_sram();
/* LEGACY __is_in_ustore */
   int __is_nfp_arch();
   int __is_nfp_arch_or_above();
   int __is_read_reg();
/* LEGACY __is_sram_read_reg */
/* LEGACY __is_sram_reg */
/* LEGACY __is_sram_write_reg */
   int __is_write_reg();
   int __is_xfer_reg();
   long long __link_sym();
   long long __load_expr();
   unsigned int __n_ctx();
   unsigned int __nctx_mode();
   int __nfp_idstr2meid();
   int __nfp_meid();
   void __no_spill_begin();
   void __no_spill_end();
   void __no_swap_begin();
   void __no_swap_end();
/* PRINTF __pflush */
/* PRINTF __plinebuf */
/* PRINTF __printf */
/* PRINTF __put */
/* PRINTF __puthc */
/* PRINTF __puthi */
/* PRINTF __puthll */
/* PRINTF __putns */
/* PRINTF __puts */
/* PRINTF __putsi */
/* PRINTF __putsll */
/* PRINTF __putui */
/* PRINTF __putull */
/* UNPROT __reserve_relative_register */
   int __signal_number();
   SIGNAL_MASK __signals();
   void __switch_pack();
   void __timer_report();
   void __timer_report_all_ctx();
   void __timer_reset();
   void __timer_start();
   void __timer_stop();
   void __timer_strobe();
   void __wait_for_all();
   void __wait_for_all_single();
   void __wait_for_any();
   void __wait_for_any_single();
   int __xfer_reg_number();
/* PRINTF printf */
   int signal_test();
/* UNPROT ua_get_atomic_u64 */
   int ua_get_s16();
   int ua_get_s32();
   long long ua_get_s64();
   int ua_get_s8();
   unsigned int ua_get_u16();
   unsigned int ua_get_u32();
   unsigned long long ua_get_u64();
   unsigned int ua_get_u8();
   unsigned int ua_get_u8_cls();
/* LEGACY ua_get_u8_dram */
/* LEGACY ua_get_u8_scratch */
   unsigned int ua_get_u8_sram();
   void ua_memcpy();
   void ua_set_16();
   void ua_set_32();
   void ua_set_64();
   void ua_set_8();

   void __lmpt_reserve(void);

#endif /* NFP_STDLIB_ENABLE_CMD_INTRINSICS || NFP_STDLIB_LEGACY */

   __intrinsic void local_csr_write(local_csr_t csr, unsigned int data);
   __intrinsic unsigned int local_csr_read(local_csr_t csr);

    __intrinsic unsigned int dbl_shr(unsigned int srcA, unsigned int srcB, unsigned int shift_cnt);
    __intrinsic unsigned int dbl_shl(unsigned int srcA, unsigned int srcB, unsigned int shift_cnt);

#endif /* __NFP_H__ */

