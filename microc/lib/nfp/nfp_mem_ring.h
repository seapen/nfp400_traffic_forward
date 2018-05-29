/*
 * Copyright (C) 2008-2014 Netronome Systems, Inc.  All rights reserved.
 */

#ifndef __NFP_MEM_RING_H__
#define __NFP_MEM_RING_H__

#ifndef NFP_LIB_ANY_NFCC_VERSION
    #if (!defined(__NFP_TOOL_NFCC) ||                       \
        (__NFP_TOOL_NFCC < NFP_SW_VERSION(5, 0, 0, 0)) ||   \
        (__NFP_TOOL_NFCC > NFP_SW_VERSION(6, 0, 2, 255)))
        #error "This standard library is not supported for the version of the SDK currently in use."
    #endif
#endif

/** @file nfp_mem_ring.h
 * @addtogroup mu_ring MU Ring Intrinsics
 * @{
 */

/** @name Ring functions for MEM
 *  @{
 */

/** Return the byte address of the head of a ring for a given descriptor. */
#define MEM_RING_HEAD(desc) (((desc).head_ptr << 2) | (((desc).tail_ptr & ~0xFFFFFF) << 2))

/** Return the byte address of the tail of a ring for a given descriptor. */
#define MEM_RING_TAIL(desc)  ((desc).tail_ptr << 2)

/** Ring word size.
 */
typedef enum MEM_RING_SIZE
{
    RING_SIZE_512,   /**< 512 Long Words */
    RING_SIZE_1K,    /**< 1 K           */
    RING_SIZE_2K,    /**< 2 K           */
    RING_SIZE_4K,    /**< 4 K           */
    RING_SIZE_8K,    /**< 8 K           */
    RING_SIZE_16K,   /**< 16 K          */
    RING_SIZE_32K,   /**< 32 K          */
    RING_SIZE_64K,   /**< 64 K          */

    RING_SIZE_128K,  /**< 128 K         */
    RING_SIZE_256K,  /**< 256 K         */
    RING_SIZE_512K,  /**< 512 K         */
    RING_SIZE_1M,    /**< 1M            */
    RING_SIZE_2M,    /**< 2M            */
    RING_SIZE_4M,    /**< 4M            */
    RING_SIZE_8M,    /**< 8M            */
    RING_SIZE_16M,   /**< 16M           */
} MEM_RING_SIZE;

#ifdef __BIGENDIAN
/** Push descriptor type. */
typedef union mem_ring_desc_t
{
    struct
    {
        /*
         * First ring buffer descriptor longword
         */
        unsigned int ring_size  : 4;            /**< Ring size specification and must be one of MEM_RING_SIZE. @see MEM_RING_SIZE */
        unsigned int reserved_1 : 2;            /**< Reserved.                                          */
        unsigned int head_ptr   : 24;           /**< 24 - bit pointer - Byte address of ring buffer.
                                                    @note Must be aligned to the byte size of the ring. */
        unsigned int eop        : 1;            /**< This bit is set when an overflow occurred on journal command.
                                                     @see mem_ring_journal_buffer, mem_ring_fastjournal_imm */
        unsigned int reserved_2 : 1;            /**< Reserved.                                          */

        /*
         * Second ring buffer descriptor longword
         */
        unsigned int tail_ptr   : 30;           /**< Byte address of the tail of the ring.               */
        unsigned int q_type     : 2;            /**< Is set to 2 for ring intrinsic library functions.  */

        /*
         * Third ring buffer descriptor longword
         */
        unsigned int q_loc      : 2;            /**< Locality specification of data.                    */
        unsigned int reserved_3 : 4;            /**< Reserved.                                          */
        unsigned int q_page     : 2;            /**< Page of ring data.                                 */
        unsigned int q_count    : 24;           /**< Number of words on the ring.                       */

        /*
         * Fourth longword
         */
        unsigned int reserved_4;
    };
    unsigned int value[4];                      /**< Accessor to entire descriptor structure. */
} mem_ring_desc_t;

/** mem_ring_put return type.
 */
