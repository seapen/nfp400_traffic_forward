/*
 * Copyright (C) 2008-2014 Netronome Systems, Inc.  All rights reserved.
 */

#ifndef __NFP_MEM_LOCK_H__
#define __NFP_MEM_LOCK_H__

#ifndef NFP_LIB_ANY_NFCC_VERSION
    #if (!defined(__NFP_TOOL_NFCC) ||                       \
        (__NFP_TOOL_NFCC < NFP_SW_VERSION(5, 0, 0, 0)) ||   \
        (__NFP_TOOL_NFCC > NFP_SW_VERSION(6, 0, 2, 255)))
        #error "This standard library is not supported for the version of the SDK currently in use."
    #endif
#endif

/** @file nfp_mem_lock.h
 *  @addtogroup mu_lock MU Lock Intrinsics
 *  @{
 */

/** @name Memory lock functions for MEM
 *  @{
 * Memory lock commands support locking of specific ranges of memory as opposed to semantic locking supported
 * by queue locking commands. It allows the user to request a lock on a memory region with a specific size and base
 * address. The size of the locked region is specified in the byte mask and its address in the write transfer register.
 * Memory locks are implemented using 16-bit TCAM lookup with addition.
 */

/** 128-bit memory lock container type. */
typedef struct mem_lock128_t
{
    unsigned int value[4]; /**< Storage for the memory lock entries. */
} mem_lock128_t;

/** 256-bit memory lock container type. */
typedef struct mem_lock256_t
{
    unsigned int value[8]; /**< Storage for the memory lock entries. */
} mem_lock256_t;

/** 384-bit memory lock container type. */
typedef struct mem_lock384_t
{
    unsigned int value[12]; /**< Storage for the memory lock entries. */
} mem_lock384_t;

/** 512-bit memory lock container type. */
typedef struct mem_lock512_t
{
    unsigned int value[16]; /**< Storage for the memory lock entries. */
} mem_lock512_t;

/* Memory lock container type aligned in memory. */
typedef __addr32 __align16 mem_lock128_t  mem_lock128_in_mem_t;
typedef __addr32 __align16 mem_lock256_t  mem_lock256_in_mem_t;
typedef __addr32 __align16 mem_lock384_t  mem_lock384_in_mem_t;
typedef __addr32 __align16 mem_lock512_t  mem_lock512_in_mem_t;

/* Memory lock container pointer type aligned in 40-bit addressed MEM. */
#ifdef __PTR40
typedef __mem __addr40 __align16 mem_lock128_t *mem_lock128_ptr40_t;
typedef __mem __addr40 __align16 mem_lock256_t *mem_lock256_ptr40_t;
typedef __mem __addr40 __align16 mem_lock384_t *mem_lock384_ptr40_t;
typedef __mem __addr40 __align16 mem_lock512_t *mem_lock512_ptr40_t;
#endif

#ifdef __BIGENDIAN

/** Input type for the memory lock operation
 *
 * The address field must be populated before requesting the memory lock.
 */
typedef union mem_lock_in_t
{
    struct
    {
        unsigned int reserved       : 16;       /**< Unused, the regions are addressable to 64k regions */
        unsigned int address        : 16;       /**< Region address to lock
                                                     @note Bit 0 is reserved and is assumed to be 0.  */
    };
    unsigned int value;                         /**< Accessor to entire structure               */

} mem_lock_in_t;

/** Output type for the memory lock operation
 *
 *
 *
 */
typedef union mem_lock_out_t
{
    struct
    {
        unsigned int match_bitf     : 16;       /**< Bitfield of matching entries */
        unsigned int reserved       : 8;        /**< Reserved */
        unsigned int added          : 1;        /**< When set, this field indicates that an entry was added.
                                                 *   @note This field is also set when the memory lock queue is full. */
        unsigned int first_match    : 7;        /**< First matched entry number, or on a new memory lock entry where the entry was added.
                                                 *   @note All-bits in this field are set when the memory lock queue is full. */
    };
    unsigned int value;                         /**< Accessor to entire structure               */
} mem_lock_out_t;

#else
/* __LITTLEENDIAN */

/* See BE description above */
typedef union mem_lock_in_t
{
    struct
    {
        unsigned int address        : 16;
        unsigned int reserved       : 16;
    };
    unsigned int value;
} mem_lock_in_t;

/* See BE description above */
typedef union mem_lock_out_t
{
    struct
    {
        unsigned int first_match    : 7;
        unsigned int added          : 1;
        unsigned int reserved       : 8;
        unsigned int match_bitf     : 16;
    };
    unsigned int value;
} mem_lock_out_t;

#endif /* __BIGENDIAN */

/** Type for mem_lock_out_t in read registers. */
typedef __xread mem_lock_out_t        mem_lock_out_in_read_reg_t;

