/*
 * Copyright (C) 2008-2014 Netronome Systems, Inc.  All rights reserved.
 */

/* NFP enhanced intrinsic function definitions */

#ifndef __NFP_LEGACY_H__
#define __NFP_LEGACY_H__

#ifndef NFP_LIB_ANY_NFCC_VERSION
    #if (!defined(__NFP_TOOL_NFCC) ||                       \
        (__NFP_TOOL_NFCC < NFP_SW_VERSION(5, 0, 0, 0)) ||   \
        (__NFP_TOOL_NFCC > NFP_SW_VERSION(6, 0, 2, 255)))
        #error "This standard library is not supported for the version of the SDK currently in use."
    #endif
#endif

/*
 * NOTE: When writing inline-asm, it's important not to use reserved words
 *       for variables.  Common ones are 'a','b', 'csr', 'state', and
 *       'inp_state'.
 */

#include <nfp_compatibility.h>

/** @file nfp.h
 * @addtogroup misc Miscellaneous Intrinsics
 * @{
 */

/*
 * Convenience macros provided for compatibility with earlier release.
 */
#define free_write_buffer(a)    __free_write_buffer(a)
#define global_label(a)         __global_label(a)
#define LoadTimeConstant(a)     __LoadTimeConstant(a)
#define ctx()                   __ctx()
#define n_ctx()                 __n_ctx()
#define nctx_mode()             __nctx_mode()
#define timer_start(a)          __timer_start(a)
#define timer_stop(a)           __timer_stop(a)
#define timer_strobe(a)         __timer_strobe(a)
#define timer_reset(a)          __timer_reset(a)
#define timer_report(a)         __timer_report(a)
#define timer_report_all_ctx(a) __timer_report_all_ctx(a)
#define sleep(a)                __sleep(a)
#define set_timestamp(a)        __set_timestamp(a)
#define timestamp_start()       __timestamp_start()
#define timestamp_stop(a)       __timestamp_stop(a)
#define set_profile_count(a)    __set_profile_count(a)
#define profile_count_start()   __profile_count_start()
#define profile_count_stop(a)   __profile_count_stop(a)
#define wait_for_any            __wait_for_any
#define wait_for_any_single     __wait_for_any_single
#define wait_for_all            __wait_for_all
#define wait_for_all_single     __wait_for_all_single
#define lmpt_reserve            __lmpt_reserve



/*
 * External memory string constant defines
 */
#define i24_emem_base        "__ADDR_I24_EMEM"      // Type: EMEM, Island: 24
#define i25_emem_base        "__ADDR_I25_EMEM"      // Type: EMEM, Island: 25
#define i26_emem_base        "__ADDR_I26_EMEM"      // Type: EMEM, Island: 26


/* offsetof support */

#if !defined(offsetof)
#define offsetof(s,m)   (size_t)&(((s *)0)->m)
#endif

/*
 * statement attributes
 */
#define ASM_HAS_JUMP            0x0001  /**< Statement attribute. */
#define LITERAL_ASM             0x0002  /**< Statement attribute. */
#define LITERAL_ASM_HAS_JUMP    0x0003  /**< Statement attribute. */



/*
 * 3rd party addressing mode target ID
 */
#define NBI0_TARG_ID                1   /**< Two NBI channels. */
#define QDR_TARG_ID                 2   /**< Address selects channel which is configurable at boot time. */
#define ILA_TAR_ID                  6   /**< Two ILAs.  */
#define MEM_TARG_ID                 7   /**< Memory units for external DDR3, internal memory and Cluster Target Memory. */
#define PCIE_TARG_ID                8   /**< Two PCIe blocks. */
#define ARM11_TARG_ID               10  /**< ARM target id.*/
#define CRYPTO_TARG_ID              12  /**< CRYPTO target id.*/
#define CLUSTER_TARG_ID             14  /**< Access specific cluster by address. */
#define LOCAL_SCRATCH_TARG_ID       15  /**< Local within cluster. */


/*
 * misc define
 */

#ifdef NDEBUG

#define assert(exp)
#define assert_fast(expr)

#else /* NDEBUG */
#ifdef ASSERT_FAST

#define assert(exp) (void)( (exp) || (__assert(0, 0, 0), 0) )
#define assert_fast(exp) (void)( (exp) || (__assert(0, 0, 0), 0) )

#else /* ASSERT_FAST */

#define assert(exp) (void)( (exp) || (__assert(#exp, __FILE__, __LINE__), 0) )
#define assert_fast(exp) (void)( (exp) || (__assert(0, 0, 0), 0) )

#endif /* ASSERT_FAST */
#endif /* NDEBUG */
#define NFCC_VERSION(a,b,c) ((a*10000)+(b*100)+c)

/** Assert. */
__noinline void __assert( char *s, char *f, unsigned l);

/**
 * @}
 */


/*
 *  Make __NFP_INDIRECT_REF_FORMAT_NFP6000 the default when
 * __NFP_INDIRECT_REF_FORMAT_NFP3200 or __NFP_INDIRECT_REF_FORMAT_NFP6000 is not specified
 */

#ifndef __NFP_INDIRECT_REF_FORMAT_NFP3200
    #ifndef __NFP_INDIRECT_REF_FORMAT_NFP6000
    #warning "__NFP_INDIRECT_REF_FORMAT_NFP3200 or __NFP_INDIRECT_REF_FORMAT_NFP6000 is not set, setting __NFP_INDIRECT_REF_FORMAT_NFP6000"
    #define __NFP_INDIRECT_REF_FORMAT_NFP6000
    #endif
#endif


/*
 * Sanity check
 */

#ifndef __NFP_INDIRECT_REF_FORMAT_NFP3200
    #ifndef __NFP_INDIRECT_REF_FORMAT_NFP6000
       #error "__NFP_INDIRECT_REF_FORMAT_NFP3200 or __NFP_INDIRECT_REF_FORMAT_NFP6000 must be set"
   #endif
#endif


/*
 * Enable ptr40 function support only in BIGENDIAN and NFP-32xx indirect reference format mode.
 * If __PTR40 is defined, functions supporting 40-bit pointers are included in the compilation.
 */
#ifdef __BIGENDIAN
    #ifdef __NFP_INDIRECT_REF_FORMAT_NFP3200
        #ifndef NFCC_OMIT_PTR40_INTRINSICS
            #define __PTR40
        #endif
    #endif
    #ifdef __NFP_INDIRECT_REF_FORMAT_NFP6000
        #ifndef NFCC_OMIT_PTR40_INTRINSICS
            #define __PTR40
        #endif
    #endif
#endif


/** @addtogroup signal Synchronization Intrinsics
 *  @{
 * This section describes the data types and functions used for synchronization.
 */

/** SIGNAL_MASK data type is used for masks specifying one or more signal registers. */
typedef int SIGNAL_MASK;

/** SIGNAL data type is used to declare signal variables. */
typedef __declspec(signal) int SIGNAL;

/** SIGNAL_PAIR container type for even/odd signal pair. */
typedef __declspec(signal_pair) struct SIGNAL_PAIR
{
    int even;           /**< Even signal number.  */
    int odd;            /**< Odd signal number.  */
} SIGNAL_PAIR;

/** Sync types for I/O operations. */
typedef enum
{
    sig_done,           /**< Continue execution and set signal when operation is done. */
    ctx_swap            /**< Swap thread out and wait until operation is complete.  */
} sync_t;

/** Signal types for ctx_wait other than mask. */
typedef enum
{
    kill,       /**< Suspend the context.
                 * The kill signal puts the context into the Sleep state and does not return to the Ready state.
                 */
    voluntary,  /**< Put the context in the sleep state.
                 * The voluntary signal puts the context into the Sleep state. The context is
                 * put back into the Ready state in one cycle since the Voluntary Event Signal is always set.
                 */
    bpt         /** The bpt (breakpoint) stops all contexts, interrupts the ARM processor, and puts the current
                 * context into the Sleep state. It also sets the CTX_Enable[Breakpoint] bit.
                 * This value is typically used for debugging purposes. For more information the use of this
                 * value, refer to the ctx_arb instruction in the @prm
                 */
} signal_t;

/**
 * @}
 */


/* Override functionality */
#include "nfp_override.h"

/* generic intrinsics inside __intrinsic */
/* 32xx */
#define __nfp3216  131072
#define __nfp3240  262144
#define __nfp3200 (__nfp3216 | __nfp3240)
#define __nfp32xx __nfp3200

/* 6xxx */
#define __nfp6000  524288
#define __nfp6xxx __nfp6000

/*
 * revision
 */
#define __nfp_stepping(major,minor)     (((major - 'A') << 4) | minor & 0xf)
#define __REVISION_A0                   __nfp_stepping('A', 0)
#define __REVISION_A1                   __nfp_stepping('A', 1)
#define __REVISION_B0                   __nfp_stepping('B', 0)
#define __REVISION_C0                   __nfp_stepping('C', 0)


int __is_ct_const(int v);                       /* v is constant */
int __nfp_meid(int island, int menum);          /* island ID, ME number in island */
int __nfp_idstr2meid(const char *idstr);        /* MEID string, "iX.meY" */

int     __is_in_reg(void *p);                   /* content pointed to is in register, or p==NULL */
int     __is_read_reg(void *p);                 /* content pointed to is read xfer, or p==NULL */
int     __is_write_reg(void *p);                /* content pointed to is write xfer, or p==NULL */
int     __is_xfer_reg(void *p);                 /* content pointed to is xfer, or p==NULL */
#define __is_read_write_reg(_x)    \
    (__is_read_reg(_x) && __is_write_reg(_x))   /* must be read_reg and write_reg */

int     __is_in_lmem(void *p);      /* content pointed to is in LOCAL_MEM, or p==NULL */
#define __is_in_mem  __is_in_dram   /* content pointed to is in CTM. EMEM or IMEM, or p==NULL */

int __is_nfp_arch(int chip_mask, int stepping);
int __is_nfp_arch_or_above(int chip_mask, int stepping_at_least);

int __elem_size(void *p);
void __ct_assert(int v, char *reason);
void __ct_Qperfinfo(int mask, char *info);

void __intrinsic_begin(void);
void __intrinsic_end(void);

void __associate_read_write_reg_pair_no_spill(
    __xread void *rd_buf,                           /* read xfer buffer */
    __xwrite void *wr_buf,                          /* write xfer buffer */
    ...                                             /* (optional) size required */
);


