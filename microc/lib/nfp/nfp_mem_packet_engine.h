/*
 * Copyright (C) 2008-2014 Netronome Systems, Inc.  All rights reserved.
 */

/* NFP NBI intrinsic function definitions */

#ifndef __NFP_MEM_PACKET_ENGINE_H__
#define __NFP_MEM_PACKET_ENGINE_H__

#ifndef NFP_LIB_ANY_NFCC_VERSION
    #if (!defined(__NFP_TOOL_NFCC) ||                       \
        (__NFP_TOOL_NFCC < NFP_SW_VERSION(5, 0, 0, 0)) ||   \
        (__NFP_TOOL_NFCC > NFP_SW_VERSION(6, 0, 2, 255)))
        #error "This standard library is not supported for the version of the SDK currently in use."
    #endif
#endif

/** @file nfp_mem_packet_engine.h
 * @addtogroup mu_pe MU PE (Packet Engine) Intrinsics
 * @{
 */

/** Packet engine rewrite script offset
 */
typedef enum MEM_PACKET_REWRITE_SCRIPT_OFFSET
{
    PACKET_ENGINE_SCRIPT_OFFSET_8        =   0,    /**< 0 = 8. */
    PACKET_ENGINE_SCRIPT_OFFSET_16       =   1,    /**< 1 = 16. */
    PACKET_ENGINE_SCRIPT_OFFSET_24       =   2,    /**< 2 = 24. */
    PACKET_ENGINE_SCRIPT_OFFSET_32       =   3,    /**< 3 = 32. */
    PACKET_ENGINE_SCRIPT_OFFSET_40       =   4,    /**< 4 = 40. */
    PACKET_ENGINE_SCRIPT_OFFSET_48       =   5,    /**< 5 = 48. */
    PACKET_ENGINE_SCRIPT_OFFSET_56       =   6,    /**< 6 = 56. */
} MEM_PACKET_REWRITE_SCRIPT_OFFSET;

/** Indicate the credit bucket of the packet engine for each master.
    The ME bucket is maintained for all ME masters.
 */
typedef enum MEM_PACKET_MASTER_BUCKET
{
    PACKET_ENGINE_MASTER_ME          =   0,    /**< Credits of all MEs. */
    PACKET_ENGINE_MASTER_NBI_0       =   1,    /**< Credits of NBI-0. */
    PACKET_ENGINE_MASTER_NBI_1       =   2     /**< Credits of NBI-1. */
} MEM_PACKET_MASTER_BUCKET;

/** Packet length for packet allocation
 */
typedef enum MEM_PACKET_LENGTH
{
    PACKET_LENGTH_256B      =   0,    /**< 256B packets are allocated at a 256B offset. */
    PACKET_LENGTH_512B      =   1,    /**< 512B packets are allocated at a 512B offset. */
    PACKET_LENGTH_1KB       =   2,    /**< 1KB packets are allocated at a 1KB offset. */
    PACKET_LENGTH_2KB       =   3     /**< 2KB packets are allocated at a 2KB offset. */
} MEM_PACKET_LENGTH;


/** The transfer type for packets.
 */
typedef enum MEM_PACKET_TRANSFER_TYPE
{
    PACKET_TRANSFER_ADDRESS_MODE        =   0,    /**< Transfer type is address mode */
    PACKET_TRANSER_PACKET_MODE          =   1    /**< Transfer type is packet mode  */
} MEM_PACKET_TRANSFER_TYPE;


#ifdef __BIGENDIAN

/** Response of mem_packet_read_packet_status
 */
typedef union mem_packet_read_status_response_t
{
    struct
    {
        unsigned int                error                   : 1;    /**< Error. */
        unsigned int                last_segment_received   : 1;    /**< Last segment received. */
        unsigned int                first_segment_received  : 1;    /**< First segment received.*/
        unsigned int                sent_to_ME              : 1;    /**< Packet sent to ME.*/
        unsigned int                packet_not_valid        : 1;    /**< Packet not valid, error.*/
        unsigned int                packet_owned_by_ME      : 1;    /**< Packet owner = 0 or packet owner = 1 is packet owned by ME. */
        MEM_PACKET_MASTER_BUCKET    packet_owner            : 2;    /**< Packet owner . */
        unsigned int                reserved2               : 6;    /**< Reserved. */
        MEM_PACKET_LENGTH           packet_length           : 2;    /**< Packet size. */
        unsigned int                reserved                : 6;    /**< Reserved. */
        unsigned int                ctm_dcache_address_256B : 10;   /**< CTM DCACHE address. Multiply by 256 to get actual CTM address.  */

    };
    unsigned int value;                                             /**< Accessor to entire structure */
} mem_packet_read_status_response_t;

