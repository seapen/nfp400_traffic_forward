/*
 * Copyright (C) 2008-2014 Netronome Systems, Inc.  All rights reserved.
 */

/* mem lockq functions */

#ifndef __NFP_MEM_LOCKQ_H__
#define __NFP_MEM_LOCKQ_H__

#ifndef NFP_LIB_ANY_NFCC_VERSION
    #if (!defined(__NFP_TOOL_NFCC) ||                       \
        (__NFP_TOOL_NFCC < NFP_SW_VERSION(5, 0, 0, 0)) ||   \
        (__NFP_TOOL_NFCC > NFP_SW_VERSION(6, 0, 2, 255)))
        #error "This standard library is not supported for the version of the SDK currently in use."
    #endif
#endif

#include <nfp.h>
#include <nfp_intrinsic.h>


/** @file nfp_mem_lockq.h
 *  @addtogroup mu_queue_lock MU Queue Lock Intrinsics
 *  @{
 *
 *  @name Lock Queue functions for MEM
 *  @{
 *
 *  Lock queues maintain a queue of lock requests. A lock is acquired with mem_lockq128/256_lock(). Subsequent calls by
 *  other threads/MEs to mem_lockq128/256_lock() will block (not get signalled) until the lock is released with
 *  mem_lockq128/256_unlock() by the lock holder.
 *
 *  On queue overflow an odd signal is returned by mem_lockq128/256_lock().
 *
 *  @note Please refer to the section on MEM QueueLock Commands in the Databook for more detail.
 */
#ifdef __BIGENDIAN
/** Lock queue descriptor.
 */
typedef union mem_lockq_desc_t
{
    struct
    {
        unsigned int reserved_1     : 4;    /**< Reserved.                                          */

        unsigned int event_source   : 12;   /**< Event source number to include in event.           */
        unsigned int reserved_2     : 6;    /**< Reserved.                                          */

        unsigned int generate_event : 1;    /**< Generate event on under or overflow.               */
        unsigned int entry_size     : 1;    /**< Entry size - must but 0 to be 16 bits.             */
        unsigned int overflow       : 1;    /**< Set on overflow.                                   */
        unsigned int reserved_3     : 2;    /**< Reserved.                                          */
        unsigned int locked         : 1;    /**< Set when the lock has been given out.              */
        unsigned int num_elements   : 4;    /**< 0-6 or 0-14 depending on if it is a 128 or 256
                                             *   bit queue.
                                             */
    };
    unsigned int value;                     /**< Accessor to entire structure.                      */
} mem_lockq_desc_t;

/** Lock queue entries.
 *
 * This is an internal structure and no user manipulation is needed for the use of lock queues.
 */
typedef union mem_lockq_entry_t
{
    struct
    {
        unsigned short signal_ref    : 7;   /**< Signal Reference.              */
        unsigned short reserved      : 1;   /**< Reserved.                      */
        unsigned short signal_master : 8;   /**< Signal Master.                 */
    };
    unsigned short value;                   /**< Accessor to entire structure.  */
} mem_lockq_entry_t;

#else
/* !__BIGENDIAN */
typedef union mem_lockq_desc_t
{
    struct
    {

        unsigned int num_elements   : 4;
        unsigned int locked         : 1;
        unsigned int reserved_3     : 2;
        unsigned int overflow       : 1;
        unsigned int entry_size     : 1;
        unsigned int generate_event : 1;
        unsigned int reserved_2     : 6;
        unsigned int event_source   : 12;
        unsigned int reserved_1     : 4;
    };
    unsigned int value;
} mem_lockq_desc_t;

typedef union mem_lockq_entry_t
{
    struct
    {
        unsigned short signal_master : 8;
        unsigned short reserved      : 1;
        unsigned short signal_ref    : 7;
    };
    unsigned short value;
} mem_lockq_entry_t;

#endif /* __BIGENDIAN */

/** 128 bit lock queue container type.
 *  The first word is the queue descriptor @see mem_lockq_desc_t.
 */
typedef struct mem_lockq128_t
{
    mem_lockq_desc_t desc;                  /**< Lock queue descriptor */
    mem_lockq_entry_t q[7];                 /**< 3 words for queue contents */
} mem_lockq128_t;

/** 256 bit lock queue container type.
 *  The first word is the queue descriptor @see mem_lockq_desc_t.
 */
typedef struct mem_lockq256_t
{
    mem_lockq_desc_t desc;                  /**< Lock queue descriptor */
    mem_lockq_entry_t q[15];                /**< 7 words for queue contents */
} mem_lockq256_t;

/** 128 bit lock queue aligned in 32-bit addressed MEM. */
typedef volatile __addr32 __align16 mem_lockq128_t mem_lockq128_in_mem_t;