/*__ct_const_val(v);   */     /* used in inline-asm only */
/*__ct_sig_pair(s);    */     /* used in inline-asm only */
/*__ct_4_byte_esize(v);*/     /* used in inline-asm only */

/** @addtogroup signal Synchronization Intrinsics
 *  @{
 */

/** Take address of a signal variable and return the number of the physical signal register allocated to
 * that variable.
 *
 * @param sig Pointer to a signal variable
 * @param ... Optional microengine number
 *
 * This is useful for operations such as setting up of the RX_THREAD_FREELIST CSRs. For signals
 * declared as remote, the __signal_number() takes two arguments, the first being the address of the signal and the
 * second being the microengine number in which the remote signal resides.
 *
 * @note If the signal is declared as remote, the second argument should be an unsigned integer of the microengine on
 * which it resides.
 */
int __signal_number(volatile void *sig, ...);


/** Generate a ctx_arb on the set of signals specified by the arguments.
 *
 * This function take a variable length list of signal pointers, and/or signal masks
 * as arguments and generates a ctx_arb on their union.
 *
 * @param ... List of addresses of SIGNAL or SIGNAL_PAIR variables
 *
 * The OR form of the ctx_arb is generated will return when any signal is set.
 *
 * @note For signal pairs, both even and odd signals are included in the mask used for the ctx_arb. On return,
 * signals also remain set and signal_test() is typically used to ensure they are cleared before next use.
 */
void __wait_for_any(...);


/** Generate a ctx_arb on the set of signals specified by the arguments.
 *
 * This function take a variable length list of signal pointers, and/or signal masks
 * as arguments and generates a ctx_arb on their union.
 *
 * @param ... List of addresses of SIGNAL or SIGNAL_PAIR variables
 *
 * The OR form of the ctx_arb is generated will return when any signal is set.
 *
 * @note For signal pairs, only the even signals are included in the mask used for the ctx_arb. On return,
 * signals also remain set and signal_test() is typically used to ensure they are cleared before next use.
 */
void __wait_for_any_single(...);


/** Generate a ctx_arb on the set of signals specified by the arguments.
 *
 * This function take a variable length list of signal pointers, and/or signal masks
 * as arguments and generates a ctx_arb on their union.
 *
 * @param ... List of addresses of SIGNAL or SIGNAL_PAIR variables
 *
 * The AND form of the ctx_arb is generated which will only return when all signals are set.
 *
 * @note For signal pairs, both even and odd signals are included in the mask used for the ctx_arb.
 */
void __wait_for_all(...);


/** Generate a ctx_arb on the set of signals specified by the arguments.
 *
 * This function take a variable length list of signal pointers, and/or signal masks
 * as arguments and generates a ctx_arb on their union.
 *
 * @param ... List of addresses of SIGNAL or SIGNAL_PAIR variables
 *
 * The AND form of the ctx_arb is generated which will only return when all signals are set.
 *
 * @note For signal pairs, only even signals are included in the mask used for the ctx_arb.
 */
void __wait_for_all_single(...);


/** This intrinsic creates a signal mask out of a variable length argument list of signal pointers,
 * and/or other signal masks.
 *
 * @param ... List of addresses of SIGNAL, SIGNAL_PAIR or signal mask variables
 *
 * Each argument must be one of the following:
 * @li An address of a SIGNAL or SIGNAL_PAIR variable. For signal pairs, both even and odd signals are included
 * in the mask.
 * @li A signal mask.
 *
 * @return A 16 bit signal mask as an int that can be used to generate a ctx_arb either through the
 * __wait_for_all() / __wait_for_all_single() / __wait_for_any() / __wait_for_any_single() intrinsics, or through inline assembly.
 *
 * The returned mask represents the hardware signals allocated to your signal variables. Any number of
 * signals of type SIGNAL between 1 and 15 can be specified.
 *
 * This function is useful for generating signal masks for use with ctx_arb.
 *
 * @note When a user passes in a signal mask to a function as an int parameter, the compiler cannot
 * always figure out what bits are set in the mask and hence does not know the members of the
 * signal set that is represented by the mask. The compiler does not know the life range of these
 * signals represented in such a mask. To get register allocation right, you have to insert calls to
 * implicit_read().
 *
 */
SIGNAL_MASK __signals(...);
/*SIGNAL_MASK __add_signals_to_mask(SIGNAL_MASK mask, ...);   */
/*SIGNAL_MASK __delete_signals_to_mask(SIGNAL_MASK mask, ...);*/

/**
 * @}
 */

/**
 * @addtogroup misc Miscellaneous Intrinsics
 * @{
 */

/** Take the address of a transfer register variable and return the number of the transfer register allocated
 * to that variable.
 *
 * @param xfer  Pointer to a transfer register
 * @param ...   If the signal is declared as remote, the second argument should be an unsigned integer
 *              of the microengine on which it resides.
 *
 * This is useful for operations such as setting up of the RX_THREAD_FREELIST CSRs. For transfer
 * registers declared as remote, the __xfer_reg_number() intrinsic takes two arguments, the first being the address of
 * the transfer register and the second being the microengine number in which the transfer register resides.
 */
int __xfer_reg_number(volatile void *xfer, ...);

/** Take the address of a signal or transfer register variable and indicates that the signal
 * or transfer register is being read asynchronously or implicitly by the hardware.
 *
 * @param sig_or_xfer   Pointer to a signal or transfer register address
 * @param ...           Integer argument that specifies the size in bytes of the read. This can
 *                      be used to target specific elements of a structure or array.
 *
 * This function takes as argument the address of a register variable and indicates that the signal or
 * transfer register is being read asynchronously or implicitly by the hardware. It is necessary to use
 * this intrinsic to mark all definitions and use points of signal/transfer registers that are not directly visible to
 * the compiler. They ensure that the compiler does correct lifetime analysis and hence correct register allocation to
 * such variables. This intrinsic must be used, for example, when the RX_THREAD_FREELIST CSR is written with the
 * register number allocated to a variable, when a signal is requested by writing into a CSR, or a signal is tested
 * by doing a ctx_arb with a signal mask generated with __signals().
 *
 * @note Performs the same task as __free_write_buffer().
 */
void __implicit_read(void *sig_or_xfer, ...);

/** Take the address of a signal or transfer register variable and indicate that the signal or transfer register
 * is being written asynchronously or implicitly by the hardware.
 *
 * @param sig_or_xfer Pointer to a signal or transfer register address
 * @param ...         Integer argument that specifies the size in bytes of the write.
 *                    This can be used to target specific elements of a structure or array.
 *
 * This function takes as argument the address of a signal or transfer register variable and indicates
 * that the signal or transfer register is being written asynchronously or implicitly by the hardware.
 * It is necessary to use this intrinsic to mark all definitions and use points of signal/transfer registers
 * that are not directly visible to the compiler. They ensure that the compiler does correct lifetime analysis
 * and hence correct register allocation to such variables. This intrinsic must be used, for example, when
 * the RX_THREAD_FREELIST CSR is written with the register number allocated to a variable, when a signal
 * is requested by writing into a CSR, or a signal is tested by doing a ctx_arb with a signal mask
 * generated with __signals(). See "Things to Remember When Writing Code" in the
 * <em>Netronome Network Flow C Compiler User's Guide</em> for a more complete explanation with examples.
 */
void __implicit_write(void *sig_or_xfer, ...);

/** Indicate that the given variable should become undefined after this program point and its register(s) can be released.
 *
 * @param sig_or_xfer   Pointer to signal or transfer register variables
 * @param ...           Optional argument to specify the size of the area in bytes to be marked undefined
 *
 * This function takes as an argument the address of a register variable, and indicates to the
 * compiler that the variable can be considered undefined until the next time it is written to,
 * even if the variable is read. Undefined variables do not require registers. __implicit_undef() and
 * __implicit_write() are similar in that they can be used to prevent the compiler from storing
 * a prior value of the variable. Unlike __implicit_write(), however, __implicit_undef() will
 * not cause the compiler to reserve registers for the variable after the call.
 *
 *<b>Example:</b>
 *
 * @code
 * while (1) {
 *   __implicit_undef(&x);
 *   ... /// Other code
 *   if (!error) {
 *      x = 1;
 * }
 * sram_write(&x,...);
 *    }
 * @endcode
 *
 * In this example the __implicit_undef() will guarantee that registers will not be reserved for "x" in the area marked
 * "Other code". Without it, the compiler has to assume that the value of "x" from a previous iteration of the loop
 * might be used in the current iteration, since "error" might be true. Registers would then have to be reserved for "x"
 * throughout the entire loop. With the __implicit_undef() call, the compiler will see that "x" starts with an undefined
 * value in every loop iteration, and the previous value will not be needed. __implicit_write() could also be used, but
 * it would have to be placed directly before the "if (!error)" statement, since it is equivalent to writing a new value
 * to "x" which has to be preserved by the compiler in a register. __implicit_undef(), in contrast, "overwrites" any
 * previous value of the variable but does not "write" a new value.
 *
 */
void __implicit_undef(void *sig_or_xfer, ...);

/** Take the address of a signal variable or transfer register variable and binds it to a physical register number.
 *
 * @param sig_or_reg    Address of a signal variable or transfer register variable
 * @param reg_num       Physical register number to bind variable to
 *
 * This function takes the address of a signal variable or register variable, and binds it to a physical register
 * number. If the address of a structure or array is passed, the first element of the structure or array will be
 * assigned the physical register number, and every successive element will be assigned a consecutive register number.
 */
void __assign_relative_register(void *sig_or_reg, int reg_num);

/** Mark the beginning of a "no-spill" program region, where the compiler attempts to keep all the used variables
 * in registers unless they have been explicitly allocated to memory or have had their address taken.
 *
 * This is done at the expense of other program regions, which may incur extra spills. If the compiler cannot
 * allocate all the variables to registers, compilation will halt with an error message.
 */
void __no_spill_begin(void);

/** Mark the end of a "no-spill" program region.
 *
 * @see __no_spill_begin()
 */
void __no_spill_end(void);

/** Mark the start of a no swap region.
 *
 * Create a region where the compiler will not generate any instructions that will incur a context swap.
 */
void __no_swap_begin(void);

/** Mark the end of a no swap region.
 *
 * End of a no swap region. @see __no_swap_begin()
 */
void __no_swap_end(void);

/** @cond */
void __lmpt_reserve(void);
/** @endcond */

/**
 * @}
 */