/** Initialize a 128-bit memory lock container in 32-bit addressed MEM in memory.
 *
 * @param mem_lock      Pointer to the memory lock container in MEM
 */
__intrinsic
void mem_lock128_init_ptr32(
    __mem mem_lock128_in_mem_t *mem_lock
);

/** Initialize a 128-bit memory lock container in 40-bit addressed MEM.
 *
 * @param mem_lock      Pointer to the memory lock container in MEM
 */
#ifdef __PTR40
__intrinsic
void mem_lock128_init_ptr40(
    mem_lock128_ptr40_t mem_lock
);
#endif

/** Initialize a 256-bit memory lock container in 32-bit addressed MEM.
 *
 * @param mem_lock      Pointer to the memory lock container in MEM
 */
__intrinsic
void mem_lock256_init_ptr32(
    __mem mem_lock256_in_mem_t *mem_lock
);

/** Initialize a 256-bit lock container in 40-bit addressed MEM.
 *
 * @param mem_lock      Pointer to the memory lock container in MEM
 */
#ifdef __PTR40
__intrinsic
void mem_lock256_init_ptr40(
    mem_lock256_ptr40_t mem_lock
);
#endif

/** Initialize a 384-bit memory lock container in 32-bit addressed MEM in memory.
 *
 * @param mem_lock      Pointer to the memory lock container in MEM
 */
__intrinsic
void mem_lock384_init_ptr32(
    __mem mem_lock384_in_mem_t *mem_lock
);

/** Initialize a 384-bit memory lock container in 40-bit addressed MEM.
 *
 * @param mem_lock      Pointer to the memory lock container in MEM
 */
#ifdef __PTR40
__intrinsic
void mem_lock384_init_ptr40(
    mem_lock384_ptr40_t mem_lock
);
#endif

/** Initialize a 512-bit memory lock container in 32-bit addressed MEM in memory.
 *
 * @param mem_lock      Pointer to the memory lock container in MEM
 */
__intrinsic
void mem_lock512_init_ptr32(
    __mem mem_lock512_in_mem_t *mem_lock
);

/** Initialize a 512-bit memory lock container in 40-bit addressed MEM.
 *
 * @param mem_lock      Pointer to the memory lock container in MEM
 */
#ifdef __PTR40
__intrinsic
void mem_lock512_init_ptr40(
    mem_lock512_ptr40_t mem_lock
);
#endif

/** Attempt to acquire a lock entry in a 128-bit lock container in 32-bit addressed MEM, supporting 4 locks .
 *
 * @param mem_lock          Pointer to the memory lock container in MEM
 * @param xfer              Pointer to write xfer register containing the region address
 * @param lsbzeroes         Number of least significant-bits to set to zero in the lock mask. This represent the lock region size.
 * @param sync              Type of synchronization to use. (must be sig_done)
 * @param sig_pair_ptr      Signal pair to raise upon completion
 * @return                  Pointer to the read transfer register containing the result of the lock attempt
 *
 * @note                    The result is returned in a mem_lock_out_t structure.

 * @see                     mem_lock_in_t, mem_lock_out_t
 *
 *
 */
__intrinsic
mem_lock_out_in_read_reg_t *mem_lock128_ptr32(
    __mem mem_lock128_in_mem_t *mem_lock,
    __xwrite mem_lock_in_t *xfer,
    unsigned int lsbzeroes,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
);

/** Attempt to acquire a lock entry in a 128-bit lock container in 40-bit addressed MEM, supporting 4 locks .
 *
 * @param mem_lock          Pointer to the memory lock container in MEM
 * @param xfer              Pointer to write xfer register containing the region address
 * @param lsbzeroes         Number of least significant-bits to set to zero in the lock mask. This represent the lock region size.
 * @param sync              Type of synchronization to use. (must be sig_done)
 * @param sig_pair_ptr      Signal pair to raise upon completion
 * @return                  Pointer to the read transfer register containing the result of the lock attempt
 *
 * @note                    The result is returned in a mem_lock_out_t structure.

 * @see                     mem_lock_in_t, mem_lock_out_t
 *
 *
 */
#ifdef __PTR40
__intrinsic
mem_lock_out_in_read_reg_t *mem_lock128_ptr40(
    mem_lock128_ptr40_t mem_lock,
    __xwrite mem_lock_in_t *xfer,
    unsigned int lsbzeroes,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
);
#endif

/** Attempt to acquire a lock entry in a 256-bit lock container in 32-bit addressed MEM, supporting 8 locks.
 *
 * @param mem_lock          Pointer to the memory lock container in MEM
 * @param xfer              Pointer to write xfer register containing the region address
 * @param lsbzeroes         Number of least significant-bits to set to zero in the lock mask. This represent the lock region size.
 * @param sync              Type of synchronization to use. (must be sig_done)
 * @param sig_pair_ptr      Signal pair to raise upon completion
 * @return                  Pointer to the read transfer register containing the result of the lock attempt
 *
 * @note                    The result is returned in a mem_lock_out_t structure.

 * @see                     mem_lock_in_t, mem_lock_out_t
 *
 *
 */
