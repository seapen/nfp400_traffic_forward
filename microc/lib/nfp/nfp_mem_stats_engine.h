/*
 * Copyright (C) 2008-2014 Netronome Systems, Inc.  All rights reserved.
 */

/* NFP MEM STATS intrinsic function definitions */

#ifndef __NFP_MEM_STATS_ENGINE_H__
#define __NFP_MEM_STATS_ENGINE_H__

#ifndef NFP_LIB_ANY_NFCC_VERSION
    #if (!defined(__NFP_TOOL_NFCC) ||                       \
        (__NFP_TOOL_NFCC < NFP_SW_VERSION(5, 0, 0, 0)) ||   \
        (__NFP_TOOL_NFCC > NFP_SW_VERSION(6, 0, 2, 255)))
        #error "This standard library is not supported for the version of the SDK currently in use."
    #endif
#endif


/** @file nfp_mem_stats_engine.h
 * @addtogroup mu_statistics MU Statistics Engine Intrinsics
 * @{
 */


/** @name Statistics Engine functions for MEM
 *  @{
 *
 * Statistics engine functions are available on internal memory, island 28 or island 29.
 *
 * Statistics are cleared with mem_stats_read_and_clear() and read with mem_stats_read().
 * Statistics are logged with mem_stats_log(), mem_stats_log_event(), mem_stats_log_saturate() or mem_stats_log_event_saturate().
 * The statistics can be in packed or unpacked format (mem_stats_unpacked_address_detail_t) or (mem_stats_packed_address_detail_t).
 *
 * Use helper macros MEM_STATS_EXTRACT_WRAP_PKT_AND_BYTE_COUNT() to extract
 * the packet and byte count or MEM_STATS_EXTRACT_SATURATE_PKT_AND_BYTE_COUNT() to also extract the saturation flag for
 * packet and byte count.
 *
 * Below is a complete example with statistics on island 28 (imem0) and the statistics (unpacked) are
 * cleared, logged and read to verify values.
 *
 * @code
 *    mem_stats_read_command_address_format_t     read_stats;
 *    SIGNAL              sig;
 *    unsigned int        count = 4;
 *    unsigned int        i;
 *    unsigned long long  island = (unsigned long long)LoadTimeConstant("__ADDR_I28_IMEM");
 *
 *    read_stats.value = 0;
 *    read_stats.base_address_select = BASE_ADDRESS_1;
 *    read_stats.statistic_address = 0x80;
 *
 *    // read and clear stats
 *    {
 *        // address for reading stats is made up from:
 *        //   - island id ([39:32]) and
 *        //   - mem_stats_read_command_address_format_t for lower 32 bits
 *        unsigned long long  stats_address = island | read_stats.value;
 *        __xread unsigned int read_register[8];
 *
 *        mem_stats_read_and_clear(
 *            (void *)read_register,
 *            (__addr40 __mem void *)stats_address,
 *            count,
 *            ctx_swap,
 *            &sig
 *        );
 *    }
 *
 *    // log stats
 *    {
 *        mem_stats_log_command_address_format_t  log_stats;
 *
 *        log_stats.value = 0;
 *        log_stats.add_byte_count_value = 0x11;
 *        log_stats.address_packed_config = STATS_ALL_32_BIT_UNPACKED;
 *
 *        {
 *            volatile __lmem mem_stats_unpacked_address_detail_t  stats_addr;
 *
 *            // address for logging stats is made up from:
 *            //   - island id ([39:32]) and
 *            //   - mem_stats_log_command_address_format_t for lower 32 bits
 *            unsigned long long                  stat_index_address = island | log_stats.value;
 *            __xwrite unsigned int  wr_reg[4];
 *
 *            stats_addr.value = 0;
 *            stats_addr.base_address_select = BASE_ADDRESS_1;
 *
 *            stats_addr.statistic_address = 0x80;
 *            wr_reg[0] = stats_addr.value;
 *
 *            stats_addr.statistic_address = 0x80 + 1;
 *            wr_reg[1] = stats_addr.value;
 *
 *            stats_addr.statistic_address = 0x80 + 2;
 *            wr_reg[2] = stats_addr.value;
 *
 *            stats_addr.statistic_address = 0x80 + 3;
 *            wr_reg[3] = stats_addr.value;
 *
 *         // increment statistics for all 4 addresses
 *            mem_stats_log(
 *                (void *)wr_reg,
 *                (__addr40 __mem void *) (stat_index_address),
 *                count*2,
 *                ctx_swap,
 *                &sig
 *                );
 *
 *         // increment statistics only for first address
 *            mem_stats_log(
 *                (void *)&wr_reg,
 *                (__addr40 __mem void *) (stat_index_address),
 *                2,
 *                ctx_swap,
 *                &sig
 *                );
 *        }
 *    }
 *
 *    // read statistics and verify content
 *    {
 *        unsigned long long stats_address = island | read_stats.value;
 *        __xread unsigned int rd_reg[8];
 *
 *        mem_stats_read(
 *            (void *)rd_reg,
 *            (__addr40 __mem void *) stats_address,
 *            3,
 *            ctx_swap,
 *            &sig
 *            );
 *
 *        // first statistics should be two packets and 0x11*2 byte count
 *        {
 *            unsigned long long stats0 = ((unsigned long long) rd_reg[1] << 32) | rd_reg[0];
 *            unsigned long long byte_cnt;
 *            unsigned int       pkt_cnt;
 *
 *            MEM_STATS_EXTRACT_WRAP_PKT_AND_BYTE_COUNT(stats0, pkt_cnt, byte_cnt);
 *
 *            if (byte_cnt != 0x22)
 *            {
 *                return 0;        // We have an error
 *            }
 *
 *            if (pkt_cnt != 0x2)
 *            {
 *                return 0;        // We have an error
 *            }
 *        }
 *
 *        // second statistics should be one packet and 0x11 byte count
 *        {
 *            unsigned long long stats1 = ((unsigned long long) rd_reg[3] << 32) | rd_reg[2];
 *            unsigned long long byte_cnt;
 *            unsigned int       pkt_cnt;
 *
 *            MEM_STATS_EXTRACT_WRAP_PKT_AND_BYTE_COUNT(stats1, pkt_cnt, byte_cnt);
 *
 *            if (byte_cnt != 0x11)
 *            {
 *                return 0;        // We have an error
 *            }
 *
 *            if (pkt_cnt != 0x1)
 *            {
 *                return 0;        // We have an error
 *            }
 *        }
 *    }
 *
 *    return 1;
 * @endcode
 */