/** @addtogroup csr Control and Status Register Access Intrinsics
 * @{
 */

/** This enumeration specifies the CSRs used in local_csr_read and
 * local_csr_write functions.
 */
typedef enum
{
    local_csr_ustore_address                = 0x000,    /**< Used to load programs into the Control Store.   */
    local_csr_ustore_data_lower             = 0x001,    /**< Control Store Data - lower.   */
    local_csr_ustore_data_upper             = 0x002,    /**< Control Store Data - upper.   */
    local_csr_ustore_error_status           = 0x003,    /**< ECC errors during Control Store reads.   */
    local_csr_alu_out                       = 0x004,    /**< Debug to show state of ALU.  */
    local_csr_ctx_arb_cntl                  = 0x005,    /**< Context Arbiter Control - used by the context
                                                            arbiter and for debug.
                                                        */
    local_csr_ctx_enables                   = 0x006,    /**< Context Enables - used by the context arbiter
                                                            and for debug.
                                                        */
    local_csr_cc_enable                     = 0x007,    /**< Condition Code Enable.   */
    local_csr_csr_ctx_pointer               = 0x008,    /**< CSR Context Pointer.   */

    local_csr_pc_breakpoint_0               = 0x009,    /**< PC Breakpoint 1 - PCB system. */
    local_csr_pc_breakpoint_1               = 0x00a,    /**< PC Breakpoint 1 - PCB system. */
    local_csr_pc_breakpoint_status          = 0x00b,    /**< PC Breakpoint - Status register associated with the PCB system. */
    local_csr_lm_register_error_status      = 0x00c,    /**< Information about parity errors detected on Datapath Regs. */
    local_csr_lm_error_status               = 0x00d,    /**< Status on ECC errors recorded on Local Memory reads. */
    local_csr_lm_error_mask                 = 0x00e,    /**< Controls Error Injection bits into an LM data-path word. */

    local_csr_indirect_ctx_sts              = 0x010,    /**< Indirect Context Status Register.   */
    local_csr_active_ctx_sts                = 0x011,    /**< Active Context Status Register.  */

    local_csr_indirect_ctx_sig_events       = 0x012,    /**< Indirect Context Signal Events Register.  */
    local_csr_active_ctx_sig_events         = 0x013,    /**< Active Context Signal Events Register   */
    local_csr_indirect_ctx_wakeup_events    = 0x014,    /**< Indirect Context Wakeup Events Register.   */
    local_csr_active_ctx_wakeup_events      = 0x015,    /**< Active Context Wakeup Events Register.   */
    local_csr_indirect_ctx_future_count     = 0x016,    /**< Indirect Context Future Count Register.   */
    local_csr_active_ctx_future_count       = 0x017,    /**< Active Context Future Count Register.   */
    local_csr_byte_index                    = 0x01C,    /**< Byte Index Register.   */

    local_csr_t_index                       = 0x01D,    /**< Transfer Index Register.   */
    local_csr_indirect_future_count_signal  = 0x01E,    /**< Which signal to set when FUTURE_COUNT == TIMESTAMP.   */
    local_csr_active_future_count_signal    = 0x01F,    /**< Which signal to set when FUTURE_COUNT == TIMESTAMP.   */
    local_csr_nn_put                        = 0x020,    /**< Next Neighbor Put Register.   */
    local_csr_nn_get                        = 0x021,    /**< Next Neighbor Get Register.   */

    local_csr_indirect_lm_addr_0            = 0x018,    /**< Indirect Local Memory Address 0 Register.   */
    local_csr_active_lm_addr_0              = 0x019,    /**< Active Local Memory Address 0 Register.   */
    local_csr_indirect_lm_addr_1            = 0x01A,    /**< Indirect Local Memory Address 1 Register.   */
    local_csr_active_lm_addr_1              = 0x01B,    /**< Active Local Memory Address 1 Register.   */

    local_csr_indirect_lm_addr_2            = 0x024,    /**< Indirect Local Memory Address 2 Register.   */
    local_csr_active_lm_addr_2              = 0x025,    /**< Active Local Memory Address 2 Register.   */
    local_csr_indirect_lm_addr_3            = 0x026,    /**< Indirect Local Memory Address 3 Register.   */
    local_csr_active_lm_addr_3              = 0x027,    /**< Active Local Memory Address 3 Register.   */

    local_csr_indirect_lm_addr_0_byte_index = 0x038,    /**< Alias of IndLMAddr0 and ByteIndex.   */
    local_csr_active_lm_addr_0_byte_index   = 0x039,    /**< Alias of ActLMAddr0 and ByteIndex.   */
    local_csr_indirect_lm_addr_1_byte_index = 0x03A,    /**< Alias of IndLMAddr1 and ByteIndex.   */
    local_csr_active_lm_addr_1_byte_index   = 0x03B,    /**< Alias of ActLMAddr1 and ByteIndex.   */

    local_csr_indirect_lm_addr_2_byte_index = 0x028,    /**< Alias of IndLMAddr2 and ByteIndex.   */
    local_csr_active_lm_addr_2_byte_index   = 0x029,    /**< Alias of ActLMAddr2 and ByteIndex.   */
    local_csr_indirect_lm_addr_3_byte_index = 0x02A,    /**< Alias of IndLMAddr3 and ByteIndex.   */
    local_csr_active_lm_addr_3_byte_index   = 0x02B,    /**< Alias of ActLMAddr3 and ByteIndex.   */

    local_csr_indirect_predicate_cc         = 0x02C,    /**< Indirect Predicate CC select. */

    local_csr_t_index_byte_index            = 0x03D,    /**< This register is used when Transfer registers
                                                            are accessed via indexed mode.
                                                        */

    local_csr_timestamp_low                 = 0x030,    /**< Timestamp is 64 bits. It counts up by one every
                                                            sixteen cycles.
                                                        */
    local_csr_timestamp_high                = 0x031,    /**< Timestamp is 64 bits. It counts up by one every
                                                            sixteen cycles.
                                                        */
    local_csr_next_neighbor_signal          = 0x040,    /**< Signal a Context in Next Neighbor.   */
    local_csr_prev_neighbor_signal          = 0x041,    /**< Signal a Context in Previous Neighbor.   */
    local_csr_same_me_signal                = 0x042,    /**< Signal another Context in same Microengine.   */
    local_csr_crc_remainder                 = 0x050,    /**< Result of the CRC operation after a crc instruction.   */
    local_csr_profile_count                 = 0x051,    /**< The profile count is used for code profiling
                                                            and tuning.
                                                        */
    local_csr_pseudo_random_number          = 0x052,    /**< Random number generator.   */
    local_csr_misc_control                  = 0x058,    /**< Miscellaneous Control Register.   */

    pc_breakpoint_0_mask                    = 0x059,    /**< Mask register associated with PC Breakpoint 0. */
    pc_breakpoint_1_mask                    = 0x05a,    /**< Mask register associated with PC Breakpoint 1. */

    local_csr_mailbox0                      = 0x05c,    /**< Mailbox Register 0.  */
    local_csr_mailbox1                      = 0x05d,    /**< Mailbox Register 1.   */
    local_csr_mailbox2                      = 0x05e,    /**< Mailbox Register 2.   */
    local_csr_mailbox3                      = 0x05f,    /**< Mailbox Register 3.   */
    local_csr_mailbox_0                     = 0x05c,    /**< Alias of Mailbox0.    */
    local_csr_mailbox_1                     = 0x05d,    /**< Alias of Mailbox1.   */
    local_csr_mailbox_2                     = 0x05e,    /**< Alias of Mailbox2.   */
    local_csr_mailbox_3                     = 0x05f,    /**< Alias of Mailbox3.   */

    local_csr_cmd_indirect_ref0             = 0x064,    /**< Indirect reference to control register 0 */
    local_csr_cmd_indirect_ref1             = 0x065,    /**< Indirect reference to control register 1 */

    local_csr_cmd_indirect_ref_0            = 0x064,    /**< Alias of local_csr_cmd_indirect_ref0 */
    local_csr_cmd_indirect_ref_1            = 0x065,    /**< Alias of local_csr_cmd_indirect_ref1 */

    local_csr_reserved                      = 0x0FF     /**< Reserved  */
} local_csr_t;



/* CSR definitions */
#if __BIGENDIAN
/**  Active_CTX_Status CSR format.
 *
 * The Active_CTX_Status CSR maintains the context number of the Context currently executing.
 * Each Microengine supports eight contexts (0 through 7).
 */
typedef union
{
    struct
    {
        unsigned int AB0: 1;            /**< If set, the Microengine has a Context in the Executing state.
                                        *   If clear, no Context is in Executing State.
                                        */
        unsigned int ISLAND_ID: 6;      /**< Island number where the ME is instantiated. */
        unsigned int ATXPC: 17;         /**< Program count of the Executing Context. Only valid if AB0 is a 1.
                                        *   Valid values are 0 to 131071.
                                        *   This field provides a snapshot value of the PC. This value is
                                        *   used for tracking/code profiling purposes. When issued as
                                        *   a local_csr_read from the Microengine, the PC value may
                                        *   not be the exact PC value of the local_csr_rd instruction.
                                        */
        unsigned int RESERVED: 1;       /**< Reserved. */
        unsigned int ME_ID: 4;          /**< The unique ME number which identifies it within the
                                        *   cluster where it happens to be instantiated.
                                        */
        unsigned int ACNO: 3;           /**< The number of the Executing context. Only valid if AB0 bit is a 1.*/
    };
    unsigned int value;                 /**< Accessor to all bits simultaneously. */
} ACTIVE_CTX_STS_t;

#else
/* __LITTLEENDIAN */

typedef union
{
    struct
    {
        unsigned int ACNO: 3;
        unsigned int ME_ID: 4;
        unsigned int RESERVED: 1;
        unsigned int ATXPC: 17;
        unsigned int ISLAND_ID: 6;
        unsigned int AB0: 1;
    };
    unsigned int value;
} ACTIVE_CTX_STS_t;

#endif /* __BIGENDIAN */


/**
 * @}
 */

/** @addtogroup crc CRC Intrinsics
 * @{
 */

/** CRC bytes specifier.
 *
 * The bytes_specifier_t enumeration is used as an argument to the CRC functions and specifies one or more contiguous
 * bytes within a 32-bit word of big-endian or little-endian data. For example, the bytes_0_3 item in this enumeration
 * refers to bytes 0 through 3. When using the big-endian CRC functions, byte 0 refers to the most significant byte
 * and byte 3 refers to the least significant byte. When using the little-endian CRC functions, byte 0 refers to the least
 * significant byte and byte 3 refers to the most significant byte. This enumeration type specifies the bytes to be used
 * with CRC operations.
 */