__intrinsic
mem_lock_out_in_read_reg_t *mem_lock256_ptr32(
    __mem mem_lock256_in_mem_t *mem_lock,
    __xwrite mem_lock_in_t *xfer,
    unsigned int lsbzeroes,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
);

/** Attempt to acquire a lock entry in a 256-bit lock container in 40-bit addressed MEM, supporting 8 locks.
 *
 * @param mem_lock          Pointer to the memory lock container in MEM
 * @param xfer              Pointer to write xfer register containing the region address
 * @param lsbzeroes         Number of least significant-bits to set to zero in the lock mask. This represent the lock region size.
 * @param sync              Type of synchronization to use. (must be sig_done)
 * @param sig_pair_ptr      Signal pair to raise upon completion
 * @return                  Pointer to the read transfer register containing the result of the lock attempt
 *
 * @note                    The result is returned in a mem_lock_out_t structure.

 * @see                     mem_lock_in_t, mem_lock_out_t
 *
 *
 */
#ifdef __PTR40
__intrinsic
mem_lock_out_in_read_reg_t *mem_lock256_ptr40(
    mem_lock256_ptr40_t mem_lock,
    __xwrite mem_lock_in_t *xfer,
    unsigned int lsbzeroes,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
);
#endif

/** Attempt to acquire a lock entry in a 384-bit lock container in 32-bit addressed MEM, supporting 12 locks.
 *
 * @param mem_lock          Pointer to the memory lock container in MEM
 * @param xfer              Pointer to write xfer register containing the region address
 * @param lsbzeroes         Number of least significant-bits to set to zero in the lock mask. This represent the lock region size.
 * @param sync              Type of synchronization to use. (must be sig_done)
 * @param sig_pair_ptr      Signal pair to raise upon completion
 * @return                  Pointer to the read transfer register containing the result of the lock attempt
 *
 * @note                    The result is returned in a mem_lock_out_t structure.

 * @see                     mem_lock_in_t, mem_lock_out_t
 *
 *
 */
__intrinsic
mem_lock_out_in_read_reg_t *mem_lock384_ptr32(
    __mem mem_lock384_in_mem_t *mem_lock,
    __xwrite mem_lock_in_t *xfer,
    unsigned int lsbzeroes,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
);

/** Attempt to acquire a lock entry in a 384-bit lock container in 40-bit addressed MEM, supporting 12 locks.
 *
 * @param mem_lock          Pointer to the memory lock container in MEM
 * @param xfer              Pointer to write xfer register containing the region address
 * @param lsbzeroes         Number of least significant-bits to set to zero in the lock mask. This represent the lock region size.
 * @param sync              Type of synchronization to use. (must be sig_done)
 * @param sig_pair_ptr      Signal pair to raise upon completion
 * @return                  Pointer to the read transfer register containing the result of the lock attempt
 *
 * @note                    The result is returned in a mem_lock_out_t structure.

 * @see                     mem_lock_in_t, mem_lock_out_t
 *
 *
 */
#ifdef __PTR40
__intrinsic
mem_lock_out_in_read_reg_t *mem_lock384_ptr40(
    mem_lock384_ptr40_t mem_lock,
    __xwrite mem_lock_in_t *xfer,
    unsigned int lsbzeroes,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
);
#endif

/** Attempt to acquire a lock entry in a 512-bit lock container in 32-bit addressed MEM, supporting 16 locks.
 *
 * @param mem_lock          Pointer to the memory lock container in MEM
 * @param xfer              Pointer to write xfer register containing the region address
 * @param lsbzeroes         Number of least significant-bits to set to zero in the lock mask. This represent the lock region size.
 * @param sync              Type of synchronization to use. (must be sig_done)
 * @param sig_pair_ptr      Signal pair to raise upon completion
 * @return                  Pointer to the read transfer register containing the result of the lock attempt
 *
 * @note                    The result is returned in a mem_lock_out_t structure.

 * @see                     mem_lock_in_t, mem_lock_out_t
 *
 *
 */
__intrinsic
mem_lock_out_in_read_reg_t *mem_lock512_ptr32(
    __mem mem_lock512_in_mem_t *mem_lock,
    __xwrite mem_lock_in_t *xfer,
    unsigned int lsbzeroes,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
);

