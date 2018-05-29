/*
 * Copyright (C) 2008-2014 Netronome Systems, Inc.  All rights reserved.
 */

#ifndef __NFP_MEM_TICKET_H__
#define __NFP_MEM_TICKET_H__

#ifndef NFP_LIB_ANY_NFCC_VERSION
    #if (!defined(__NFP_TOOL_NFCC) ||                       \
        (__NFP_TOOL_NFCC < NFP_SW_VERSION(5, 0, 0, 0)) ||   \
        (__NFP_TOOL_NFCC > NFP_SW_VERSION(6, 0, 2, 255)))
        #error "This standard library is not supported for the version of the SDK currently in use."
    #endif
#endif


/** @file nfp_mem_ticket.h
 *  @addtogroup mu_ticket MU Ticket Intrinsics
 *  @{
 */

/** @name Ticket release functions for MEM
 *  @{
 *
 * Ticket release commands are used for reordering management, for example to reorder packets after processing.
 *
 * Using 128 bit memory data structure (ticket line), these commands can help users to keep track of up to 96 packets.
 * The first word of this structure contains a 10 bit number (or ticket) of the packet currently being processed.
 * The remaining words contain a 96 bit map that marks tickets released prior to the current one.
 */

#ifdef __BIGENDIAN
/** Ticket line
 *
 * The ticket line is 128  bit memory structure managing the released tickets.
 */
typedef struct mem_ticket_line_t
{
    unsigned int reserved       : 22;       /**< Reserved                                    */
    unsigned int current_ticket : 10;       /**< Current ticket number released              */

    unsigned int bitmap0        : 32;       /**< Bitmap of tickets presented for release. Current ticket+1 to current ticket+31. */

    unsigned int bitmap1        : 32;       /**< Current ticket+32 to current ticket+63      */

    unsigned int bitmap2        : 32;       /**< Current ticket+64 to current ticket+95      */

} mem_ticket_line_t;

/** Ticket line push
 *
 * The ticket line is 128  bit memory structure managing the released tickets.
 * It differs from Ticket line in that the top 22 bits encodes a remote data master and data reference
 * to push the ticket release result to.
 */
typedef struct mem_ticket_line_push_t
{
    unsigned int master_cluster  :4;        /**< Cluster ID of ME that should receive the result. */
    unsigned int master_is_me    :1;        /**< Bit indicating if the result receiver is a ME. This bit should be set to 1. */
    unsigned int master_id       :3;        /**< Microengine ID that should receive the result. */
    unsigned int dataref_type    :3;        /**< Data reference type.
                                              *  0x0 - Transfer Register address
                                              *  0x3 - Next Neighbor register address
                                              *  0x2 - CSR address. In this case dataref_address[10] should be set to 0 */
    unsigned int dataref_address :11;       /**< Register or CSR address                      */
    unsigned int current_ticket : 10;       /**< Current ticket number released              */

    unsigned int bitmap0        : 32;       /**< Bitmap of tickets presented for release. Current ticket+1 to current ticket+31. */

    unsigned int bitmap1        : 32;       /**< Current ticket+32 to current ticket+63      */

    unsigned int bitmap2        : 32;       /**< Current ticket+64 to current ticket+95      */

} mem_ticket_line_push_t;

#else
/* __LITTLEENDIAN */

/* See BE description above */
typedef struct mem_ticket_line_t
{
    unsigned int current_ticket : 10;
    unsigned int reserved       : 22;

    unsigned int bitmap0        : 32;

    unsigned int bitmap1        : 32;

    unsigned int bitmap2        : 32;

} mem_ticket_line_t;

/* See BE description above */
typedef struct mem_ticket_line_push_t
{
    unsigned int current_ticket : 10;
    unsigned int dataref_address :10;
    unsigned int dataref_type    :4;
    unsigned int master_id       :3;
    unsigned int master_is_me    :1;
    unsigned int master_cluster  :4;

    unsigned int bitmap0        : 32;

    unsigned int bitmap1        : 32;

    unsigned int bitmap2        : 32;

} mem_ticket_line_push_t;
#endif

/** Release the supplied ticket number from the ticket line at a 32-bit addressed address.
 *
 * @param xfer          [In] Ticket number to release [Out] Release result
 * @param address       MEM address where the 128-bit ticket line starts
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal to raise upon completion
 *
 * Returns (via xfer) the number of consecutive released tickets or MEM_TICKET_RELEASE_ERROR.
 *
 *
 */