typedef enum
{
    bytes_0_3,                  /**< BE: 0, 1, 2, 3      LE: 3, 2, 1, 0. */
    bytes_0_2,                  /**< BE: 0, 1, 2         LE:    2, 1, 0. */
    bytes_0_1,                  /**< BE: 0, 1            LE:       1, 0. */
    byte_0,                     /**< BE: 0               LE:          0. */
    bytes_1_3,                  /**< BE:    1, 2, 3      LE: 3, 2, 1   . */
    bytes_2_3,                  /**< BE:       2, 3      LE: 3, 2      . */
    byte_3                      /**< BE:          3      LE: 3         . */
} bytes_specifier_t;

/** CRC 5 computation in Big-endian format.
 *
 * @param data      Data on which to perform the CRC 5 computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a CRC-5 computation on specified bytes of the data argument that are
 * assumed to be in Big-endian format and return the unmodified value of data.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
__intrinsic
unsigned int crc_5_be(
    unsigned int data,
    bytes_specifier_t bspec
);

/** CRC 5 computation in Little-endian format.
 *
 * @param data      Data on which to perform the CRC 5 computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a CRC-5 computation on specified bytes of the data argument that are
 * assumed to be in Little-endian format and return the unmodified value of data.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
__intrinsic
unsigned int crc_5_le(
    unsigned int data,
    bytes_specifier_t bspec
);

/** CRC 10 computation in Big-endian format.
 *
 * @param data      Data on which to perform the CRC 10 computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a CRC-10 computation on specified bytes of the data argument that are
 * assumed to be in Big-endian format and return the unmodified value of data.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
__intrinsic
unsigned int crc_10_be(
    unsigned int data,
    bytes_specifier_t bspec
);

/** CRC 10 computation in Little-endian format.
 *
 * @param data      Data on which to perform the CRC 10 computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a CRC-10 computation on specified bytes of the data argument that are
 * assumed to be in Little-endian format and return the unmodified value of data.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
__intrinsic
unsigned int crc_10_le(
    unsigned int data,
    bytes_specifier_t bspec
);

/** 16-bit CCITT CRC computation in Big-endian format.
 *
 * @param data      Data on which to perform the 16-bit CCITT CRC computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a 16-bit CCITT CRC computation on specified bytes in the data argument that
 * is assumed to be in Big-endian format and return the unmodified value of data.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
__intrinsic
unsigned int crc_16_be(
    unsigned int data,
    bytes_specifier_t bspec
);

/** 16-bit CCITT CRC computation in Little-endian format.
 *
 * @param data      Data on which to perform the 16-bit CCITT CRC computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a 16-bit CCITT CRC computation on specified bytes in the data argument that
 * is assumed to be in Little-endian format and return the unmodified value of data.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
__intrinsic
unsigned int crc_16_le(
    unsigned int data,
    bytes_specifier_t bspec
);

/** 32-bit iSCSI CRC computation in Big-endian format.
 *
 * @param data      Data on which to perform the 32-bit iSCSI CRC computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a CRC-32 computation on specified bytes in the data argument that is
 * assumed to be in Big-endian format and return the unmodified value of data.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
__intrinsic
unsigned int crc_32_be(
    unsigned int data,
    bytes_specifier_t bspec
);

/** 32-bit iSCSI CRC computation in Little-endian format.
 *
 * @param data      Data on which to perform the 32-bit iSCSI CRC computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a CRC-32 computation on specified bytes in the data argument that is
 * assumed to be in Little-endian format and return the unmodified value of data.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
__intrinsic
unsigned int crc_32_le(
    unsigned int data,
    bytes_specifier_t bspec
);

/** 16-bit CCITT CRC computation in Big-endian format.
 *
 * @param data      Data on which to perform the 16-bit CCITT CRC computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a 16-bit CCITT CRC computation on specified bytes in the data argument that
 * is assumed to be in Big-endian format and return the unmodified value of data.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
__intrinsic
unsigned int crc_ccitt_be(
    unsigned int data,
    bytes_specifier_t bspec
);

/** 16-bit CCITT CRC computation in Little-endian format.
 *
 * @param data      Data on which to perform the 16-bit CCITT CRC computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a 16-bit CCITT CRC computation on specified bytes in the data argument that
 * is assumed to be in Little-endian format and return the unmodified value of data.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
__intrinsic
unsigned int crc_ccitt_le(
    unsigned int data,
    bytes_specifier_t bspec
);

/** 32-bit iSCSI CRC computation in Big-endian format.
 *
 * @param data      Data on which to perform the 32-bit iSCSI CRC computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a 32-bit iSCSI CRC computation on specified bytes in the data argument that
 * is assumed to be in Big-endian format and return the unmodified value of data.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
__intrinsic
unsigned int crc_iscsi_be(
    unsigned int data,
    bytes_specifier_t bspec
);

/** 32-bit iSCSI CRC computation in Little-endian format.
 *
 * @param data      Data on which to perform the 32-bit iSCSI CRC computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a 32-bit iSCSI CRC computation on specified bytes in the data argument that
 * is assumed to be in Little-endian format and return the unmodified value of data.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
__intrinsic
unsigned int crc_iscsi_le(
    unsigned int data,
    bytes_specifier_t bspec
);


/* crc_none little-endian */

/** @cond */
unsigned int crc_none_le(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
);

/* crc_none big-endian */

unsigned int crc_none_be(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
);
/** @endcond */

/** CRC 5 computation and bit swap in Big-endian format.
 *
 * @param data      Data on which to perform the CRC 5 computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a CRC-5 computation on specified bytes of the data argument that are
 * assumed to be in Big-endian format and return the unmodified value of data.
 * The bits in each byte are swapped before the computation begins.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
unsigned int crc_5_be_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
);

/** CRC 5 computation and bit swap in Little-endian format.
 *
 * @param data      Data on which to perform the CRC 5 computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a CRC-5 computation on specified bytes of the data argument that are
 * assumed to be in Little-endian format and return the unmodified value of data.
 * The bits in each byte are swapped before the computation begins.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
unsigned int crc_5_le_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
);

/** CRC 10 computation and bit swap in Big-endian format.
 *
 * @param data      Data on which to perform the CRC 10 computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a CRC-10 computation on specified bytes of the data argument that are
 * assumed to be in Big-endian format and return the unmodified value of data.
 * The bits in each byte are swapped before the computation begins.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
unsigned int crc_10_be_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
);

/** CRC 10 computation and bit swap in Little-endian format.
 *
 * @param data      Data on which to perform the CRC 10 computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a CRC-10 computation on specified bytes of the data argument that are
 * assumed to be in Little-endian format and return the unmodified value of data.
 * The bits in each byte are swapped before the computation begins.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
unsigned int crc_10_le_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
);

/** 16-bit CCITT CRC computation and bit swap in Big-endian format.
 *
 * @param data      Data on which to perform the 16-bit CCITT CRC computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a 16-bit CCITT CRC computation on specified bytes of the data argument that are
 * assumed to be in Big-endian format and return the unmodified value of data.
 * The bits in each byte are swapped before the computation begins.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
unsigned int crc_16_be_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
);

/** 16-bit CCITT CRC computation and bit swap in Little-endian format.
 *
 * @param data      Data on which to perform the 16-bit CCITT CRC computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a 16-bit CCITT CRC computation on specified bytes of the data argument that are
 * assumed to be in Little-endian format and return the unmodified value of data.
 * The bits in each byte are swapped before the computation begins.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
unsigned int crc_16_le_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
);

/** 32-bit iSCSI CRC computation and bit swap in Big-endian format.
 *
 * @param data      Data on which to perform the 32-bit iSCSI CRC computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a 32-bit iSCSI CRC computation on specified bytes of the data argument that are
 * assumed to be in Big-endian format and return the unmodified value of data.
 * The bits in each byte are swapped before the computation begins.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
unsigned int crc_32_be_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
);

/** 32-bit iSCSI CRC computation and bit swap in Little-endian format.
 *
 * @param data      Data on which to perform the 32-bit iSCSI CRC computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a 32-bit iSCSI CRC computation on specified bytes of the data argument that are
 * assumed to be in Little-endian format and return the unmodified value of data.
 * The bits in each byte are swapped before the computation begins.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
unsigned int crc_32_le_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
);

/** 16-bit CCITT CRC computation and bit swap in Big-endian format.
 *
 * @param data      Data on which to perform the 16-bit CCITT CRC computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a 16-bit CCITT CRC computation on specified bytes of the data argument that are
 * assumed to be in Big-endian format and return the unmodified value of data.
 * The bits in each byte are swapped before the computation begins.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
unsigned int crc_ccitt_be_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
);

/** 16-bit CCITT CRC computation and bit swap in Little-endian format.
 *
 * @param data      Data on which to perform the 16-bit CCITT CRC computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a 16-bit CCITT CRC computation on specified bytes of the data argument that are
 * assumed to be in Little-endian format and return the unmodified value of data.
 * The bits in each byte are swapped before the computation begins.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
unsigned int crc_ccitt_le_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
);

/** 32-bit iSCSI CRC computation and bit swap in Big-endian format.
 *
 * @param data      Data on which to perform the 32-bit iSCSI CRC computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a 32-bit iSCSI CRC computation on specified bytes of the data argument that are
 * assumed to be in Big-endian format and return the unmodified value of data.
 * The bits in each byte are swapped before the computation begins.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
unsigned int crc_iscsi_be_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
);

/** 32-bit iSCSI CRC computation and bit swap in Little-endian format.
 *
 * @param data      Data on which to perform the 32-bit iSCSI CRC computation
 * @param bspec     Specified bytes in the data argument on which to perform the computation
 *
 * Perform a 32-bit iSCSI CRC computation on specified bytes of the data argument that are
 * assumed to be in Little-endian format and return the unmodified value of data.
 * The bits in each byte are swapped before the computation begins.
 *
 * crc_write() can be used to initialize the CRC value and the result can be obtained from crc_read().
 * @see crc_read() and crc_write()
 */
unsigned int crc_iscsi_le_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
);

/* crc_none little-endian, bit_swap */
/** @cond */
unsigned int crc_none_le_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
);