typedef struct mem_ring_put_status_t
{
    unsigned int success    : 1;                /**< Bit is set when data was placed on ring. */
    unsigned int reserved   : 7;                /**< Reserved.                                 */
    unsigned int words_in_ring_before_put : 24; /**< Number of words on ring before the operation. */
} mem_ring_put_status_t;

#else /* __LITTLEENDIAN */
typedef union mem_ring_desc_t
{
    struct
    {

        unsigned int reserved_2 : 1;
        unsigned int eop        : 1;
        unsigned int head_ptr   : 24;
        unsigned int reserved_1 : 2;
        unsigned int ring_size  : 4;

        unsigned int q_type     : 2;
        unsigned int tail_ptr   : 30;

        unsigned int q_count    : 24;
        unsigned int q_page     : 2;
        unsigned int reserved_3 : 4;
        unsigned int q_loc      : 2;

        unsigned int reserved_4;
    };
    unsigned int value[4];
} mem_ring_desc_t;

/*
 * mem_ring_put return type
 */
typedef struct mem_ring_put_status_t
{
    unsigned int words_in_ring_before_put : 24;
    unsigned int reserved       : 7;
    unsigned int success        : 1;
} mem_ring_put_status_t;
#endif /* __BIGENDIAN */


/** Descriptor type definition to ensure correct alignment in MEM.
 */
typedef __addr40 __align16 mem_ring_desc_t mem_ring_desc_in_mem_t;

/** mem_ring_put_status_t in a read register
 */
typedef __xread mem_ring_put_status_t mem_ring_put_status_in_read_reg_t;

/** Read MEM queue descriptor from MEM into queue array.
 *
 * @param ring_number           Ring descriptor number to load. The range of the ring number identifies the external memory to use.
 * - 0 - 1023:    emem0 or island 24,
 * - 1024 - 2047: emem1 or island 25,
 * - 2048 - 3071: emem2 or island 26
 * @param mem_ring_desc_in_mem  40 bit pointer to the Ring Descriptor in external memory including the MU island.
 *                              The pointer must be 16 byte aligned.
 *
 *
 */
__intrinsic
void mem_ring_read_desc(
    unsigned int ring_number,
    mem_ring_desc_in_mem_t *mem_ring_desc_in_mem
);

/** Write MEM queue descriptor from queue array into MEM.
 *
 * @param ring_number           Ring descriptor to write. The range of the ring number identifies the external memory to use.
 * - 0 - 1023:    emem0 or island 24,
 * - 1024 - 2047: emem1 or island 25,
 * - 2048 - 3071: emem2 or island 26
 * @param mem_ring_desc_in_mem    40 bit pointer where to place ring descriptor in external memory including the MU island.
 *                                  The pointer must be 16 byte aligned.
 *
 *
 */
__intrinsic
void mem_ring_write_desc(
    unsigned int ring_number,
    mem_ring_desc_in_mem_t *mem_ring_desc_in_mem
);