/** Helper macro to extract only the packet count (29 bits) from 64-bit value
 *  after reading statistics in wrapping statistic format.
 */
#define MEM_STATS_WRAP_PACKET_COUNT(value) (value >> 35)

/** Helper macro to extract only the byte count (35 bits) from 64-bit value
 *  after reading statistics in wrapping statistic format.
 */
#define MEM_STATS_WRAP_BYTE_COUNT(value) (value & 0x7ffffffff)

/** Helper macro to extract the packet count (29 bits) and byte count (35 bits) from 64-bit value
 *  after reading statistics in wrapping statistic format.
 */
#define MEM_STATS_EXTRACT_WRAP_PKT_AND_BYTE_COUNT\
(value, pkt_cnt, byte_cnt)                                                      \
{                                                                               \
    byte_cnt = MEM_STATS_WRAP_BYTE_COUNT(value);                                \
    pkt_cnt = MEM_STATS_WRAP_PACKET_COUNT(value);                               \
}


/** Helper macro to extract only the packet count (28 bits) from 64-bit value
 *  after reading statistics in saturating statistic format.
 */
#define MEM_STATS_SATURATE_PACKET_COUNT(value) ((value >> 35) & 0x7fffffff)

/** Helper macro to extract only the byte count (34 bits) from 64-bit value
 *  after reading statistics in saturating statistic format.
 */