/* crc_none big-endian, bit_swap */

unsigned int crc_none_be_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
);
/** @endcond */

/** Read CRC remainder accumulated so far.
 *
 */
unsigned int crc_read(void);

/** Write the CRC remainder.
 *
 * @param residue   Value to initialize the CRC remainder
 *
 */
void crc_write(
    unsigned int residue
);

/**
 * @}
 */

/**
 * @addtogroup misc Miscellaneous Intrinsics
 * @{
 */

/** @name Byte align intrinsics
 * @{
 */

/** Byte align block in Big-endian format.
 *
 * @param n_byte_align_oper Number of byte_align operations to perform on dest and src
 * @param dest              Address that stores the results of the alignment shift
 * @param src               Address that contains the pair of 32-bit elements to shift
 * @param shift_cnt         Number of bytes to shift
 *
 * This function sets local_csr BYTE_INDEX to shift_cnt, then performs n_byte_align_oper times
 * of consecutive byte_align_le operations on a pair of 32-bit elements in dest and src. Arguments
 * dest and src are addresses of Xfer/GPR 32-bit variables (or aggregates of 32-bit elements) that
 * must be enregisterized.
 *
 */
void byte_align_block_be(
    unsigned int n_byte_align_oper,
    void *dest,
    void *src,
    unsigned shift_cnt
);

/** Byte align block in Little-endian format.
 *
 * @param n_byte_align_oper Number of byte_align operations to perform on dest and src
 * @param dest              Address that stores the results of the alignment shift
 * @param src               Address that contains the pair of 32-bit elements to shift
 * @param shift_cnt         Number of bytes to shift
 *
 * This function sets local_csr BYTE_INDEX to shift_cnt, then performs n_byte_align_oper times
 * of consecutive byte_align_le operations on a pair of 32-bit elements in dest and src. Arguments
 * dest and src are addresses of Xfer/GPR 32-bit variables (or aggregates of 32-bit elements) that
 * must be enregisterized.
 *
 */
void byte_align_block_le(
    unsigned int n_byte_align_oper,
    void *dest,
    void *src,
    unsigned shift_cnt
);

/**
 * @}
 */

/** @name Other intrinsics
 * @{
 */

/** Halt the ME
 */
void halt();


/** Find the first (least significant) bit set in data.
 *
 * @param data  Data to examine
 *
 * This function finds the first (least significant) bit set in data and returns its bit position.
 * If there are no bits set (i.e., the data argument is 0) then the return value is undefined.
 * Otherwise, the return value is in the range 0 through 31.
 *
 */
unsigned int ffs(
    unsigned int data
);

/** Pop the number of "1" bits.
 *
 * @param data  Value on which to perform the operation
 *
 * This function returns the number of "1" bits in the given value "data".
 *
 */
unsigned int pop_count(
    unsigned int data
);

/** Swap bytes in a long word.
 *
 *  @param lw Long word to swap bytes in
 */
unsigned int bswap(unsigned int lw);

/** Swap bits in each byte of a long word.
 *
 * @param lw Long word where bits in bytes are swapped
 */
unsigned int bitswap(unsigned int lw);

/* ToDo: load field */

/* ToDo: load field with clear */

/**
 * @}
 */

/** @name CAM intrinsics
 * @{
 */

#if __BIGENDIAN

/** This structure is used to capture the results of a CAM lookup.
 *
 * @see cam_lookup(), cam_read_state().
 */
typedef union
{
    struct
    {
        unsigned int zeros1         : 20;   /**< All zeros.                             */
        unsigned int state          : 4;    /**< CAM entry state.                       */
        unsigned int hit            : 1;    /**< hit (1) or miss (0).                   */
        unsigned int entry_num      : 4;    /**< CAM entry number.                      */
        unsigned int zeros2         : 3;    /**< All zeros.                             */
    };
    unsigned int value;                     /**< Accessor to all fields simultaneously  */
} cam_lookup_t;
#else
/* __LITTLEENDIAN */
typedef union
{
    struct
    {
        unsigned int zeros2         : 3;    /* all zeros */

        unsigned int entry_num      : 4;    /* CAM entry number */
        unsigned int hit            : 1;    /* hit (1) or miss (0) */
        unsigned int state          : 4;    /* CAM entry state */
        unsigned int zeros1         : 20;   /* all zeros */
    };
    unsigned int value;
} cam_lookup_t;

#endif /* __BIGENDIAN */

/** Write an entry in the CAM.
 *
 * @param entry_num CAM entry number to write
 * @param tag       Value to set for this CAM entry
 * @param cam_state State to set for this CAM entry
 *
 * Writes an entry in the CAM specified by the argument index with the value
 * specified by tag, and sets the state to the value specified in the argument state.
 * Argument state must be a constant literal specified directly in the intrinsics
 * argument list. Otherwise, the compiler may have to generate runtime checks for the possible 16
 * values, since the microcode only accepts a constant literal for the state.
 *
 */
void cam_write(
    unsigned int entry_num,             /* CAM entry number */
    unsigned int tag,                   /* tag to write */
    unsigned int cam_state              /* state to write */
);

/** Perform a CAM lookup.
 *
 * @param tag       The value to lookup in the CAM
 *
 * Perform a CAM lookup and return the hit/miss status, state, and entry number as
 * bitfields in the return value. In the event of a miss, the entry value is the
 * LRU (least recently used) entry (which is the suggested entry to replace) and state
 * bits are 0. On a CAM hit, this function has the side effect of marking the CAM entry as
 * MRU (most recently used).
 *
 */
cam_lookup_t cam_lookup(
    unsigned int tag                    /* tag to lookup */
);

/** Set the state for the entry in the CAM.
 *
 * @param entry_num       CAM entry whose state is set
 * @param cam_state       State to set for the CAM entry
 *
 * Set the state for the entry in the CAM specified by the entry_num argument to the value specified
 * in the argument state. Argument state must be a constant literal specified directly in the
 * intrinsics argument list. Otherwise, the compiler may have to generate runtime checks for the
 * possible 16 values, since the microcode only accepts a constant literal for the state.
 *
 */
void cam_write_state(
    unsigned int entry_num,             /* CAM entry number */
    unsigned int cam_state              /* state to write */
);

/** Read the tag associated with the CAM entry.
 *
 * @param entry_num       CAM entry whose tag is returned
 *
 * Read out the tag associated with the CAM entry specified by the entry_num argument.
 *
 */
unsigned int cam_read_tag(
    unsigned int entry_num              /* CAM entry number */
);

/** Read the state associated with the CAM entry.
 *
 * @param entry_num       CAM entry whose state is returned
 *
 * Read out the state associated with the CAM entry specified by the entry_num
 * argument and returns it in the state bitfield of the return value. All other
 * fields of the return value structure are set to 0.
 *
 */
cam_lookup_t cam_read_state(
    unsigned int entry_num              /* CAM entry number */
);

/** Clear all entries in the CAM.
 *
 */
void cam_clear(void);

/**
 * @}
 */

/** @name Multiplication intrinsics
 * @{
 */

/** Multiply 24-bit by 8-bit.
 *
 * @param x     24-bit int to multiply
 * @param y     8-bit int to multiply
 *
 * Returns the result of 24-bit x multiplied by 8-bit y.
 */
unsigned int multiply_24x8(
    unsigned int x,
    unsigned int y
);

/** Multiply 16-bit by 16-bit.
 *
 * @param x     16-bit int to multiply
 * @param y     16-bit int to multiply
 *
 * Returns the result of 16-bit x multiplied by 16-bit y.
 */
unsigned int multiply_16x16(
    unsigned int x,
    unsigned int y
);

/** Multiply 32-bit by 32-bit.
 *
 * @param x     32-bit int to multiply
 * @param y     32-bit int to multiply
 *
 * Returns the lower 32-bit result of 32-bit x multiplied by 32-bit y.
 *
 */
unsigned int multiply_32x32_lo(
    unsigned int x,
    unsigned int y
);

/** Multiply 32-bit by 32-bit.
 *
 * @param x     32-bit int to multiply
 * @param y     32-bit int to multiply
 *
 * Returns the higher 32-bit result of 32-bit x multiplied by 32-bit y.
 *
 */
unsigned int multiply_32x32_hi(
    unsigned int x,
    unsigned int y
);

/** Multiply 32-bit by 32-bit.
 *
 * @param x     32-bit int to multiply
 * @param y     32-bit int to multiply
 *
 * Returns the higher 32-bit result of 32-bit x multiplied by 32-bit y.
 */
unsigned long long multiply_32x32(
    unsigned int x,
    unsigned int y
);

/**
 * @}
 */

/** @name Timer intrinsics
 * @{
 */

/** Sets the timestamp for local CSR enum.
 *
 * @param timestamp     Timestamp to set
 *
 * Sets both the local_csr_timestamp_low and local_csr_timestamp_high fields of the local_csr_t enum.
 */
void __set_timestamp(__int64 timestamp);

/** Start timestamp.
 *
 * This function uses local_csr_timestamp_low and timestamp_high to measure time elapse in 16-cycle intervals
 * between start and stop. The __timestamp_start() function returns a handle that is used by the __timestamp_stop()
 * function.
 *
 * @note This function returns a handle that is used by the __timestamp_stop() function.
 *
 */
__int64 __timestamp_start(void);

/** Stop timestamp.
 *
 * @param handle    Timestamp handle returned by the __timestamp_start() function
 *
 * This function returns the time elapse in 16-cycle intervals between start and stop.
 *
 */
__int64 __timestamp_stop(__int64 handle);

/** Sleep for a number of cycles.
 *
 * @param cycles Approximate number of cycles to sleep, resolution is 16 cycles and should be less than (1 << 20).
 *
 * @note The ME timers must be enabled before using the sleep function.
 *
 */
void __sleep(unsigned int cycles);

/**
 * @}
 */

/** Sets the local_csr_profile_count field of the local_csr_t enum.
 *
 * @param profile_count Profile count to set.
 */
void __set_profile_count(unsigned int profile_count);


/** Uses local_csr_profile_count to measure time elapse in cycle between start and stop.
 *
 * The __profile_count_start() function returns a handle that is used by the __profile_count_stop()
 * function.
 *
 * @see __profile_count_stop
 */
unsigned int __profile_count_start(void);