__intrinsic
void mem_ticket_release_ptr32(
    __xrw void *xfer,
    volatile void  __addr32 __mem *address,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
);

/** Release the supplied ticket number from the ticket line at a 40-bit address.
 *
 * @param xfer          [In] Ticket number to release [Out] Release result
 * @param address       40-bit MEM address where the 128-bit ticket line starts
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal to raise upon completion
 *
 * Returns (via xfer) the number of consecutive released tickets or MEM_TICKET_RELEASE_ERROR.
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_ticket_release_ptr40(
    __xrw void *xfer,
    volatile void __addr40 __mem *address,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
);
#endif

/** Release the supplied ticket number from the ticket line at a 32-bit addressed address.
 *
 * @param xfer          [In] Ticket number to release
 * @param address       MEM address where the 128-bit ticket line starts
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise in caller upon completion
 *
 * The result is 'pushed' to the data master and reference setup in the mem_ticket_line_t
 * structure pasted to mem_init_ticket_line.
 *
 * @note No signal is delivered to the data master and one would typically push to a
 * NN ring (dataref_type = 0x3) to prevent possible data loss.
 *
 *
 */
__intrinsic
void mem_ticket_release_push_ptr32(
    __xrw void *xfer,
    volatile void  __addr32 __mem *address,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** Release the supplied ticket number from the ticket line at a 40-bit address.
 *
 * @param xfer          [In] Ticket number to release
 * @param address       40-bit MEM address where the 128-bit ticket line starts
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise in caller upon completion
 *
 * The result is 'pushed' to the data master and reference setup in the mem_ticket_line_t
 * structure pasted to mem_init_ticket_line.
 *
 * @note No signal is delivered to the data master and one would typically push to a
 * NN ring (dataref_type = 0x3) to prevent possible data loss.
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_ticket_release_push_ptr40(
    __xrw void *xfer,
    volatile void __addr40 __mem *address,
    sync_t sync,
    SIGNAL *sig_ptr
);
#endif

/** Helper function for initializing the ticket release functionality in 32-bit addressed MEM.
 *
 * @param mem_ticket_line   Pre-populated mem_ticket_line_t struct to initialize MEM with
 * @param address  MEM address at which the 128-bit ticket structure should start
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_ptr  Signal to raise upon completion
 *
 *
 */
__intrinsic
void mem_ticket_line_init_ptr32(
    mem_ticket_line_t *mem_ticket_line,
    volatile void  __addr32 __mem *address,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** Helper function for initializing the ticket release functionality in 40-bit addressed MEM.
 *
 * @param mem_ticket_line   Pre-populated mem_ticket_line_t struct to initialize MEM with
 * @param address  40-bit MEM address at which the 128-bit ticket structure should start
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_ptr  Signal to raise upon completion
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_ticket_line_init_ptr40(
    mem_ticket_line_t *mem_ticket_line,
    volatile void __addr40 __mem *address,
    sync_t sync,
    SIGNAL *sig_ptr
);
#endif

/** Helper function for initializing the ticket release functionality in 32-bit addressed MEM.
 *
 * @param mem_ticket_line_push   Pre-populated mem_ticket_line_push_t struct to initialize MEM with
 * @param address  MEM address at which the 128-bit ticket structure should start
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_ptr  Signal to raise upon completion
 *
 * This variation enables the ability to push the result elsewhere.
 *
 *
 */
__intrinsic
void mem_ticket_line_push_init_ptr32(
    mem_ticket_line_push_t *mem_ticket_line_push,
    volatile void  __addr32 __mem *address,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** Helper function for initializing the ticket release functionality in 40-bit addressed MEM.
 *
 * @param mem_ticket_line_push   Pre-populated mem_ticket_line_push_t struct to initialize MEM with
 * @param address  40-bit MEM address at which the 128-bit ticket structure should start
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_ptr  Signal to raise upon completion
 *
 * This variation enables the ability to push the result elsewhere.
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_ticket_line_push_init_ptr40(
    mem_ticket_line_push_t *mem_ticket_line_push,
    volatile void __addr40 __mem *address,
    sync_t sync,
    SIGNAL *sig_ptr
);
#endif
/** @}
 * @}
 */

#endif /* __NFP_MEM_TICKET_H__ */