#define MEM_STATS_SATURATE_BYTE_COUNT(value) (value &  0x3ffffffff)

/** Helper macro to extract only the saturate packet count indicator (1 bit) from 64-bit value
 *  after reading statistics in saturating statistic format.
 */
#define MEM_STATS_SATURATE_PACKET_COUNT_SATURATE_IND(value) (value >> 63)

/** Helper macro to extract only the saturate byte count indicator (1 bit) from 64-bit value
 *  after reading statistics in saturating statistic format.
 */
#define MEM_STATS_SATURATE_BYTE_COUNT_SATURATE_IND(value) ((value >> 34) & 0x01)


/** Helper macro to extract the packet count (28 bits) and byte count (34 bits) as well as
 *  saturation indicators from the 64-bit value
 *  after reading statistics in saturate statistic format.
 */
#define MEM_STATS_EXTRACT_SATURATE_PKT_AND_BYTE_COUNT\
(value, pkt_cnt, byte_cnt, pkt_sat_flag, byte_sat_flag)                                            \
{                                                                                                  \
    byte_cnt = MEM_STATS_SATURATE_BYTE_COUNT(value);                                               \
    pkt_cnt = MEM_STATS_SATURATE_PACKET_COUNT(value);                                              \
    pkt_sat_flag =  MEM_STATS_SATURATE_PACKET_COUNT_SATURATE_IND(value);                           \
    byte_sat_flag = MEM_STATS_SATURATE_BYTE_COUNT_SATURATE_IND(value);                             \
}



/** Base address CSR select (MUSEBaseAddr)
 */
typedef enum MEM_STATS_BASE_ADDRESS_SELECT
{
    BASE_ADDRESS_0             = 0x00,     /**< Base address 0.    */
    BASE_ADDRESS_1             = 0x01,     /**< Base address 1.    */
    BASE_ADDRESS_2             = 0x02,     /**< Base address 2.    */
    BASE_ADDRESS_3             = 0x03,     /**< Base address 3.    */

} MEM_STATS_BASE_ADDRESS_SELECT;




/** Address packing configuration.
 */
typedef enum MEM_STATS_ADDRESS_PACK_CONFIG
{
    STATS_ALL_16_BIT_PACKED             = 0x01,     /**< All addresses are 16bit packed addresses.    */
    STATS_ALL_32_BIT_UNPACKED           = 0x02,     /**< All addresses are 32bit unpacked addresses.  */
    STATS_FIRST_32_BIT_UNPACKED_ONLY    = 0x03      /**< First address is 32bit unpacked and remaining addresses are 16bit packed. */

} MEM_STATS_ADDRESS_PACK_CONFIG;




#ifdef __BIGENDIAN

/** Log statistic command address field. */
typedef union mem_stats_log_command_address_format_t
{
    struct
    {
        unsigned int reserved                                       : 14;  /**< Reserved. */
        MEM_STATS_ADDRESS_PACK_CONFIG address_packed_config         : 2;   /**< How the pulled addresses are packed into the transfer registers. */
        unsigned int add_byte_count_value                           : 16;  /**< Value to add to the byte count statistics field.   */
    };
    unsigned int value;                             /**< Accessor to entire descriptor structure. */
} mem_stats_log_command_address_format_t;

#else /* __LITTLEENDIAN */

typedef union mem_stats_log_command_address_format_t
{
    struct
    {
        unsigned int add_byte_count_value                           : 16;
        MEM_STATS_ADDRESS_PACK_CONFIG address_packed_config         : 2;
        unsigned int reserved                                       : 14;
    };
    unsigned int value;
} mem_stats_log_command_address_format_t;

#endif


#ifdef __BIGENDIAN