/** This function use local_csr_profile_count to measure time elapse in cycle between start and stop.
 *
 * @param handle Handle returned by the __profile_count_start() function that is passed to the __profile_count_stop() function.
 *
 * The __profile_count_start() function returns a handle that is used by the __profile_count_stop()
 * function.
 *
 * @see __profile_count_start
 *
 */
unsigned int __profile_count_stop(unsigned int handle);

/** @cond */
/* Simulator timer */
void __timer_start(                 /* Start timer #id at running context                               */
    int id                          /* timer ID, var or const in 0..255, or -1 which means all          */
);

void __timer_stop(                  /* Stop timer #id at running context                                */
    int id                          /* timer ID, var or const in 0..255, or -1 which means all          */
);

void __timer_strobe(                /* Increment timer #id by 1 (used as counter) at running context    */
    int id                          /* timer ID, var or const in 0..255, or -1 which means all          */
);

void __timer_reset(                 /* Reset timer #id at running context                               */
    int id                          /* timer ID, var or const in 0..255, or -1 which means all          */
);

void __timer_report(                /* Report timer #id at running context                              */
    int id                          /* timer ID, var or const in 0..255, or -1 which means all          */
);

void __timer_report_all_ctx(        /* Report timer #id for all contexts                                */
    int id                          /* timer ID, var or const in 0..255, or -1 which means all          */
);
/** @endcond */



/** @name Miscellaneous intrinsics
 * @{
 */


/** Get the current island/cluster id of the current Microengine.
 *  Also available for use is LoadTimeConstant("__island");
 *
 * @return The island/cluster id of the currently executing microengine
 *
 * @see __LoadTimeConstant
 */
unsigned int __island(void);


/** Get the current Microengine number and island id.
 *  Also available for use LoadTimeConstant("__meid");
 *
 * @return The value of the currently executing microengine.
 *         (island_id << 4) | (me_num + 4)
 *
 * @see __LoadTimeConstant
 */
unsigned int __ME(void);



/** Get the current context.
 * @return The value of the currently executing context in the range of 0 through 7.
 */
unsigned int __ctx(void);


/** Get the number of contexts compiled.
 *  This is specified by the nfcc option "-Qnctx=<1, 2, 3, 4, 5, 6, 7, 8>"
 *
 *  @return The number of contexts compiled to run, the range is 1 to 8.
 */
unsigned int __n_ctx(void);


/** Get the context mode.
 *  This is specified by the nfcc option "-Qnctx_mode=<4, 8>"
 *
 * @return Depending on context mode, either 4 or 8.
 */
unsigned int __nctx_mode(void);

/**
 * @}
 */

/**
 * @}
 */

/** @addtogroup signal Synchronization Intrinsics
 *  @{
 */

/** Wait for signal.
 * This is a C macro that serves as a wrapper around the function call ctx_wait(voluntary). The
 * ctx_wait(voluntary) function call voluntarily swaps out the current context. The context is
 * ready to run again immediately.
 */
#define ctx_swap()  ctx_wait(voluntary)

/** Wait for signal.
 *
 * @param sig One of kill, voluntary or bpt.
 *
 * This function swaps out the current context and waits for the specified signal, bpt,
 * voluntary, kill, or no_load (where the signal mask is specified earlier in one of the local csr
 * CTX_WAKEUP_EVENTS). Please use the __wait_for_all(), __wait_for_all_single(), __wait_for_any(), __wait_for_any_single() or
 * signal_test() intrinsics to wait for signal variables.
 */
void ctx_wait(signal_t sig);

/** Test if a signal is set.
 *
 * This function tests whether or not a signal is set. Signal is a user signal variable.
 *
 * @param   sig_ptr Pointer to the signal
 * @return  When it is set a value of 1 is returned otherwise, 0 is returned.
 *
 * @note    If the signal is set, it gets cleared as a side effect of testing it.
 */
int signal_test(volatile SIGNAL *sig_ptr);

/**
 * @}
 */

/**
 * @addtogroup misc Miscellaneous Intrinsics
 * @{

/** Test the bit_pos in data word and return a 1 if set or 0 if clear.
 *
 * @param data      Data word to test
 * @param bit_pos   Bit position in data to test
 */
int bit_test(
    unsigned int data,
    unsigned int bit_pos
);

/** This enumeration defines the state values that can be tested
 * with the inp_state_test() intrinsic.
 */
typedef enum
{
    inp_state_nn_empty          = 0x0, /**< NN_Ring in the neighbor microengine is empty.       */
    inp_state_nn_full           = 0x1, /**< NN_Ring in the neighbor microengine is full.        */

    inp_state_ctm_ring0_status  = 0x2, /**< Indicates if CTM Ring 0 is full or empty.
                                            The Full Flag can be configured as an Empty Flag by
                                            the RING_STATUS_FLAG bit in the CTM_RING_BASE_0 register.
                                        */
    inp_state_ctm_ring1_status  = 0x3, /**< Indicates if CTM Ring 1 is full or empty.
                                            The Full Flag can be configured as an Empty Flag by
                                            the RING_STATUS_FLAG bit in the CTMRING_BASE_1 register.
                                        */
    inp_state_ctm_ring2_status  = 0x4, /**< Indicates if CTM Ring 2 is full or empty.
                                            The Full Flag can be configured as an Empty Flag by
                                            the RING_STATUS_FLAG bit in the CTM_RING_BASE_2 register.
                                        */
    inp_state_ctm_ring3_status  = 0x5, /**< Indicates if CTM Ring 3 is full or empty.
                                            The Full Flag can be configured as an Empty Flag by
                                            the RING_STATUS_FLAG bit in the CTM_RING_BASE_3 register.
                                        */
    inp_state_ctm_ring4_status  = 0x6, /**< Indicates if CTM Ring 4 is full or empty.
                                            The Full Flag can be configured as an Empty Flag by
                                            the RING_STATUS_FLAG bit in the CTM_RING_BASE_4 register.
                                        */
    inp_state_ctm_ring5_status  = 0x7, /**< Indicates if CTM Ring 5 is full or empty.
                                            The Full Flag can be configured as an Empty Flag by
                                            the RING_STATUS_FLAG bit in the CTM_RING_BASE_5 register.
                                        */
    inp_state_ctm_ring6_status  = 0x8, /**< Indicates if CTM Ring 6 is full or empty.
                                            The Full Flag can be configured as an Empty Flag by
                                            the RING_STATUS_FLAG bit in the CTM_RING_BASE_6 register.
                                        */
    inp_state_ctm_ring7_status  = 0x9, /**< Indicates if CTM Ring 7 is full or empty.
                                            The Full Flag can be configured as an Empty Flag by
                                            the RING_STATUS_FLAG bit in the CTM_RING_BASE_7 register.
                                        */
    inp_state_ctm_ring8_status  = 0xA, /**< Indicates if CTM Ring 8 is full or empty.
                                            The Full Flag can be configured as an Empty Flag by
                                            the RING_STATUS_FLAG bit in the CTM_RING_BASE_8 register.
                                        */
    inp_state_ctm_ring9_status  = 0xB, /**< Indicates if CTM Ring 9 is full or empty.
                                            The Full Flag can be configured as an Empty Flag by
                                            the RING_STATUS_FLAG bit in the CTM_RING_BASE_9 register.
                                        */
    inp_state_ctm_ring10_status = 0xC, /**< Indicates if CTM Ring 10 is full or empty.
                                            The Full Flag can be configured as an Empty Flag by
                                            the RING_STATUS_FLAG bit in the CTM_RING_BASE_10 register.
                                        */
    inp_state_ctm_ring11_status = 0xD, /**< Indicates if CTM Ring 11 is full or empty.
                                            The Full Flag can be configured as an Empty Flag by
                                            the RING_STATUS_FLAG bit in the CTM_RING_BASE_11 register.
                                        */
    inp_state_ctm_ring12_status = 0xE, /**< Indicates if CTM Ring 12 is full or empty.
                                            The Full Flag can be configured as an Empty Flag by
                                            the RING_STATUS_FLAG bit in the CTM_RING_BASE_12 register.
                                        */
    inp_state_ctm_ring13_status = 0xF, /**< Indicates if CTM Ring 13 is full or empty.
                                            The Full Flag can be configured as an Empty Flag by
                                            the RING_STATUS_FLAG bit in the CTM_RING_BASE_13 register.
                                        */
    inp_state_ctm_ring0_full    = inp_state_ctm_ring0_status,   /**< Indicates if CTM Ring 0 is full.
                                                                    This assumes CTM_Ring_Base_0[Ring_Status_Flag]
                                                                    is configured to set the flag when the ring is full. */
    inp_state_ctm_ring1_full    = inp_state_ctm_ring1_status,   /**< Indicates if CTM Ring 1 is full.
                                                                    This assumes CTM_Ring_Base_1[Ring_Status_Flag]
                                                                    is configured to set the flag when the ring is full. */
    inp_state_ctm_ring2_full    = inp_state_ctm_ring2_status,   /**< Indicates if CTM Ring 2 is full.
                                                                    This assumes CTM_Ring_Base_2[Ring_Status_Flag]
                                                                    is configured to set the flag when the ring is full. */
    inp_state_ctm_ring3_full    = inp_state_ctm_ring3_status,   /**< Indicates if CTM Ring 3 is full.
                                                                    This assumes CTM_Ring_Base_3[Ring_Status_Flag]
                                                                    is configured to set the flag when the ring is full. */
    inp_state_ctm_ring4_full    = inp_state_ctm_ring4_status,   /**< Indicates if CTM Ring 4 is full.
                                                                    This assumes CTM_Ring_Base_4[Ring_Status_Flag]
                                                                    is configured to set the flag when the ring is full. */
    inp_state_ctm_ring5_full    = inp_state_ctm_ring5_status,   /**< Indicates if CTM Ring 5 is full.
                                                                    This assumes CTM_Ring_Base_5[Ring_Status_Flag]
                                                                    is configured to set the flag when the ring is full. */
    inp_state_ctm_ring6_full    = inp_state_ctm_ring6_status,   /**< Indicates if CTM Ring 6 is full.
                                                                    This assumes CTM_Ring_Base_6[Ring_Status_Flag]
                                                                    is configured to set the flag when the ring is full. */
    inp_state_ctm_ring7_full    = inp_state_ctm_ring7_status,   /**< Indicates if CTM Ring 7 is full.
                                                                    This assumes CTM_Ring_Base_7[Ring_Status_Flag]
                                                                    is configured to set the flag when the ring is full. */
    inp_state_ctm_ring8_full    = inp_state_ctm_ring8_status,   /**< Indicates if CTM Ring 8 is full.
                                                                    This assumes CTM_Ring_Base_8[Ring_Status_Flag]
                                                                    is configured to set the flag when the ring is full. */
    inp_state_ctm_ring9_full    = inp_state_ctm_ring9_status,   /**< Indicates if CTM Ring 9 is full.
                                                                    This assumes CTM_Ring_Base_9[Ring_Status_Flag]
                                                                    is configured to set the flag when the ring is full. */
    inp_state_ctm_ring10_full   = inp_state_ctm_ring10_status,  /**< Indicates if CTM Ring 10 is full.
                                                                    This assumes CTM_Ring_Base_10[Ring_Status_Flag]
                                                                    is configured to set the flag when the ring is full. */
    inp_state_ctm_ring11_full   = inp_state_ctm_ring11_status,  /**< Indicates if CTM Ring 11 is full.
                                                                    This assumes CTM_Ring_Base_11[Ring_Status_Flag]
                                                                    is configured to set the flag when the ring is full. */
    inp_state_ctm_ring12_full   = inp_state_ctm_ring12_status,  /**< Indicates if CTM Ring 12 is full.
                                                                    This assumes Scratch_Ring_Base_12[Ring_Status_Flag]
                                                                    is configured to set the flag when the ring is full. */
    inp_state_ctm_ring13_full   = inp_state_ctm_ring13_status   /**< Indicates if CTM Ring 13 is full.
                                                                    This assumes CTM_Ring_Base_13[Ring_Status_Flag]
                                                                    is configured to set the flag when the ring is full. */
} inp_state_t;