/** Attempt to acquire a lock entry in a 512-bit lock container in 40-bit addressed MEM, supporting 16 locks.
 *
 * @param mem_lock          Pointer to the memory lock container in MEM
 * @param xfer              Pointer to write xfer register containing the region address
 * @param lsbzeroes         Number of least significant-bits to set to zero in the lock mask. This represent the lock region size.
 * @param sync              Type of synchronization to use. (must be sig_done)
 * @param sig_pair_ptr      Signal pair to raise upon completion
 * @return                  Pointer to the read transfer register containing the result of the lock attempt
 *
 * @note                    The result is returned in a mem_lock_out_t structure.

 * @see                     mem_lock_in_t, mem_lock_out_t
 *
 *
 */
#ifdef __PTR40
__intrinsic
mem_lock_out_in_read_reg_t *mem_lock512_ptr40(
    mem_lock512_ptr40_t mem_lock,
    __xwrite mem_lock_in_t *xfer,
    unsigned int lsbzeroes,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
);
#endif

/** Unlock a memory lock entry in a 128-bit lock container in 32-bit addressed MEM
 *
 * @param mem_lock          Pointer to the memory lock container in MEM
 * @param index             Memory lock entry to unlock (0 is the first entry)
 * @param sync              Type of synchronization to use. (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * @note The maximum index is 3.
 *
 *
 */
__intrinsic
void mem_unlock128_ptr32(
    __mem mem_lock128_in_mem_t *mem_lock,
    unsigned int index,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** Unlock a memory lock entry in a 128-bit lock container in 40-bit addressed MEM
 *
 * @param mem_lock          Pointer to the memory lock container in MEM
 * @param index             Memory lock entry to unlock (0 is the first entry)
 * @param sync              Type of synchronization to use. (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * @note The maximum index is 3.
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_unlock128_ptr40(
    mem_lock128_ptr40_t mem_lock,
    unsigned int index,
    sync_t sync,
    SIGNAL *sig_ptr
);
#endif

/** Unlock a memory lock entry in a 256-bit lock container in 32-bit addressed MEM
 *
 * @param mem_lock          Pointer to the memory lock container in MEM
 * @param index             Memory lock entry to unlock (0 is the first entry)
 * @param sync              Type of synchronization to use. (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * @note The maximum index is 7.
 *
 *
 */
__intrinsic
void mem_unlock256_ptr32(
    __mem mem_lock256_in_mem_t *mem_lock,
    unsigned int index,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** Unlock a memory lock entry in a 256-bit lock container in 40-bit addressed MEM
 *
 * @param mem_lock          Pointer to the memory lock container in MEM
 * @param index             Memory lock entry to unlock (0 is the first entry)
 * @param sync              Type of synchronization to use. (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * @note The maximum index is 7.
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_unlock256_ptr40(
    mem_lock256_ptr40_t mem_lock,
    unsigned int index,
    sync_t sync,
    SIGNAL *sig_ptr
);
#endif

/** Unlock a memory lock entry in a 384-bit lock container in 32-bit addressed MEM
 *
 * @param mem_lock          Pointer to the memory lock container in MEM
 * @param index             Memory lock entry to unlock (0 is the first entry)
 * @param sync              Type of synchronization to use. (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * @note The maximum index is 11.
 *
 *
 */
__intrinsic
void mem_unlock384_ptr32(
    __mem mem_lock384_in_mem_t *mem_lock,
    unsigned int index,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** Unlock a memory lock entry in a 384-bit lock container in 40-bit addressed MEM
 *
 * @param mem_lock          Pointer to the memory lock container in MEM
 * @param index             Memory lock entry to unlock (0 is the first entry)
 * @param sync              Type of synchronization to use. (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * @note The maximum index is 11.
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_unlock384_ptr40(
    mem_lock384_ptr40_t mem_lock,
    unsigned int index,
    sync_t sync,
    SIGNAL *sig_ptr
);
#endif

/** Unlock a memory lock entry in a 512-bit lock container in 32-bit addressed MEM
 *
 * @param mem_lock          Pointer to the memory lock container in MEM
 * @param index             Memory lock entry to unlock (0 is the first entry)
 * @param sync              Type of synchronization to use. (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * @note The maximum index is 15.
 *
 *
 */
__intrinsic
void mem_unlock512_ptr32(
    __mem mem_lock512_in_mem_t *mem_lock,
    unsigned int index,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** Unlock a memory lock entry in a 512-bit lock container in 40-bit addressed MEM
 *
 * @param mem_lock          Pointer to the memory lock container in MEM
 * @param index             Memory lock entry to unlock (0 is the first entry)
 * @param sync              Type of synchronization to use. (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * @note The maximum index is 15.
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_unlock512_ptr40(
    mem_lock512_ptr40_t mem_lock,
    unsigned int index,
    sync_t sync,
    SIGNAL *sig_ptr
);
#endif

/** @}
 * @}
 */

#endif /* __NFP_MEM_LOCK_H__ */