/** Read (push) statistic command address field. */
typedef union mem_stats_read_command_address_format_t
{
    struct
    {
        MEM_STATS_BASE_ADDRESS_SELECT base_address_select           : 2;    /**< Select base address for statistics address. */
        unsigned int reserved_2                                     : 8;    /**< Reserved. */
        unsigned int statistic_address                              : 19;   /**< Statistic address (64b aligned).  */
        unsigned int reserved_1                                     : 3;    /**< Reserved. */
    };
    unsigned int value;                                                     /**< Accessor to entire descriptor structure. */
} mem_stats_read_command_address_format_t;

#else /* __LITTLEENDIAN */

typedef union mem_stats_read_command_address_format_t
{
    struct
    {
        unsigned int reserved_1                                     : 3;
        unsigned int statistic_address                              : 19;
        unsigned int reserved_2                                     : 8;
        MEM_STATS_BASE_ADDRESS_SELECT base_address_select           : 2;
    };
    unsigned int value;
} mem_stats_read_command_address_format_t;

#endif




#ifdef __BIGENDIAN

/** Statistic packed address detail (16 bit). */
typedef union mem_stats_packed_address_detail_t
{
    struct
    {
        MEM_STATS_BASE_ADDRESS_SELECT base_address_select           :  2;   /**< Select base address for statistics address. */
        unsigned int statistic_address                              : 14;   /**< Statistic address (64b aligned).  */
    };
    unsigned short value;                                                   /**< Accessor to entire descriptor structure. */
} mem_stats_packed_address_detail_t;

#else /* __LITTLEENDIAN */

typedef union mem_stats_packed_address_detail_t
{
    struct
    {
        unsigned int statistic_address                              : 14;
        MEM_STATS_BASE_ADDRESS_SELECT base_address_select           :  2;
    };
    unsigned short value;
} mem_stats_packed_address_detail_t;

#endif



#ifdef __BIGENDIAN

/** Statistic unpacked address detail (32 bit). */
typedef union mem_stats_unpacked_address_detail_t
{
    struct
    {
        MEM_STATS_BASE_ADDRESS_SELECT base_address_select           :  2;   /**< Select base address for statistics address. */
        unsigned int reserved                                       : 11;   /**< Reserved. */
        unsigned int statistic_address                              : 19;   /**< Statistic address (64b aligned).  */
    };
    unsigned int value;                                                     /**< Accessor to entire descriptor structure. */
} mem_stats_unpacked_address_detail_t;

#else /* __LITTLEENDIAN */

typedef union mem_stats_unpacked_address_detail_t
{
    struct
    {
        unsigned int statistic_address                              : 19;
        unsigned int reserved                                       : 11;
        MEM_STATS_BASE_ADDRESS_SELECT base_address_select           :  2;
    };
    unsigned int value;
} mem_stats_unpacked_address_detail_t;

#endif




/** Retrieve the statistic data from the data cache.
 *
 * @param xfer              Transfer registers containing statistics data
 * @param address           40 bit pointer containing mu island in upper 8 bits (see 6xxx databook for recommended addressing mode) and
 *                           mem_stats_read_command_address_format_t for the lower 32 bits.
 * @param count             Length in 64-bits to read (valid values 1-16).
 * @param sync              Type of synchronization to use (sig_done or ctx_swap).
 * @param sig_ptr           Signal to raise upon completion.
 *
 *
 */