#else /* __LITTLEENDIAN */

typedef union mem_packet_read_status_response_t
{
    struct
    {
        unsigned int                ctm_dcache_address_256B : 10;
        unsigned int                reserved                : 6;
        MEM_PACKET_LENGTH           packet_length           : 2;
        unsigned int                reserved2               : 6;
        MEM_PACKET_MASTER_BUCKET    packet_owner            : 2;
        unsigned int                packet_owned_by_ME      : 1;
        unsigned int                packet_not_valid        : 1;
        unsigned int                sent_to_ME              : 1;
        unsigned int                first_segment_received  : 1;
        unsigned int                last_segment_received   : 1;
        unsigned int                error                   : 1;
    };
    unsigned int value;
} mem_packet_read_status_response_t;

#endif /* __BIGENDIAN */

/** Type for response of mem_packet_read_packet_status in read registers. */
typedef __xread mem_packet_read_status_response_t      mem_packet_read_status_response_in_read_reg_t;




#ifdef __BIGENDIAN

/** Type for response of mem_packet_alloc
 */
typedef union mem_packet_alloc_response_t
{
    struct
    {
        unsigned int                reserved                : 2;     /**< Reserved. */
        unsigned int                packet_number           : 10;    /**< Last segment received. */
        unsigned int                packet_credit           : 11;    /**< Number of packets to be returned to the master. */
        unsigned int                buffer_credit           : 9;     /**< Number of buffers to be returned to the master. */
    };
    unsigned int value;                                             /**< Accessor to entire structure */
} mem_packet_alloc_response_t;

#else /* __LITTLEENDIAN */

typedef union mem_packet_alloc_response_t
{
    struct
    {
        unsigned int                buffer_credit           : 9;
        unsigned int                packet_credit           : 11;
        unsigned int                packet_number           : 10;
        unsigned int                reserved                : 2;
    };
    unsigned int value;
} mem_packet_alloc_response_t;


#endif

/** Type for response of mem_packet_alloc in read registers. */
typedef __xread mem_packet_alloc_response_t      mem_packet_alloc_response_in_read_reg_t;


/** Packet complete request
 */
#ifdef __BIGENDIAN
typedef union mem_packet_complete_request_t
{
    struct
    {
        unsigned int                        reserved                : 4;    /**< Not used. */
        unsigned int                        nbi_number              : 2;    /**< NBI number. */
        unsigned int                        total_packet_length     : 14;   /**< Total packet length. */
        MEM_PACKET_REWRITE_SCRIPT_OFFSET    script_offset           : 14;   /**< Script offset. */
        unsigned int                        sequencer_number        : 5;    /**< Sequencer number. */
        unsigned int                        sequence_number         : 12;   /**< Sequence number. */
        unsigned int                        tx_queue_number         : 10;   /**< Tx queue number. */
        unsigned int                        retry_bit               : 1;    /**< Retry bit. */
    };
    unsigned long long value;                                               /**< Accessor to entire structure */
} mem_packet_complete_request_t;

#else /* __LITTLEENDIAN */

typedef union mem_packet_complete_request_t
{
    struct
    {
        unsigned int                        retry_bit               : 1;
        unsigned int                        tx_queue_number         : 10;
        unsigned int                        sequence_number         : 12;
        unsigned int                        sequencer_number        : 5;
        MEM_PACKET_REWRITE_SCRIPT_OFFSET    script_offset           : 14;
        unsigned int                        total_packet_length     : 14;
        unsigned int                        nbi_number              : 2;
        unsigned int                        reserved                : 4;
    };
    unsigned long long value;
} mem_packet_complete_request_t;

#endif


#ifdef __BIGENDIAN

/** Packet header as Initial CTM transfer format. Two 32 bit words.
 */