/** 128 bit lock queue pointer aligned in 40-bit addressed MEM. */
#ifdef __PTR40
typedef volatile __mem __addr40 __align16 mem_lockq128_t  *mem_lockq128_ptr40_t;
#endif


/** 256 bit lock queue aligned in 32-bit addressed MEM. */
typedef volatile __addr32 __align16 mem_lockq256_t mem_lockq256_in_mem_t;


/** 256 bit lock queue pointer aligned in 40-bit addressed MEM. */
#ifdef __PTR40
typedef volatile __mem __addr40 __align16 mem_lockq256_t *mem_lockq256_ptr40_t;
#endif


/** Claim a lock in a 128-bit lock queue in 32-bit addressed MEM.
 *
 * @param lockq             Pointer to lock queue in MEM
 * @param sync              Type of synchronization to use. Must be sig_done.
 * @param sig_pair_ptr      Even signal is raised upon completion. Odd signal is raised on overflow.
 */
__intrinsic
void mem_lockq128_lock_ptr32(
    __mem mem_lockq128_in_mem_t *lockq,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );


/** Claim a lock in a 128-bit lock queue in 32-bit addressed MEM with indirect word
 *
 * @param lockq             Pointer to lock queue in MEM
 * @param ind               Indirect word
 * @param sync              Type of synchronization to use. Must be sig_done.
 * @param sig_pair_ptr      Even signal is raised upon completion. Odd signal is raised on overflow.
 */
__intrinsic
void mem_lockq128_lock_ind_ptr32(
    __mem mem_lockq128_in_mem_t *lockq,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );


/** Claim a lock in a 128-bit lock queue in 40-bit addressed MEM.
 *
 * @param lockq             Pointer to lock queue in MEM
 * @param sync              Type of synchronization to use. Must be sig_done.
 * @param sig_pair_ptr      Even signal is raised upon completion. Odd signal is raised on overflow.
 */