/** Tests the value of the specified input state name.
 *
 * @param state State to test
 *
 * This function tests the value of the specified state name and returns a 1 if the state is set or 0 if clear.
 * The argument state must be a constant literal as required by the microcode assembler; otherwise,
 * the compiler generates a runtime check, if possible, with loss of performance.
 */
int inp_state_test(
    inp_state_t state
);

/** @name Next Neighbor intrinsics
 * @{
 */

/** Dequeue from next neighbor ring.
 *
 * @return Next neighbor ring
 *
 * This function returns the next neighbor ring indexed by NN_GET without post-incrementing NN_GET.
 *
 */
unsigned int nn_ring_dequeue(void);

/** Dequeue from and post-increment next neighbor ring.
 *
 * @return Next neighbor ring
 *
 * This function returns the next neighbor ring indexed by NN_GET, then post-increments NN_GET.
 *
 */
unsigned int nn_ring_dequeue_incr(void);

/** Enqueue to the next neighbor ring.
 *
 * @param val    Value to set next neighbor ring indexed by NN_PUT
 *
 * This function sets the next neighbor ring indexed by NN_PUT with val and post-increments NN_PUT.
 *
 */
void nn_ring_enqueue_incr(unsigned int val);
/** @}
 * @}
 */

/** @addtogroup signal Synchronization Intrinsics
 *  @{
 */

/** Signal the same Microengine, same context.
 *
 * @param sig_no    Signal number to raise
 * @param ctx       Context in which the signal is to be raised
 *
 * Raise the specified signal number in the specified context of the same Microengine.
 * The context "ctx" must be running on the same Microengine.
 *
 */
void signal_same_ME(
    unsigned int sig_no,
    unsigned int ctx
);

/** Signal the same Microengine, next context.
 *
 * @param sig_no    Signal number to raise
 *
 * Raise the specified signal number in the next context number of the same Microengine.
 *
 */
void signal_same_ME_next_ctx(
    unsigned int sig_no
);

/** Signal the previous Microengine.
 *
 * @param sig_no    Signal number to raise
 * @param ctx       Context in which to raise the signal
 *
 * Raise the specified signal number in the specified context of the previous Microengine.
 *
 */
void signal_prev_ME(
    unsigned int sig_no,
    unsigned int ctx
);

/** Signal the previous Microengine, same context.
 *
 * @param sig_no    Signal number to raise
 *
 * Raise the specified signal number in the same context number of the previous Microengine.
 *
 */
void signal_prev_ME_this_ctx(
    unsigned int sig_no
);

/** Signal the next Microengine.
 *
 * @param sig_no    Signal number to raise
 * @param ctx       Context in which to raise the signal
 *
 * Raise the specified signal number in the specified context of the next Microengine.
 *
 */
void signal_next_ME(
    unsigned int sig_no,
    unsigned int ctx
);

/** Signal the next Microengine, same context.
 *
 * @param sig_no    Signal number to raise
 *
 * Raise the specified signal number in the same context number of the next Microengine.
 *
 */
void signal_next_ME_this_ctx(
    unsigned int sig_no
);
/**
 * @}
 */

/**
 * @addtogroup misc Miscellaneous Intrinsics
 * @{
 */

/** Indicates that any pending write that writes out the data buffer can be considered as
 * having completed. The transfer registers allocated for the write can now be used for other
 * write operations.
 *
 * @param data Data buffer to write
 *
 * This intrinsic is called after an asynchronous memory write operation has been issued.
 * It indicates that all pending writes that require the given data buffer have completed.
 * The transfer registers allocated for the write can then be reused for other write operations.
 * Without a call to this intrinsic, the compiler will assume that transfer registers involved
 * in an asynchronous memory write can be reused immediately after the operation has issued,
 * which may cause invalid data to be written out to memory. See "Things to Remember When
 * Writing Code" in the <em>Netronome Network Flow C Compiler User's Guide</em> for
 * a more complete explanation with examples.
 *
 * @note Performs the same task as __implicit_read().
 */
void __free_write_buffer(void *data);   /* data buffer to free up */

/** Creates a named global label at the point the intrinsic is defined.
 *
 * @param label Name of the label to create
 *
 * This function creates a named global label at the point the intrinsic is defined.
 *
 * <b>Examples:</b>
 *
 * 1. This example creates a label named ixp_start_packet_count at the intrinsic invocation point. The name of the
label is exactly as specified (i.e., no "_" is prepended to the name). The name of the label must be unique. The
label does not interact with other C labels since C labels are renamed.
 * @code
 * global_label("ixp_start_packet_count");
 * @endcode
 *
 * 2. This fragment creates two different labels -- one global LABEL# and some other option/ code specific label,
 * such as 1_345#.
 *
 *@code
 * global_label(LABEL);
 * ...
 * LABEL:
 * @endcode
 */
void __global_label(char *label);       /* unique label name */

/** Causes a string constant (name) to be associated with an integer value at load time (using nfld)
 *  and returns the integer.
 *
 * Only 48-bit values are supported with this function.
 *
 * @param const_name  Name of a constant to bound at load time
 *
 * This function associates a constant name with an integer value at load time using nfld
 * and returns the integer. This provides equivalent functionality as the .import_var
 * using assembler. There is no register or memory allocated to this constant.
 * The name argument uniquely identifies the constant.
 *
 * A number of predefined import variables are supported by the linker. These are fully
 * resolved at link time. These are also documented in the assembler user guide.
 *
 * - __meid, __uengine_id : A microengine ID, format depends on chip family,
 *      -# For NFP-32xx: (cluster_num << 4) | (me_num) == __nfp_meid(cluster_num, menum)
 *      -# For NFP-6xxx: (island_id << 4) | (me_num + 4) == __nfp_meid(island_id, menum)
 * - __island: Island/Cluster number
 * - __menum: Zero-based microengine number within island.
 * - __addr_<id> : A series of predefined import variables that resolve to the
 *              base address of the <id> memory resource or target from the island the list file is assigned to.
 *              Values for <id> are the same as memory types used in __declspec, with dots replaced by underscores,
 *              and some additions for non-memory targets. For example:
 *      - __addr_emem0, __addr_i24_emem : Both base of emem0.
 *      - __addr_imem0, __addr_i28_imem : Both base of imem0.
 *      - __addr_iX_ctm : Base of CTM in island iX.
 *      - __addr_ctm : Base of CTM in local island. This is 0 for the default SDK IMB CPP Address Translation Tables.
 *      - __addr_iX_cls : Same as iX_ctm, but for CLS.
 *      - __addr_cls : Same as ctm, but for CLS.
 *      - __addr_i4_pcie, __addr_pcie0 : Both resolve to address 0 of PCIE island 4, to be used with pcie[] instructions.
 *      - __addr_i8_nbi, __addr_nbi0 : Same as bove, but for nbi[] instructions targeting NBI islands.
 *      - __addr_i48_ila, __addr_ila0 : Same as above, for ila[] instructions and ILA islands.
 *      - __addr_arm : For arm[] instructions targeting the ARM island.
 *
 * <b>Example:</b>
 *
 * In the following example, A1 and A2 have the same constant, which may or may not be the same
 * as the independent constant for B.
 *
 * @code
 * A1 = __LoadTimeConstant("CONST_A");
 * A2 = __LoadTimeConstant("CONST_A");
 * B = __LoadTimeConstant("CONST_B");
 * @endcode
 */
long long __LoadTimeConstant(char *const_name);

/**  This function provides generic access to linker symbols.
 *
 * @param id  Link-time symbol
 */
long long __link_sym(const char *id);

/**  This function provides equivalent functionality to .alloc_resource
 * in the assembler.
 *
 * @param argstr  Argument string
 */
unsigned long long __alloc_resource(const char *argstr);

/**
 * @}
 */

/** @addtogroup unaligned Unaligned Data Access
 *  @{
 *
 * The functions described in the following sections allow access to data that is
 * not aligned on natural boundaries (32 or 64 bits). They also allow access to
 * data types smaller than those supported by the hardware (8, 16, 32 and 64
 * bits) at any byte address.
 *
 * These functions take a two-part address:
 * A pointer, aligned or unaligned, an integer byte offset from the pointer.
 * For functions that do not specify a particular memory region in its name or argument list,
 * the pointer may point to
 * any memory region. For example, the following function gets a signed 8-bit integer addressed by
 * the void pointer "ptr" and the integer "offset":
 *
 * ua_get_s8(void *ptr, unsigned int offset);
 *
 * This function resolves the void pointer to the appropriate memory region (SRAM, MEM, LOCAL_MEM
 * or Cluster Local Scratch). In almost all situations, you should use these general functions to
 * access unaligned data. The function names are shorter and you do not have to specify the memory
 * region in which the data resides. However, in rare cases, the compiler will be unable to resolve
 * the pointer to a memory region. In these cases, you should use one of the memory-region-qualified
 * unaligned functions. For example:
 *
 * ua_get_s8_mem(__mem void *p, unsigned int offset);
 *
 * This function resolves the pointer to the MEM memory region and returns a signed 8-bit integer from MEM.
 * The following sections summarize all unaligned get, set, and memcpy intrinsic functions.
 *
 * @note These functions are ENDIAN aware and takes the compiler ENDIAN setting int account.
 *
 */