typedef struct mem_packet_header_t
{
    union
    {
        struct
        {
            unsigned int                ctm_number              : 6;    /**< CTM that contains the packet. */
            unsigned int                packet_number           : 10;   /**< Packet number used to address the packet in CTM. */
            unsigned int                buffer_list_queue       : 2;    /**< Buffer list queue associated with the MU pointer. */
            unsigned int                packet_length           : 14;   /**< Packet length in bytes. */
        };
        unsigned int value;                                             /**< Accessor to word_1 structure. */
    } word_1;                                                            /**< First word. */

    union
    {
        struct
        {
            unsigned int                split                   : 1;     /**< Indicates if the packet is split between CTM and a memory buffer. */
            unsigned int                reserved                : 2;     /**< Reserved. */
            unsigned int                mu_pointer              : 29;    /**< MU pointer to the memory buffer at 2KB boundaries. */
        };
        unsigned int value;                                              /**< Accessor to word_2 structure */
    } word_2;                                                            /**< Second word. */
} mem_packet_header_t;

#else /* __LITTLEENDIAN */


typedef struct mem_packet_header_t
{
    union
    {
        struct
        {
            unsigned int                packet_length           : 14;
            unsigned int                buffer_list_queue       : 2;
            unsigned int                packet_number           : 10;
            unsigned int                ctm_number              : 6;
        };
        unsigned int value;
    } word_1;
    union
    {
        struct
        {
            unsigned int                mu_pointer              : 29;
            unsigned int                reserved                : 2;
            unsigned int                split                   : 1;
        } ;
        unsigned int value;
    } word_2;
} mem_packet_header_t;


#endif



/** MEM_PACKET_LENGTH_CALC_BYTE_LENGTH
 *
 * The PE packet size is given as 0=256 1=512 2=1024 3=2048 bytes. This macro translates it to a byte value
 *
 * @param pkt_size        MEM_PACKET_LENGTH: 0=256 1=512 2=1024 3=2048
 * @return                256B, 512B, 1024B, 2048B
 */
#define MEM_PACKET_LENGTH_CALC_BYTE_LENGTH(pkt_size)    (0x100 << ((0x100 | pkt_size) & 0x1f))


/** Return packet and buffer credits
 *
 * @param data              Transfer register for packet credit response
 * @param credit_bucket
 * - 0 - ME
 * - 1 - NBI0
 * - 2 - NBI1
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 *  The response is sent irrespective of the availability of packets/memory or packet/buffer credits.
 *  The ref_count
 */
__intrinsic
void mem_packet_credit_get(
    __xread void *data,
    enum MEM_PACKET_MASTER_BUCKET credit_bucket,
    sync_t sync,
    SIGNAL *sig_ptr
);


/** Packet allocation request.
 *
 * @param data              Transfer register for packet allocation response
 * @param credit_bucket
 * - 0 - ME
 * - 1 - NBI0
 * - 2 - NBI1
 * @param packet_length
 * - 0 - 256B
 * - 1 - 512B
 * - 2 - 1KB
 * - 3 - 2KB
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 *  If the packet cannot be allocated, the allocation request waits for a free packet.
 */
__intrinsic
void mem_packet_alloc(
    __xread mem_packet_alloc_response_t *data,
    enum MEM_PACKET_MASTER_BUCKET credit_bucket,
    enum MEM_PACKET_LENGTH packet_length,
    sync_t sync,
    SIGNAL *sig_ptr
);


/** Packet allocation poll request
 *
 * @param data              Transfer register for packet allocation response
 * @param credit_bucket
 * - 0 - ME
 * - 1 - NBI0
 * - 2 - NBI1
 * @param packet_length
 * - 0 - 256B
 * - 1 - 512B
 * - 2 - 1KB
 * - 3 - 2KB
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 *  If the packet cannot be allocated, the response is sent immediately indicating that
 *  the packet cannot be allocated. The response contains all 1's in the data field.
 *
 * The following example shows mem_packet_alloc_poll() request with mem_packet_read_packet_status().
 * @code
 *    mem_packet_alloc_response_in_read_reg_t   alloc_response;
 *    MEM_PACKET_MASTER_BUCKET                  bucket_master = PACKET_ENGINE_MASTER_NBI_1;
 *    unsigned int                              pkt_number;
 *    SIGNAL                                    sig;
 *
 *    // allocate two packets
 *    mem_packet_alloc_poll(&alloc_response, bucket_master, PACKET_LENGTH_1KB, ctx_swap, &sig);
 *    mem_packet_alloc_poll(&alloc_response, bucket_master, PACKET_LENGTH_1KB, ctx_swap, &sig);
 *
 *    pkt_number = alloc_response.packet_number; // packet number of second allocated packet
 *
 *    // read and verify the packet status of second allocated packet
 *    {
 *        mem_packet_read_status_response_in_read_reg_t packet_status;
 *
 *        mem_packet_read_packet_status(&packet_status, pkt_number, ctx_swap, &sig);
 *
 *        if (packet_status.packet_length != PACKET_LENGTH_1KB)
 *        {
 *            return 0;         // We have an error
 *        }
 *        if (packet_status.packet_owner != bucket_master)
 *        {
 *            return 0;         // We have an error
 *        }
 *        if (packet_status.error != 0)
 *        {
 *            return 0;         // We have an error
 *        }
 *        if (packet_status.packet_not_valid != 0)
 *        {
 *            return 0;         // We have an error
 *        }
 *   }
 *
 *    return 1;
 *
 * @endcode
 */