#ifdef __PTR40
__intrinsic
void mem_lockq128_lock_ptr40(
    mem_lockq128_ptr40_t lockq,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Claim a lock in a 128-bit lock queue in 40-bit addressed MEM with indirect word
 *
 * @param lockq             Pointer to lock queue in MEM
 * @param ind               Indirect word
 * @param sync              Type of synchronization to use. Must be sig_done.
 * @param sig_pair_ptr      Even signal is raised upon completion. Odd signal is raised on overflow.
 */
#ifdef __PTR40
__intrinsic
void mem_lockq128_lock_ind_ptr40(
    mem_lockq128_ptr40_t lockq,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Claim a lock in a 256-bit lock queue in 32-bit addressed MEM.
 *
 * @param lockq             Pointer to lock queue in MEM
 * @param sync              Type of synchronization to use. Must be sig_done.
 * @param sig_pair_ptr      Even signal is raised upon completion. Odd signal is raised on overflow.
 */
__intrinsic
void mem_lockq256_lock_ptr32(
    __mem mem_lockq256_in_mem_t *lockq,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );


/** Claim a lock in a 256-bit lock queue in 32-bit addressed MEM with indirect word.
 *
 * @param lockq             Pointer to lock queue in MEM
 * @param ind               Indirect word
 * @param sync              Type of synchronization to use. Must be sig_done.
 * @param sig_pair_ptr      Even signal is raised upon completion. Odd signal is raised on overflow.
 */
__intrinsic
void mem_lockq256_lock_ind_ptr32(
    __mem mem_lockq256_in_mem_t *lockq,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );


/** Claim a lock in a 256-bit lock queue in 40-bit addressed MEM.
 *
 * @param lockq             Pointer to lock queue in 40-bit addressed MEM
 * @param sync              Type of synchronization to use. Must be sig_done.
 * @param sig_pair_ptr      Even signal is raised upon completion. Odd signal is raised on overflow.
 */
#ifdef __PTR40
__intrinsic
void mem_lockq256_lock_ptr40(
    mem_lockq256_ptr40_t lockq,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Claim a lock in a 256-bit lock queue in 40-bit addressed MEM with indirect word.
 *
 * @param lockq             Pointer to lock queue in 40-bit addressed MEM with indirect word.
 * @param ind               Indirect word
 * @param sync              Type of synchronization to use. Must be sig_done.
 * @param sig_pair_ptr      Even signal is raised upon completion. Odd signal is raised on overflow.
 */
#ifdef __PTR40
__intrinsic
void mem_lockq256_lock_ind_ptr40(
    mem_lockq256_ptr40_t lockq,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Release a lock in a 128-bit lock queue in 32-bit addressed MEM.
 *
 * @param lockq             Pointer to lock queue in MEM
 */
__intrinsic
void mem_lockq128_unlock_ptr32(
    __mem mem_lockq128_in_mem_t *lockq
    );


/** Release a lock in a 128-bit lock queue in 32-bit addressed MEM with indirect word
 *
 * @param lockq             Pointer to lock queue in MEM
 * @param ind               Indirect word
 */
__intrinsic
void mem_lockq128_unlock_ind_ptr32(
    __mem mem_lockq128_in_mem_t *lockq,
    generic_ind_t ind
    );


/** Release a lock in a 128-bit lock queue in 40-bit addressed MEM.
 *
 * @param lockq             Pointer to lock queue in MEM
 */
#ifdef __PTR40
__intrinsic
void mem_lockq128_unlock_ptr40(
    mem_lockq128_ptr40_t lockq
    );
#endif


/** Release a lock in a 128-bit lock queue in 40-bit addressed MEM  with indirect word.
 *
 * @param lockq             Pointer to lock queue in MEM
 * @param ind               Indirect word
 */
#ifdef __PTR40
__intrinsic
void mem_lockq128_unlock_ind_ptr40(
    mem_lockq128_ptr40_t lockq,
    generic_ind_t ind
    );
#endif




/** Release a lock in a 256-bit lock queue in 32-bit addressed MEM.
 *
 * @param lockq             Pointer to lock queue in MEM
 */
__intrinsic
void mem_lockq256_unlock_ptr32(
    __mem mem_lockq256_in_mem_t *lockq
    );


/** Release a lock in a 256-bit lock queue in 32-bit addressed MEM with indirect word.
 *
 * @param lockq             Pointer to lock queue in MEM
 * @param ind               Indirect word
 */
__intrinsic
void mem_lockq256_unlock_ind_ptr32(
    __mem mem_lockq256_in_mem_t *lockq,
    generic_ind_t ind
    );


/** Release a lock in a 256-bit lock queue in 40-bit addressed MEM.
 *
 * @param lockq             Pointer to lock queue in MEM
 */
#ifdef __PTR40
__intrinsic
void mem_lockq256_unlock_ptr40(
    mem_lockq256_ptr40_t lockq
    );
#endif


/** Release a lock in a 256-bit lock queue in 40-bit addressed MEM with indirect word.
 *
 * @param lockq             Pointer to lock queue in MEM
 * @param ind               Indirect word
 */
__intrinsic
#ifdef __PTR40
void mem_lockq256_unlock_ind_ptr40(
    mem_lockq256_ptr40_t lockq,
    generic_ind_t ind
    );
#endif




/** Initialize a 128-bit lock queue in 32-bit addressed MEM.
 *
 * @param lockq             Pointer to lock queue in MEM
 * @param generate_event    Enable event on overflow or underflow
 * @param event_source      Event to present on event bus if generate_event is 1
 *
 * The header of the lock queue is written and then read back to ensure the
 * lock queue is configured when this function returns.
 */
void mem_lockq128_init_ptr32(
    __mem mem_lockq128_in_mem_t *lockq,
    unsigned int generate_event,       /* Generate event on under or overflow */
    unsigned int event_source
    );

/** Initialize a 128-bit lock queue in 40-bit addressed MEM.
 *
 * @param lockq             Pointer to lock queue in MEM
 * @param generate_event    Enable event on overflow or underflow
 * @param event_source      Event to present on event bus if generate_event is 1
 *
 * The header of the lock queue is written and then read back to ensure the
 * lock queue is configured when this function returns.
 */
#ifdef __PTR40
void mem_lockq128_init_ptr40(
    mem_lockq128_ptr40_t lockq,
    unsigned int generate_event,       /* Generate event on under or overflow */
    unsigned int event_source
    );
#endif

/** Initialize a 256-bit lock queue in 32-bit addressed MEM.
 *
 * @param lockq             Pointer to lock queue in MEM
 * @param generate_event    Enable event on overflow or underflow
 * @param event_source      Event to present on event bus if generate_event is 1
 *
 * The header of the lock queue is written and then read back to ensure the
 * lock queue is configured when this function returns.
 */
void mem_lockq256_init_ptr32(
    __mem mem_lockq256_in_mem_t *lockq,
    unsigned int generate_event,       /* Generate event on under or overflow */
    unsigned int event_source
    );

/** Initialize a 256-bit lock queue in 40-bit addressed MEM.
 *
 * @param lockq             Pointer to lock queue in MEM
 * @param generate_event    Enable event on overflow or underflow
 * @param event_source      Event to present on event bus if generate_event is 1
 *
 * The header of the lock queue is written and then read back to ensure the
 * lock queue is configured when this function returns.
 */
#ifdef __PTR40
void mem_lockq256_init_ptr40(
    mem_lockq256_ptr40_t lockq,
    unsigned int generate_event,       /* Generate event on under or overflow */
    unsigned int event_source
    );
#endif

/** @}
 * @}
 * @}
 */

#endif /* __NFP_MEM_LOCKQ_H__ */