/** Push MEM queue descriptor from queue array into transfer registers.
 *
 * @param ring_number   Ring number descriptor to write. The range of the ring number identifies the external memory to use.
 * - 0 - 1023:    emem0 or island 24,
 * - 1024 - 2047: emem1 or island 25,
 * - 2048 - 3071: emem2 or island 26
 * @param xfer          Pointer to read xfer registers where the descriptor will be written
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 */
__intrinsic
void mem_ring_push_desc(
    unsigned int ring_number,
    __xread void *xfer,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** Read data from MEM ring at an offset from the base and place in transfer register(s)
 *   without checking for ring bounds.
 *
 * @param ring_number       MEM ring number to get data from. The range of the ring number identifies the external memory to use.
 * - 0 - 1023:    emem0 or island 24,
 * - 1024 - 2047: emem1 or island 25,
 * - 2048 - 3071: emem2 or island 26
 * @param xfer              Transfer register(s) receiving data
 * @param count             Number of 4-byte long words to get (1-16)
 * @param offset            Long word count offset from base of ring
 * @param sync              Type of synchronization to use
 * @param sig_ptr           Signal to raised upon completion
 *
 */
__intrinsic
void mem_ring_read_buffer_unbounded(
    unsigned int ring_number,
    __xread unsigned int *xfer,
    unsigned int count,
    unsigned int offset,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** Read data from MEM ring at an offset from the base and place in transfer register(s).
 *
 * @param ring_number       MEM ring number to get data from. The range of the ring number identifies the external memory to use.
 * - 0 - 1023:    emem0 or island 24,
 * - 1024 - 2047: emem1 or island 25,
 * - 2048 - 3071: emem2 or island 26
 * @param xfer              Transfer register(s) receiving data
 * @param count             Number of 4-byte long words to get (1-16)
 * @param offset            Long word count offset from base of ring
 * @param sync              Type of synchronization to use
 * @param sig_ptr           Signal to raised upon completion
 *
 */__intrinsic
void mem_ring_read_buffer(
    unsigned int ring_number,
    __xread unsigned int *xfer,
    unsigned int count,
    unsigned int offset,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** Write data at an offset in a ring without boundary checking.
 *
 * @param ring_number   Ring number. The range of the ring number identifies the external memory to use.
 * - 0 - 1023:    emem0 or island 24,
 * - 1024 - 2047: emem1 or island 25,
 * - 2048 - 3071: emem2 or island 26
 * @param xfer          Pointer to write xfer register(s) containing the data to write
 * @param count         Number of 32-bit word to put on the ring (1-16)
 * @param offset        Long word count offset from base of 16M word ring
 * @param sync          Type of synchronization to use
 * @param sig_ptr       Signal to raised upon completion
 *
 * This operation is used to access memory within the bounds of the maximum ring size
 * of the queue engine.
 *
 */
__intrinsic void mem_ring_write_buffer_unbounded(
    unsigned int ring_number,
    __xwrite void *xfer,
    unsigned int count,
    unsigned int offset,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** Write data at an offset into a ring.
 *
 * @param ring_number   Ring number. The range of the ring number identifies the external memory to use.
 * - 0 - 1023:    emem0 or island 24,
 * - 1024 - 2047: emem1 or island 25,
 * - 2048 - 3071: emem2 or island 26
 * @param xfer          Pointer to write xfer register(s) containing the data to write
 * @param count         Number of 32-bit word to put on the ring (1-16)
 * @param offset        Long word count offset from base of ring
 * @param sync          Type of synchronization to use
 * @param sig_ptr       Signal to raised upon completion
 *
 */
__intrinsic void mem_ring_write_buffer(
    unsigned int ring_number,
    __xwrite void *xfer,
    unsigned int count,
    unsigned int offset,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** Add a value to the tail of a ring wrapping it appropriately.
 *
 * @param ring_number   Ring number descriptor to write. The range of the ring number identifies the external memory to use.
 * - 0 - 1023:    emem0 or island 24,
 * - 1024 - 2047: emem1 or island 25,
 * - 2048 - 3071: emem2 or island 26
 * @param count         24 bit count to add to the tail
 *
 *
 */
__intrinsic
void mem_ring_add_tail(
    unsigned int ring_number,
    unsigned int count
);

/** Add data to the tail of a ring checking for overflow.
 *
 * @param ring_number   Ring number. The range of the ring number identifies the external memory to use.
 * - 0 - 1023:    emem0 or island 24,
 * - 1024 - 2047: emem1 or island 25,
 * - 2048 - 3071: emem2 or island 26
 * @param xfer          Pointer to read_write xfer register(s) containing the data to put on the ring
 * @param count         Number of 32-bit word to put on the ring (1-16)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 * @return              Pointer to read transfer register containing the status of the operation
 *
 */
__intrinsic
mem_ring_put_status_in_read_reg_t
*mem_ring_put_buffer(
    unsigned int ring_number,
    __xrw void *xfer,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
);

/** Add data to the tail of a ring without checking for overflow.
 *
 * @param ring_number   Ring number. The range of the ring number identifies the external memory to use.
 * - 0 - 1023:    emem0 or island 24,
 * - 1024 - 2047: emem1 or island 25,
 * - 2048 - 3071: emem2 or island 26
 * @param xfer          Pointer to write xfer register(s) containing the data to put on the ring
 * @param count         Number of 32-bit word to put on the ring (1-16)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 * @return              Read transfer register containing the status of the operation
 *
 */
__intrinsic
void
mem_ring_journal_buffer(
    unsigned int ring_number,
    __xwrite void *xfer,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** Fetch data from the head of MEM ring and place in transfer register(s).
 *
 * @param ring_number       MEM ring number to get data from. The range of the ring number identifies the external memory to use.
 * - 0 - 1023:    emem0 or island 24,
 * - 1024 - 2047: emem1 or island 25,
 * - 2048 - 3071: emem2 or island 26
 * @param xfer              Transfer register(s) receiving data
 * @param count             Number of 32-bit words to get (1-16)
 * @param sync              Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr      Even signal is raised upon completion. Odd signal is raised on underflow.
 *
 */
__intrinsic
void mem_ring_get_buffer(
    unsigned int ring_number,
    __xread unsigned int *xfer,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
);

/** Fetch data from the head of MEM ring, place in transfer register(s) and check
 *  for journal overflow.
 *
 * @param ring_number       MEM ring number to get data from. The range of the ring number identifies the external memory to use.
 * - 0 - 1023:    emem0 or island 24,
 * - 1024 - 2047: emem1 or island 25,
 * - 2048 - 3071: emem2 or island 26
 * @param xfer              Transfer register(s) receiving data
 * @param count             Number of 32-bit words to get (1-16)
 * @param sync              Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr      Even signal is raised upon completion. Odd signal is raised on underflow
 *                          or when overflow occurred during journal operation
 *
 * The EOP bit is cleared after this command
 *
 */
__intrinsic
void mem_ring_get_buffer_eop(
    unsigned int ring_number,
    __xread unsigned int *xfer,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
);


/** Fetch data from the head of MEM ring and place in transfer register(s). If not enough entries to return,
 *  do not return an error signal but return 0 for the remaining length after valid entries have been removed.
 *
 * @param ring_number       MEM ring number to get data from. The range of the ring number identifies the external memory to use.
 * - 0 - 1023:    emem0 or island 24,
 * - 1024 - 2047: emem1 or island 25,
 * - 2048 - 3071: emem2 or island 26
 * @param xfer              Transfer register(s) receiving data
 * @param count             Number of 32-bit words to get (1-16)
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * The following example shows how to create a ring in emem2 (i26). Note the setup of the ring_number
 * to indicate that the ring is in emem2.
 * @code
 *
 *    // ring head and tail on i26 or emem2
 *    __emem_n(2) __addr40 __align(512*sizeof(unsigned int)) unsigned int ring_mem[512];
 *    unsigned int        mu_island = 2;
 *    unsigned int        ring_number = (mu_island << 10) | 2;  // placing ring on emem2
 *    SIGNAL_PAIR         sig_pair;
 *    SIGNAL              sig;
 *
 *    mem_ring_init(ring_number, RING_SIZE_512, ring_mem, ring_mem, 0);
 *
 *    // Put some words on ring
 *    {
 *        __xrw unsigned int         data[3];
 *        __xread mem_ring_put_status_t     *ring_put_status;
 *        __xread unsigned int              status;
 *
 *        data[0] = 0x12345678;
 *        data[1] = 0x87654321;
 *        data[2] = 0x10101010;
 *
 *        ring_put_status = mem_ring_put_buffer(ring_number, data, 3, sig_done, &sig_pair);
 *        wait_for_all(&sig_pair);
 *
 *        if (!ring_put_status->success)
 *        {
 *            return 0;         // We have an error
 *        }
 *        if (ring_put_status->words_in_ring_before_put != 0)
 *        {
 *            return 0;         // We have an error
 *        }
 *    }
 *
 *    // Remove 4 entries from the head of the ring. The ring only contains 3 entries.
 *    // The last xfer(entry) returned will be 0.
 *    {
 *        __xread unsigned int        data_get[4];
 *
 *        mem_ring_get_buffer_freely(ring_number, data_get, 4, ctx_swap, &sig);
 *
 *        // First entry
 *        if (data_get[0] != 0x12345678)
 *        {
 *            return 0;         // We have an error
 *        }
 *        // Last xfer should be 0
 *        if (data_get[3] != 0x00)
 *        {
 *            return 0;         // We have an error
 *        }
 *    }
 *
 * @endcode
 */
__intrinsic
void mem_ring_get_buffer_freely(
    unsigned int ring_number,
    __xread unsigned int *xfer,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** Remove data from the tail of MEM ring and place in transfer register(s).
 *
 * @param ring_number       MEM ring number to get data from. The range of the ring number identifies the external memory to use.
 * - 0 - 1023:    emem0 or island 24,
 * - 1024 - 2047: emem1 or island 25,
 * - 2048 - 3071: emem2 or island 26
 * @param xfer              Transfer register(s) receiving data
 * @param count             Number of 32-bit words to get (1-16)
 * @param sync              Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr      Even signal is raised upon completion. Odd signal is raised on underflow.
 *
 * If there are not enough entries in the ring, no valid data is returned
 * and the tail pointer is not updated. An odd signal will also be delivered.
 *
 * Note that a single pop operation will return the words in the order they were added.
 * If the ring contains the words (A, B, C, D, E), then a single pop operation of 3 words
 * will return the values (C, D, E) in that order.
 *
 */
__intrinsic
void mem_ring_pop_buffer(
    unsigned int ring_number,
    __xread unsigned int *xfer,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
);

/** Fetch data from the tail of MEM ring and place in transfer register(s). If not enough entries to return,
 *  do not return an error signal but return 0 for the remaining length after valid entries have been removed.
 *
 * @param ring_number       MEM ring number to get data from. The range of the ring number identifies the external memory to use.
 * - 0 - 1023:    emem0 or island 24,
 * - 1024 - 2047: emem1 or island 25,
 * - 2048 - 3071: emem2 or island 26
 * @param xfer              Transfer register(s) receiving data
 * @param count             Number of 32-bit words to get (1-16)
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 */
__intrinsic
void mem_ring_pop_buffer_freely(
    unsigned int ring_number,
    __xread unsigned int *xfer,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Fetch data from the tail of MEM ring, place in transfer register(s) and check
 *  for journal overflow.
 *
 * @param ring_number       MEM ring number to get data from. The range of the ring number identifies the external memory to use.
 * - 0 - 1023:    emem0 or island 24,
 * - 1024 - 2047: emem1 or island 25,
 * - 2048 - 3071: emem2 or island 26
 * @param xfer              Transfer register(s) receiving data
 * @param count             Number of 32-bit words to get (1-16)
 * @param sync              Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr      Even signal is raised upon completion. Odd signal is raised on underflow or
 *                          when the EOP bit is set in the descriptor.
 *
 */
__intrinsic
void mem_ring_pop_buffer_eop(
    unsigned int ring_number,
    __xread unsigned int *xfer,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
);

/** FastJournal / Put Freely immediate data to the tail of a ring without checking for overflow.
 *
 * @param ring_number   Ring number. The range of the ring number identifies the external memory to use.
 * - 0 - 1023:    emem0 or island 24,
 * - 1024 - 2047: emem1 or island 25,
 * - 2048 - 3071: emem2 or island 26
 * @param longword      32-bit word to put on the ring
 *
 *
 * @note This function does not return a signal and the ME will automatically be throttled when it
 * generates too much data for the queue engine.
 *
 *
 */
__intrinsic
void
mem_ring_fastjournal_imm(
    unsigned int ring_number,
    unsigned int longword
);

/** Helper function to initialize a ring.
 *
 * @param ring_number   Ring number. The range of the ring number identifies the external memory to use.
 * - 0 - 1023:    emem0 or island 24,
 * - 1024 - 2047: emem1 or island 25,
 * - 2048 - 3071: emem2 or island 26
 * @param size          The ring size specified as one of enum MEM_RING_SIZE
 * @param head_ptr      Pointer to the head of the ring. Must be aligned to byte size of ring.
 * @param tail_ptr      Initial pointer to the tail of the ring. For an empty ring this is set to the head.
 * @param count         Initial number of words on the ring. For an empty ring this must be zero.
 *
 * This function configures the ring to be a type 2 in the queue engine
 *
 * The following example shows how to create a ring in emem2 (i26). Note the setup of the ring_number
 * to indicate that the ring is in emem2.
 * @code
 *
 *    // ring head and tail on i26 or emem2
 *    __emem_n(2) __addr40 __align(512*sizeof(unsigned int)) unsigned int ring_mem[512];
 *    unsigned int        mu_island = 2;
 *    unsigned int        ring_number = (mu_island << 10) | 2;    // placing ring on emem2
 *    SIGNAL_PAIR         sig_pair;
 *    SIGNAL              sig;
 *
 *    mem_ring_init(ring_number, RING_SIZE_512, ring_mem, ring_mem, 0);
 *
 *    // Put some words on ring
 *    {
 *        __xrw unsigned int         data[3];
 *        __xread mem_ring_put_status_t      *ring_put_status;
 *        __xread unsigned int               status;
 *
 *        data[0] = 0x12345678;
 *        data[1] = 0x87654321;
 *        data[2] = 0x10101010;
 *
 *        ring_put_status = mem_ring_put_buffer(ring_number, data, 3, sig_done, &sig_pair);
 *        wait_for_all(&sig_pair);
 *
 *        if (!ring_put_status->success)
 *        {
 *            return 0;         // We have an error
 *        }
 *        if (ring_put_status->words_in_ring_before_put != 0)
 *        {
 *            return 0;         // We have an error
 *        }
 *    }
 *
 *    // Verify count
 *    {
 *        __xread  mem_ring_desc_t descriptor;
 *        mem_ring_push_desc(ring_number, &descriptor, ctx_swap, &sig);
 *
 *        if (descriptor.q_count != 3)
 *        {
 *            return 0;         // We have an error
 *        }
 *    }
 *
 *    // Get buffer from head of ring
 *    {
 *        __xread unsigned int        data_get;
 *
 *        mem_ring_get_buffer(ring_number, &data_get, 1,  sig_done, &sig_pair);
 *        wait_for_all_single(&sig_pair.even);
 *
 *        if (data_get != 0x12345678)
 *        {
 *            return 0;         // We have an error
 *        }
 *    }
 *
 *    // Pop buffer from tail of ring
 *    {
 *        __xread unsigned int        data_pop;
 *
 *        mem_ring_pop_buffer(ring_number, &data_pop, 1,  sig_done, &sig_pair);
 *        wait_for_all_single(&sig_pair.even);
 *
 *        if (data_pop != 0x10101010)
 *        {
 *            return 0;         // We have an error
 *        }
 *    }
 *    return 1;
 *
 * @endcode
 */
void mem_ring_init
(
    unsigned int ring_number,
    enum MEM_RING_SIZE size,
    __addr40 __mem unsigned int *head_ptr,
    __addr40 __mem unsigned int *tail_ptr,
    unsigned int count
);

/** Helper function to initialize a ring with a locality and page specification.
 *
 * @param ring_number   Ring number. The range of the ring number identifies the external memory to use.
 * - 0 - 1023:    emem0 or island 24,
 * - 1024 - 2047: emem1 or island 25,
 * - 2048 - 3071: emem2 or island 26
 * @param size          The ring size specified as one of enum MEM_RING_SIZE
 * @param head_ptr      Pointer to the head of the ring. Must be aligned to byte size of ring.
 * @param tail_ptr      Initial pointer to the tail of the ring. For an empty ring this is set to the head.
 * @param count         Initial number of words on the ring. For an empty ring this must be zero.
 * @param q_locality    Locality of the ring. Please refer to Ring/Circular buffer section in PRM for detail.
 * @param q_page        4 Gigabyte page of ring
 *
 * This function uses a type 2 queue for the ring.
 *
 * The byte address of the head is given by
 *  {locality[1:0] 4b0 page[1:0] tail[29:24] head[23:0] 2b0}
 * and the  tail
 *  {locality[1:0] 4b0 page[1:0] tail[29:0] 2b0}
 *
 */
void mem_ring_init_with_loc_and_page
(
    unsigned int ring_number,
    enum MEM_RING_SIZE size,
    __addr40 __mem unsigned int *head_ptr,
    __addr40 __mem unsigned int *tail_ptr,
    unsigned int count,
    unsigned int q_locality,
    unsigned int q_page
);

/** @}
 * @}
 */


#endif /* __NFP_MEM_RING_H__ */