__intrinsic
void mem_packet_alloc_poll(
    __xread mem_packet_alloc_response_t *data,
    enum MEM_PACKET_MASTER_BUCKET credit_bucket,
    enum MEM_PACKET_LENGTH packet_length,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** Packet free request
 *
 * @param packet_number      Packet number to free
 *
 *  Free the packet
 */
__intrinsic
void mem_packet_free(
    unsigned int packet_number
);


/** Packet free and return pointer request
 *
 * @param data              Transfer register for packet free response
 * @param packet_number     Packet number to be freed
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 *  Free Packet and push MU Pointer of the freed packet.
 */
__intrinsic
void mem_packet_free_and_return_pointer(
    __xread void *data,
    unsigned int packet_number,
    sync_t sync,
    SIGNAL *sig_ptr
);


/** Packet free and signal request
 *
 * @param packet_number     Packet number to be freed
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 *  Free Packet and signal when packet is freed.
 */
__intrinsic
void mem_packet_free_and_signal(
    unsigned int packet_number,
    sync_t sync,
    SIGNAL *sig_ptr
);


/** Packet return pointer request
 *
 * @param data              Transfer register for packet MU pointer
 * @param packet_number     Packet number to be returned
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 *  Return the MU Pointer in the packet header
 */
__intrinsic
void mem_packet_return_pointer(
    __xread void *data,
    unsigned int packet_number,
    sync_t sync,
    SIGNAL *sig_ptr
);



/** Packet processing complete,
 *
 * @param packet_complete   Data for the packet complete command.
 * @param packet_number     Packet number of packet complete.
 *
 * Used for sequence number only.
 *
 * @ind_6000
 */
__intrinsic
void mem_packet_complete_drop(
    mem_packet_complete_request_t packet_complete,
    unsigned int packet_number
);


/** Packet processing complete for unicast packet.
 *
 * @param packet_complete   Data for the packet complete command.
 * @param packet_number     Packet number of packet complete.
 *
 * Packet processing complete and free packet on last transfer.
 *
 * @ind_6000
 */
__intrinsic
void mem_packet_complete_unicast(
    mem_packet_complete_request_t packet_complete,
    unsigned int packet_number
);


/** Packet processing complete for multicast packet.
 *
 * @param packet_complete   Data for the packet complete command.
 * @param packet_number     Packet number of packet complete.
 *
 * Packet processing complete but do not free packet on last transfer.
 *
 * @ind_6000
 */
__intrinsic
void mem_packet_complete_multicast(
    mem_packet_complete_request_t packet_complete,
    unsigned int packet_number
);


/** Packet processing complete for multicast packet.
 *
 * @param packet_complete    Data for the packet complete command.
 * @param packet_number     Packet number of packet complete.
 *
 * Packet processing complete and free packet on last transfer.
 *
 * @ind_6000
 */
__intrinsic
void mem_packet_complete_multicast_free(
    mem_packet_complete_request_t packet_complete,
    unsigned int packet_number
);


/** Packet read packet status
 *
 * @param data              Transfer register for packet read status response
 * @param packet_number     Packet number to read status of
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * Read the status of a packet. The status is returned regardless of the status of the packet.
 * If the read packet status FIFO is full; the response contains all f's.
 */
__intrinsic
void mem_packet_read_packet_status(
    __xread mem_packet_read_status_response_t *data,
    unsigned int packet_number,
    sync_t sync,
    SIGNAL *sig_ptr
);


/** Packet wait packet status
 *
 * @param data              Transfer register for packet read status response
 * @param packet_number     Packet number to read status of
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * Read the status of a packet. The status is returned after the last segment of the packet has
 * arrived. If the read packet status FIFO is full; the response contains all f's.
 */
__intrinsic
void mem_packet_wait_packet_status(
    __xread mem_packet_read_status_response_t *data,
    unsigned int packet_number,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** Add ME thread to Packet engine work queue
 *
 * @param data              Transfer register for packet allocation response
 * @param packet_offset     Offset to receive from after the first 6 32-bit words at 4 byte granularity.
 * @param count             Length in words of data to receive (valid values 6 -31)
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * Add an ME thread to the Packet Engine work queue for incoming packets.
 * If the ME adds itself to the Work Queue with a length '7' and offset '3', it receives
 * the first 6 32-bit words in 3 Push cycles. Next it receives 2 32-bit words starting at offset 3,
 * at the dataRef it specified.
 */
__intrinsic
void mem_packet_add_thread(
    __xread void *data,
    unsigned int packet_offset,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
);



/** Packet engine DMA to memory using packet mode.
 *
 * @param address           40 bit address of external memory including the MU island. Must be 8B aligned.
 * @param packet_offset     8B aligned offset with packet data to start DMA from.
 * @param packet_number     Packet number of packet to write.
 * @param ctm_island        Address of the CTM to execute instruction. Can be 0 for local island. See 6xxx databook for recommended addressing mode.
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * Move CTM data to main memory using packet mode. The packet number is specified as the source.
 * LoadTimeConstant() can be used to populate ctm_island address correctly, i.e. LoadTimeConstant("__ADDR_I34_CTM") for CTM on i34.
 *
 *
 * @ind_6000
 *
 *
 * The following shows an example of using mem_pe_dma_to_memory_packet():
 *
 * @code
 *    __emem_n(1) __addr40 unsigned long long           emem_address[6];
 *    mem_packet_alloc_response_in_read_reg_t           alloc_response;
 *    unsigned int                                      pkt_number;
 *    SIGNAL                                            sig;
 *    unsigned int                                      packet_offset = 0;
 *
 *    // allocate a packet
 *    mem_packet_alloc_poll
 *              (
 *              &alloc_response,
 *              PACKET_ENGINE_MASTER_NBI_1,
 *              PACKET_LENGTH_1KB,
 *              ctx_swap,
 *              &sig
 *              );
 *    pkt_number = alloc_response.packet_number;
 *
 *    // write to CTM in packet mode
 *    {
 *        __ctm unsigned int                    ctm_packet;
 *        __xwrite unsigned long long        write_data[2];
 *
 *        write_data[0] = 0x1122334455667788;
 *        write_data[1] = 0x9900aabbccddeeff;
 *        ctm_packet = (1 << 31) | (unsigned int)(pkt_number << 16) | (packet_offset);
 *        mem_write64
 *              (
 *              (void*)write_data,
 *              (volatile void __ctm*)ctm_packet,
 *              2,
 *              ctx_swap,
 *              &sig
 *              );
 *    }
 *    mem_pe_dma_to_memory_packet(emem_address, packet_offset, pkt_number, 0, ctx_swap, &sig);
 *
 *    // verify data in emem1
 *    {
 *        __xread unsigned long long        read_data[2];
 *
 *        mem_read64_ptr40((void*)read_data, emem_address, 2, ctx_swap, &sig);
 *
 *        if (read_data[0] != 0x1122334455667788)
 *        {
 *            return 0;         // We have an error
 *        }
 *        if (read_data[1] != 0x9900aabbccddeeff)
 *        {
 *           return 0;         // We have an error
 *        }
 *    }
 *
 *    return 1;
 *
 * @endcode
 *
 */
__intrinsic
void mem_pe_dma_to_memory_packet(
    volatile void __addr40 __mem *address,
    unsigned int packet_offset,
    unsigned int packet_number,
    unsigned int ctm_island,
    sync_t sync,
    SIGNAL *sig_ptr
);


/** Packet engine DMA to memory using packet mode. Free packet.
 *
 * @param address           40 bit address of external memory including the MU island. Must be 8B aligned.
 * @param packet_offset     8B aligned offset with packet data to start DMA from.
 * @param packet_number     Packet number of packet to write.
 * @param ctm_island        Address of the CTM to execute instruction. Can be 0 for local island. See 6xxx databook for recommended addressing mode.
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * Move CTM data to external memory using packet mode. The packet number is specified as the source.
 * Free packet after DMA completes.
 *
 * @note LoadTimeConstant() can be used to populate ctm_island address correctly,
 *      i.e. LoadTimeConstant("__ADDR_I34_CTM") for CTM on i34.
 *
 *
 * @ind_6000
 */
__intrinsic
void mem_pe_dma_to_memory_packet_free(
    volatile void __addr40 __mem *address,
    unsigned int packet_offset,
    unsigned int packet_number,
    unsigned int ctm_island,
    sync_t sync,
    SIGNAL *sig_ptr
);


/** Packet engine DMA to memory using packet mode. Byte swapped transferred data.
 *
 * @param address           40 bit address of external memory including the MU island. Must be 8B aligned.
 * @param packet_offset     8B aligned offset with packet data to start DMA from.
 * @param packet_number     Packet number of packet to write.
 * @param ctm_island        Address of the CTM to execute instruction. Can be 0 for local island. See 6xxx databook for recommended addressing mode.
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * Move CTM data to external memory using packet mode. The packet number is specified as the source.
 * Byte swap the transferred data.
 *
 * @note LoadTimeConstant() can be used to populate ctm_island address correctly,
 *      i.e. LoadTimeConstant("__ADDR_I34_CTM") for CTM on i34.
 *
 * @ind_6000
 */
__intrinsic
void mem_pe_dma_to_memory_packet_swap(
    volatile void __addr40 __mem *address,
    unsigned int packet_offset,
    unsigned int packet_number,
    unsigned int ctm_island,
    sync_t sync,
    SIGNAL *sig_ptr
);


/** Packet engine DMA to memory using packet mode. Byte swap the transferred data. Free packet.
 *
 * @param address           40 bit address of external memory including the MU island. Must be 8B aligned.
 * @param packet_offset     8B aligned offset with packet data to start DMA from.
 * @param packet_number     Packet number of packet to write.
 * @param ctm_island        Address of the CTM to execute instruction. Can be 0 for local island. See 6xxx databook for recommended addressing mode.
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * Move CTM data to external memory using packet mode. The packet number is specified as the source.
 * Byte swap the transferred data. Free packet after DMA completes.
*
 * @note LoadTimeConstant() can be used to populate ctm_island address correctly,
 *      i.e. LoadTimeConstant("__ADDR_I34_CTM") for CTM on i34.
 *
 * @ind_6000
 */
__intrinsic
void mem_pe_dma_to_memory_packet_free_swap(
    volatile void __addr40 __mem *address,
    unsigned int packet_offset,
    unsigned int packet_number,
    unsigned int ctm_island,
    sync_t sync,
    SIGNAL *sig_ptr
);


/** Packet engine DMA to memory using address mode.
 *
 * @param source_address        32 bit source address of CTM (must be 8B aligned)
 * @param destination_address   40 bit address of external memory including island and locality for the DMA command.
 * @param ctm_island            Address of the CTM to execute instruction. Can be 0 for local island. See 6xxx databook for recommended addressing mode.
 * @param count                 64B to 2048B where valid values (1-32)
 * @param sync                  Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr               Signal to raise upon completion
 *
 * Move CTM data to external memory using address mode. The CTM address is specified as the source.
 *
 * @note LoadTimeConstant() can be used to populate ctm_island address correctly,
 *      i.e. LoadTimeConstant("__ADDR_I34_CTM") for CTM on i34.
 *
 * @ind_6000
 */
__intrinsic
void mem_pe_dma_to_memory_buffer(
    volatile void __ctm *source_address,
    volatile void __addr40 __mem *destination_address,
    unsigned int ctm_island,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
);


/** Packet engine DMA to memory using address mode with byte swap.
 *
 * @param source_address        32 bit source address of CTM (must be 8B aligned)
 * @param destination_address   40 bit address of external memory including island and locality for the DMA command.
 * @param ctm_island            Address of the CTM to execute instruction. Can be 0 for local island. See 6xxx databook for recommended addressing mode.
 * @param count                 64B to 2048B where valid values (1-32)
 * @param sync                  Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr               Signal to raise upon completion
 *
 * Move CTM data to external memory using address mode with byte swap.
 * The CTM address is specified as the source.
 *
 * @note LoadTimeConstant() can be used to populate ctm_island address correctly,
 *      i.e. LoadTimeConstant("__ADDR_I34_CTM") for CTM on i34.
 *
 * @ind_6000
 */
__intrinsic
void mem_pe_dma_to_memory_buffer_swap(
    volatile void __ctm *source_address,
    volatile void __addr40 __mem *destination_address,
    unsigned int ctm_island,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
);


/** Packet engine DMA to memory using address mode. Use little_endian addressing.
 *
 * @param source_address        32 bit source address of CTM (must be 8B aligned)
 * @param destination_address   40 bit address of external memory including island and locality for the DMA command.
 * @param ctm_island            Address of the CTM to execute instruction. Can be 0 for local island. See 6xxx databook for recommended addressing mode.
 * @param count                 64B to 2048B where valid values (1-32)
 * @param sync                  Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr               Signal to raise upon completion
 *
 * Move CTM data to external memory using address mode with little endian addressing.
 * The CTM address is specified as the source.
 *
 * @note LoadTimeConstant() can be used to populate ctm_island address correctly,
 *      i.e. LoadTimeConstant("__ADDR_I34_CTM") for CTM on i34.
 *
 * @ind_6000
 */
__intrinsic
void mem_pe_dma_to_memory_buffer_le(
    volatile void __ctm *source_address,
    volatile void __addr40 __mem *destination_address,
    unsigned int ctm_island,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
);


/** Packet engine DMA to memory using address mode with byte swap. Use little_endian addressing.
 *
 * @param source_address        32 bit source address of CTM (must be 8B aligned)
 * @param destination_address   40 bit address of external memory including island and locality for the DMA command.
 * @param ctm_island            Address of the CTM to execute instruction. Can be 0 for local island. See 6xxx databook for recommended addressing mode.
 * @param count                 64B to 2048B where valid values (1-32)
 * @param sync                  Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr               Signal to raise upon completion
 *
 * Move CTM data to external memory using address mode with byte swap and little endian addressing.
 * The CTM address is specified as the source.
 *
 * @note LoadTimeConstant() can be used to populate ctm_island address correctly,
 *      i.e. LoadTimeConstant("__ADDR_I34_CTM") for CTM on i34.
 *
 * @ind_6000
 */
__intrinsic
void mem_pe_dma_to_memory_buffer_le_swap(
    volatile void __ctm *source_address,
    volatile void __addr40 __mem *destination_address,
    unsigned int ctm_island,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
);


/** Packet engine DMA from memory using address mode.
 *
 * @param source_address        40 bit address of external memory including island and locality for the DMA command.
 * @param destination_address   32 bit destination address of CTM (must be 8B aligned)
 * @param ctm_island            Address of the CTM to execute instruction. Can be 0 for local island. See 6xxx databook for recommended addressing mode.
 * @param count                 64B to 2048B where valid values (1-32)
 * @param sync                  Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr               Signal to raise upon completion
 *
 * Move data from external memory to CTM. The CTM address is specified as the destination address.
 *
 * @note LoadTimeConstant() can be used to populate ctm_island address correctly,
 *      i.e. LoadTimeConstant("__ADDR_I34_CTM") for CTM on i34.
 *
 * @ind_6000
 */
__intrinsic
void mem_pe_dma_from_memory_buffer(
    volatile void __addr40 __mem *source_address,
    volatile void __ctm *destination_address,
    unsigned int ctm_island,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
);



/** Packet engine DMA from memory using address mode with byte swap.
 *
 * @param source_address        40 bit address of external memory including island and locality for the DMA command.
 * @param destination_address   32 bit destination address of CTM (must be 8B aligned)
 * @param ctm_island            Address of the CTM to execute instruction. Can be 0 for local island. See 6xxx databook for recommended addressing mode.
 * @param count                 64B to 2048B where valid values (1-32)
 * @param sync                  Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr               Signal to raise upon completion
 *
 * Move data from external memory to CTM. The CTM address is specified as the destination address.
 *
 * @note LoadTimeConstant() can be used to populate ctm_island address correctly,
 *      i.e. LoadTimeConstant("__ADDR_I34_CTM") for CTM on i34.
 *
 * @ind_6000
 */
__intrinsic
void mem_pe_dma_from_memory_buffer_swap(
    volatile void __addr40 __mem *source_address,
    volatile void __ctm *destination_address,
    unsigned int ctm_island,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
);



/** Packet engine DMA from memory using address mode. Use little endian addressing.
 *
 * @param source_address        40 bit address of external memory including island and locality for the DMA command.
 * @param destination_address   32 bit destination address of CTM (must be 8B aligned)
 * @param ctm_island            Address of the CTM to execute instruction. Can be 0 for local island. See 6xxx databook for recommended addressing mode.
 * @param count                 64B to 2048B where valid values (1-32)
 * @param sync                  Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr               Signal to raise upon completion
 *
 * Move data from external memory to CTM. The CTM address is specified as the destination address.
 *
 * @note LoadTimeConstant() can be used to populate ctm_island address correctly,
 *      i.e. LoadTimeConstant("__ADDR_I34_CTM") for CTM on i34.
 *
 * @ind_6000
 */
__intrinsic
void mem_pe_dma_from_memory_buffer_le(
    volatile void __addr40 __mem *source_address,
    volatile void __ctm *destination_address,
    unsigned int ctm_island,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
);


/** Packet engine DMA from memory using address mode with byte swap. Use little endian addressing.
 *
 * @param source_address        40 bit address of external memory including island and locality for the DMA command.
 * @param destination_address   32 bit destination address of CTM (must be 8B aligned)
 * @param ctm_island            Address of the CTM to execute instruction. Can be 0 for local island. See 6xxx databook for recommended addressing mode.
 * @param count                 64B to 2048B where valid values (1-32)
 * @param sync                  Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr               Signal to raise upon completion
 *
 * Move data from external memory to CTM. The CTM address is specified as the destination address.
 *
 * @note LoadTimeConstant() can be used to populate ctm_island address correctly,
 *      i.e. LoadTimeConstant("__ADDR_I34_CTM") for CTM on i34.
 *
 * @ind_6000
 */
__intrinsic
void mem_pe_dma_from_memory_buffer_le_swap(
    volatile void __addr40 __mem *source_address,
    volatile void __ctm *destination_address,
    unsigned int ctm_island,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
);


/** Packet engine DMA to memory in packet mode.
 *
 * @param data              Transfer register with read result
 * @param packet_number     Packet number of packet to write
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * Write data from CTM packet to memory buffer. The packet should be setup
 * with a header as per initial CTM transfer format. The packet length and memory
 * address are used from this header to copy data from the CTM packet to memory.
 *
  * @note See union mem_packet_header_t to setup the header of ME allocated packet.
 */
__intrinsic
void mem_pe_dma_to_memory_indirect(
    __xread unsigned int *data,
    unsigned int packet_number,
    sync_t sync,
    SIGNAL *sig_ptr
);


/** Packet engine DMA to memory in packet mode with byte swap.
 *
 * @param data              Transfer register with read result
 * @param packet_number     Packet number of packet to write
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * Write data from CTM packet to memory buffer with byte swap. The packet should be setup
 * with a header as per initial CTM transfer format. The packet length and memory
 * address are used from this header to copy data from the CTM packet to memory.
 *
* @note See union mem_packet_header_t to setup the header of ME allocated packet.
 */
__intrinsic
void mem_pe_dma_to_memory_indirect_swap(
    __xread unsigned int *data,
    unsigned int packet_number,
    sync_t sync,
    SIGNAL *sig_ptr
);


/** Packet engine DMA to memory in packet mode. Free the packet after DMA completes.
 *
 * @param data              Transfer register with read result
 * @param packet_number     Packet number of packet to write
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * Write data from CTM packet to memory buffer and free packet after DMA completes.
 * The packet should be setup with a header as per initial CTM transfer format.
 * The packet length and memory address are used from this header to copy data from
 * the CTM packet to memory.
 *
 * @note See union mem_packet_header_t to setup the header of ME allocated packet.
 *
 */
__intrinsic
void mem_pe_dma_to_memory_indirect_free(
    __xread unsigned int *data,
    unsigned int packet_number,
    sync_t sync,
    SIGNAL *sig_ptr
);


/** Packet engine DMA to memory in packet mode with byte swap. Free the packet after DMA completes.
 *
 * @param data              Transfer register with read result
 * @param packet_number     Packet number of packet to write
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * Write data from CTM packet to memory buffer with byte swap and free packet after DMA completes.
 * The packet should have a header as per initial CTM transfer format.
 * The packet length and memory address are used from this header to copy data from
 * the CTM packet to memory.
 *
 * @note See union mem_packet_header_t to setup the header of ME allocated packet.
 *
 */
__intrinsic
void mem_pe_dma_to_memory_indirect_free_swap(
    __xread unsigned int *data,
    unsigned int packet_number,
    sync_t sync,
    SIGNAL *sig_ptr
);

/**
 *  @}
 * @}
 */

#endif /* __NFP_MEM_PACKET_ENGINE_H__ */