__intrinsic
void mem_stats_read(
    __xread void *xfer,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** Retrieve the statistic data from the data cache and also clear the the statistics data on read.
 *
 * @param xfer              Transfer registers containing statistics data.
 * @param address           40 bit pointer containing mu island in upper 8 bits (see 6xxx databook for recommended addressing mode) and
 *                           mem_stats_read_command_address_format_t for the lower 32 bits.
 * @param count             Length in 64-bits to read (valid values 1-16).
 * @param sync              Type of synchronization to use (sig_done or ctx_swap).
 * @param sig_ptr           Signal to raise upon completion.
 *
 *
 */
__intrinsic
void mem_stats_read_and_clear(
    __xread void *xfer,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** Log statistics data by adding byte count and incrementing packet count to specified statistics.
 *
 * @param xfer              Transfer registers containing statistic addresses. Use either mem_stats_unpacked_address_detail_t
 *                          or mem_stats_packed_address_detail_t
 * @param data              40 bit pointer containing the mu island in the 8 upper bits (see 6xxx databook for recommended addressing mode) and
 *                          mem_stats_log_command_address_format_t for the lower 32 bits
 * @param count             Number of statistic updates in 16-bit statistic address pointers to pull (valid values 1-16)
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 *
 * A single command can support a maximum of sixteen statistic updates, where each statistic data is updated with the
 * same byte count add value. Stats format is wrapping format.
 */
__intrinsic
void mem_stats_log(
    __xwrite void *xfer,
    volatile void __addr40 __mem *data,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
);



/** Log statistics data with saturation by adding byte count and incrementing packet count to specified statistics.
 *
 * @param xfer              Transfer registers containing statistic addresses. Use either mem_stats_unpacked_address_detail_t
 *                           or mem_stats_packed_address_detail_t
 * @param data              40 bit pointer containing the mu island in the 8 upper bits (see 6xxx databook for recommended addressing mode) and
 *                           mem_stats_log_command_address_format_t for the lower 32 bits
 * @param count             Number of statistic updates in 16-bit statistic address pointers to pull  (valid values 1-16)
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * A single command can support a maximum of sixteen statistic updates, where each statistic data is updated with the
 * same byte count add value.
 * Saturating statistics will continue to update after the saturation point is reached and the
 * saturate indicator will indicate the counter reached saturation point. Saturation indicator will remain set until command
 * stats_push_clear is performed to the same address.
 */
__intrinsic
void mem_stats_log_saturate(
    __xwrite void *xfer,
    volatile void __addr40 __mem *data,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
);


/** Log statistics data and also supports packet and byte counter half-wrap (event type = 3)
 *  and full-wrap (event type = 2) thresholds.
 *
 * @param xfer              Transfer registers containing statistic addresses. Use either mem_stats_unpacked_address_detail_t
 *                           or mem_stats_packed_address_detail_t
 * @param data              40 bit pointer containing the mu island in the 8 upper bits (see 6xxx databook for recommended addressing mode) and
 *                           mem_stats_log_command_address_format_t for the lower 32 bits
 * @param count             Number of statistic updates in 16-bit statistic address pointers to pull  (valid values 1- 16)
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * Same as: @see mem_stats_log but also raises an event on half wrap or full wrap levels.
 * Note that the continued counting will re-trigger half-wrap and full-wrap events when reached if the
 * stat has not been cleared.
 *
 */
__intrinsic
void mem_stats_log_event(
    __xwrite void *xfer,
    volatile void __addr40 __mem *data,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
);



/** Log statistics data with saturation and also supports packet and byte counter half-wrap (event type = 3)
 *  and full-wrap (event type = 2) thresholds.
 *
 * @param xfer              Transfer registers containing statistic addresses. Use either mem_stats_unpacked_address_detail_t
 *                          or mem_stats_packed_address_detail_t
 * @param data              40 bit pointer containing the mu island in the 8 upper bits (see 6xxx databook for recommended addressing mode) and
 *                          mem_stats_log_command_address_format_t for the lower 32 bits
 * @param count             Number of statistic updates in 16-bit statistic address pointers to pull  (valid values 1 - 16)
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * Same as: @see mem_stats_log_saturate but also raises an event on half wrap or full wrap levels.
 * Note that the continued counting will re-trigger half-wrap and full-wrap events when reached if the
 * stat has not been cleared.

 */
__intrinsic
void mem_stats_log_event_saturate(
    __xwrite void *xfer,
    volatile void __addr40 __mem *data,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
);

/**
 *  @}
 * @}
 */

#endif /* __NFP_MEM_STATS_ENGINE_H__ */