/**
 * @name Functions not specifying memory type
 * @{
 */

/** Get a signed 8-bit integer addressed by the pointer and offset from the
 * appropriate memory region.
 *
 * @param p         Pointer to location
 * @param offset    Offset from pointer location
 *
 * @return
 * @code*(signed char *)((int)p+offset);
 * @endcode
 */
int ua_get_s8(void *p, unsigned int offset);

/** Get a signed 16-bit integer addressed by the pointer and offset from the
 * appropriate memory region.
 *
 * @param p         Pointer to location
 * @param offset    Offset from pointer location
 *
 * @return
 * @code *(signed short *)((int)p+offset);
 * @endcode
 */
int ua_get_s16(void *p, unsigned int offset);

/** Get a signed 32-bit integer addressed by the pointer and offset from the
 * appropriate memory region.
 *
 * @param p         Pointer to location
 * @param offset    Offset from pointer location
 *
 * @return
 * @code *(int *)((int)p+offset);
 * @endcode
 */
int ua_get_s32(void *p, unsigned int offset);

/** Get a signed 64-bit integer addressed by the pointer and offset from the
 * appropriate memory region.
 *
 * @param p         Pointer to location
 * @param offset    Offset from pointer location
 *
 * @return
 * @code *(long long *)((int)p+offset);
 * @endcode
 */
long long ua_get_s64(void *p, unsigned int offset);

/** Get an unsigned 8-bit integer addressed by the pointer and offset from the
 * appropriate memory region.
 *
 * @param p         Pointer to location
 * @param offset    Offset from pointer location
 *
 * @return
 * @code *(unsigned char *)((int)p+offset);
 * @endcode
 */
unsigned int ua_get_u8(void *p, unsigned int offset);

/** Get an unsigned 16-bit integer addressed by the pointer and offset from the
 * appropriate memory region.
 *
 * @param p         Pointer to location
 * @param offset    Offset from pointer location
 *
 * @return
 * @code *(unsigned short *)((int)p+offset);
 * @endcode
 */
unsigned int ua_get_u16(void *p, unsigned int offset);

/** Get an unsigned 32-bit integer addressed by the pointer and offset from the
 * appropriate memory region.
 *
 * @param p         Pointer to location
 * @param offset    Offset from pointer location
 *
 * @return
 * @code *(unsigned int *)((int)p+offset);
 * @endcode
 */
unsigned int ua_get_u32(void *p, unsigned int offset);

/** Get an unsigned 64-bit integer addressed by the pointer and offset from the
 * appropriate memory region.
 *
 * @param p         Pointer to location
 * @param offset    Offset from pointer location
 *
 * @return
 * @code *(unsigned long long *)((int)p+offset);
 * @endcode
 */
unsigned long long ua_get_u64(void *p, unsigned int offset);

/** Set an unsigned 8-bit integer addressed by the pointer and offset in the
 * appropriate memory region.
 *
 * @param p         Pointer to location
 * @param offset    Offset from pointer location
 * @param value     Value to set
 */
void ua_set_8(void *p, unsigned int offset, unsigned int value);

/** Set an unsigned 16-bit integer addressed by the pointer and offset in the
 * appropriate memory region.
 *
 * @param p         Pointer to location
 * @param offset    Offset from pointer location
 * @param value     Value to set
 */
void ua_set_16(void *p, unsigned int offset, unsigned int value);

/** Set an unsigned 32-bit integer addressed by the pointer and offset in the
 * appropriate memory region.
 *
 * @param p         Pointer to location
 * @param offset    Offset from pointer location
 * @param value     Value to set
 */
void ua_set_32(void *p, unsigned int offset, unsigned int value);

/** Set an unsigned 64-bit integer addressed by the pointer and offset in the
 * appropriate memory region.
 *
 * @param p         Pointer to location
 * @param offset    Offset from pointer location
 * @param value     Value to set
 */
void ua_set_64(void *p, unsigned int offset, unsigned long long value);

/** Unaligned memory copy.
 *
 * Copies the number of bytes specified in the length argument from the source to the destination.
 * Both the source and the destination can reside in any memory region.
 *
 * @param dst       Pointer to destination
 * @param dst_off   Offset from destination pointer
 * @param src       Pointer to source
 * @param src_off   Offset from source pointer
 * @param length    Number of bytes to copy
 */
void ua_memcpy(void *dst, unsigned int dst_off, void *src, unsigned int src_off, unsigned int length);

/**
 * @}
 * @name Get functions specifying memory type
 * @{
 */

/** Get a signed 64-bit integer addressed by the pointer and offset from MEM.
 *
 * @param p         Pointer to MEM location
 * @param offset    Offset from pointer location
 *
 * @return
 * @code *(long long *)((int)p+offset);
 * @endcode
 */
long long ua_get_s64_mem(__mem void *p, unsigned int offset);

/** Get an unsigned 64-bit integer addressed by the pointer and offset from Cluster Local Scratch.
 *
 * @param p         Pointer to Cluster Local Scratch location
 * @param offset    Offset from pointer location
 *
 * @return
 * @code *(unsigned long long *)((int)p+offset);
 * @endcode
 */
unsigned long long ua_get_u64_cls(__cls void *p, unsigned int offset);

/**
 * @}
 * @name Set functions specifying memory type
 * @{
 */

/**
 * @}
 * @name Copy functions among memory types
 * @{
 */

/** Perform an unaligned copy from S-xfer register(s) to an aligned local
 * memory location with dst_off from 0 to 7. The unwritten trailing and
 * leading bytes written 32-bit words will be zeroed out. All leading unwritten
 * 32-bit words will be zeroed out as well.
 *
 * @param dst               Destination in local memory aligned (>=4) (depends on length)
 * @param dst_off           0..7 and must be a constant
 * @param ctx               0..7 and must be a constant
 * @param sxfer_reg_number  Destination xfer register
 * @param src_off           Source offset in range of dxfer[]
 * @param length            Byte length
 *
 * @note Known Issues & limitations (but not enforced):
 *      @li This implementation only supports big-endian
 *      @li dst_off must be 0..7
 *      @li dst must be properly aligned according to dst_off + length
 *          You can't safely pass middle of LM array to workaround the
 *          range limit of dst_off
 *      @li dst_off + length > 64 may not work
 *      @li src_off + length can't exceed xfer array
 *
 * @note __implicit_read(&sxfer) should follow this call.
 *
 */
void ua_memcpy_lmem0_7_sxfer_w_clr(
    __lmem void *dst,
    unsigned int dst_off,
    unsigned int ctx,
    unsigned int sxfer_reg_number,
    unsigned int src_off,
    unsigned int length
);

/**
 * Perform an unaligned copy from D-xfer register(s) to an aligned local memory
 * location with dst_off from 0 to 7.
 *
 * @param dst               Destination in local memory aligned (>=4) (depends on length)
 * @param dst_off           0..7 and must be a constant
 * @param ctx               0..7 and must be a constant
 * @param dxfer_reg_number  Destination xfer register
 * @param src_off           Source offset in range of dxfer[]
 * @param length            Byte length
 *
 * The unwritten trailing and leading bytes written 32-bit words will be zeroed out.
 * All leading unwritten 32-bit words will be zeroed out as well.
 *
 * @note __implicit_read(&dxfer) should follow this call.
 *
 * @see ua_memcpy_lmem0_7_sxfer_w_clr()
 */
void ua_memcpy_lmem0_7_dxfer_w_clr(
    __lmem void *dst,
    unsigned int dst_off,
    unsigned int ctx,
    unsigned int dxfer_reg_number,
    unsigned int src_off,
    unsigned int length
);

/**
 *  @}
 * @}
 */


/**
 * @addtogroup misc Miscellaneous Intrinsics
 * @{
 */

/** Marks a section of code as being on the critical path of the application.
 *
 * @param ... Optional argument indicates priority in 0-100. Default is 100.
 *
 * Takes an optional integer argument (0-100) that specifies the priority of overlapping critical paths.
 * Higher numbered paths receive higher priority for code layout. The default is 100 if no argument is
 * specified.
 */
void __critical_path(...);

/** Switch annotation.
 *
 * @note "Pack" refers to pack case body to the same size so jump[] src can be calculated by
 * zero-based index multiply max-size.
 */
typedef enum
{
    swpack_none,    /**< No pack, jump[] to a sequence of branch.                       */
    swpack_lmem,    /**< No pack, use local memory to hold branch table.                */
    swpack_auto,    /**< Auto pack when appropriate.                                    */
    swpack_1,       /**< Pack it, using up to 1 extra instruction to compute new src.   */
    swpack_2,       /**< Pack it, using up to 2 extra instructions to compute new src.  */
    swpack_3,       /**< Pack it, using up to 3 extra instructions to compute new src.  */
    swpack_4,       /**< Pack it, using up to 4 extra instructions to compute new src.  */
    swpack_5,       /**< Pack it, using up to 5 extra instructions to compute new src.  */
    swpack_6,       /**< Pack it, using up to 6 extra instructions to compute new src.  */
    swpack_7,       /**< Pack it, using up to 7 extra instructions to compute new src.  */
    swpack_8,       /**< Pack it, using up to 8 extra instructions to compute new src.  */
} swpack_t;

/** Ask the compiler to perform the default case removal optimization.
 *
 * This function should only be placed in the "default" handler of a switch() statement.
 */
void __impossible_path(void);

/** Ask the compiler to perform the switch block packing optimization.
 *
 * This function should only be placed in the "default" handler of a switch().
 *
 * @param swpack    Type of the switch packing optimization desired.
 * @param ...       Integer max_n_nop which defaults to -1 (auto, up to compiler)
 */
void __switch_pack(swpack_t swpack, ...);

/**
 * @}
 */

/* Other NFP includes */
#include "nfp_cluster_target.h"
#include "nfp_crypto.h"
#include "nfp_mem.h"
#include "nfp_cls.h"
#include "nfp_pcie.h"
#include "nfp_arm.h"
#include "nfp_math.h"

#endif /* __NFP_LEGACY_H__ */

