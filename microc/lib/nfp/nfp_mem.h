/*
 * Copyright (C) 2008-2014 Netronome Systems, Inc.  All rights reserved.
 */

/* DRAM extended functions */

#ifndef __NFP_MEM_H__
#define __NFP_MEM_H__

#ifndef NFP_LIB_ANY_NFCC_VERSION
    #if (!defined(__NFP_TOOL_NFCC) ||                       \
        (__NFP_TOOL_NFCC < NFP_SW_VERSION(5, 0, 0, 0)) ||   \
        (__NFP_TOOL_NFCC > NFP_SW_VERSION(6, 0, 2, 255)))
        #error "This standard library is not supported for the version of the SDK currently in use."
    #endif
#endif



#include <nfp.h>

/* For backwards compatibility */
typedef SIGNAL MEM_BULK_SIGNAL;

/** Read data from memory into transfer register.
 *
 * @param data          Xfer register(s) to store data read from memory
 * @param address       32-bit memory address to read from
 * @param count         Number of 64-bit words to read (1-16)
 * @param sync          Type of synchronization to use  (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 */
__intrinsic
void mem_read64_ptr32(
    __xread void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Read data from memory into transfer registers in indirect mode.
 *
 * @param data          Xfer register(s) to store data read from memory
 * @param address       Memory address to read from
 * @param max_nn        Maximum number of 64-bit words to read (1-16)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 */
__intrinsic
void mem_read64_ind_ptr32(
    __xread void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Read data from memory into transfer registers in indirect mode.
 *
 * @param data          Xfer register(s) to store data read from memory
 * @param address       40-bit memory address to read from
 * @param max_nn        Maximum number of 64-bit words to read (1-16)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_read64_ind_ptr40(
    __xread void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Read data from memory into transfer register.
 *
 * @param data          Xfer register(s) to store data read from memory
 * @param address       40-bit memory address to read from
 * @param count         Number of 64-bit words to read (1-16)
 * @param sync          Type of synchronization to use  (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_read64_ptr40(
    __xread void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Write data to memory from transfer registers.
 *
 * @param data          Xfer register(s) containing data to write to memory
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to write (1-16)
 * @param sync          Type of synchronization to use  (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 */
__intrinsic
void mem_write64_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Write data to memory from transfer registers.
 *
 * @param data          Xfer register(s) containing data to write to memory
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to write (1-16)
 * @param sync          Type of synchronization to use  (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write64_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif

/** Read data from memory into transfer registers (little-endian).
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address 32-bit memory address to read from
 * @param count    Number of 64-bit words to read (1-16)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_read64_le_ptr32(
    __xread void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Read data from memory into transfer registers (little-endian).
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address  40-bit memory address to read from
 * @param count    Number of 64-bit words to read (1-16)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_read64_le_ptr40(
    __xread void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Read data from memory into transfer registers in indirect mode
 * (little-endian).
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address  Memory address to read from
 * @param max_nn   Maximum number of 64-bit words to read (1-16)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_read64_le_ind_ptr32(
    __xread void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Read data from memory into transfer registers in indirect mode
 * (little-endian).
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address  40-bit memory address to read from
 * @param max_nn   Maximum number of 64-bit words to read (1-16)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_read64_le_ind_ptr40(
    __xread void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Read data from memory with byte swapping into transfer registers.
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address 32-bit memory address to read from
 * @param count    Number of 64-bit words to read (1-16)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_read64_swap_ptr32(
    __xread void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Read data from memory with byte swapping into transfer registers.
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address  40-bit memory address to read from
 * @param count    Number of 64-bit words to read (1-16)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_read64_swap_ptr40(
    __xread void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Read data from memory with byte swapping into transfer registers in indirect mode.
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address  Memory address to read from
 * @param max_nn   Maximum number of 64-bit words to read (1-16)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_read64_swap_ind_ptr32(
    __xread void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Read data from memory with byte swapping into transfer registers in indirect mode.
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address  40-bit memory address to read from
 * @param max_nn   Maximum number of 64-bit words to read (1-16)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_read64_swap_ind_ptr40(
    __xread void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Read data from memory with byte swapping into transfer registers (little-endian).
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address 32-bit memory address to read from
 * @param count    Number of 64-bit words to read (1-16)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_read64_swap_le_ptr32(
    __xread void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Read data from memory with byte swapping into transfer registers (little-endian).
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address  40-bit memory address to read from
 * @param count    Number of 64-bit words to read (1-16)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_read64_swap_le_ptr40(
    __xread void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Read data from memory with byte swapping into transfer registers in indirect mode
 * (little-endian).
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address  Memory address to read from
 * @param max_nn   Maximum number of 64-bit words to read (1-16)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_read64_swap_le_ind_ptr32(
    __xread void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Read data from memory with byte swapping into transfer registers in indirect mode
 * (little-endian).
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address  40-bit memory address to read from
 * @param max_nn   Maximum number of 64-bit words to read (1-16)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_read64_swap_le_ind_ptr40(
    __xread void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Write data to memory from transfer registers (little-endian).
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  32-bit memory address at which operation should be performed
 * @param count    Number of 64-bit words to write (1-16)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_write64_le_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Write data to memory from transfer registers (little-endian).
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param count    Number of 64-bit words to write (1-16)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write64_le_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Write data to memory from transfer registers in indirect mode
 * (little-endian).
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  Memory address at which operation should be performed
 * @param max_nn   Maximum number of 64-bit words to write (1-16)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_write64_le_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Write data to memory from transfer registers in indirect mode
 * (little-endian).
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param max_nn   Maximum number of 64-bit words to write (1-16)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write64_le_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Write data to memory from transfer registers in indirect mode.
 *
 * @param data              Xfer register(s) containing data to write to memory
 * @param address           32-bit memory address at which operation should be performed
 * @param max_nn            Maximum number of 64-bit words to write (1-16)
 * @param ind               Indirect word
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal pair to raise upon completion
 */
__intrinsic
void mem_write64_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Write data to memory from transfer registers in indirect mode.
 *
 * @param data              Xfer register(s) containing data to write to memory
 * @param address           40-bit memory address at which operation should be performed
 * @param max_nn            Maximum number of 64-bit words to write (1-16)
 * @param ind               Indirect word
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal pair to raise upon completion
 */
#ifdef __PTR40
__intrinsic
void mem_write64_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Write data to memory from transfer register in big endian (LWBE) format
 * with byte swapping.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  32-bit memory address at which operation should be performed
 * @param count    Number of 64-bit words to write (1-16)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
__intrinsic
void mem_write64_swap_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Write data to memory from transfer register in big endian (LWBE) format
 * with byte swapping.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param count    Number of 64-bit words to write (1-16)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write64_swap_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/**Write data to memory from transfer register in big endian (LWBE) format
 * with byte swapping in indirect mode.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  Memory address at which operation should be performed
 * @param max_nn   Maximum number of 64-bit words to write (1-16)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
__intrinsic
void mem_write64_swap_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/**Write data to memory from transfer register in big endian (LWBE) format
 * with byte swapping in indirect mode.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param max_nn   Maximum number of 64-bit words to write (1-16)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write64_swap_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Write data to memory from transfer register in little endian format
 * with byte swapping.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  32-bit memory address at which operation should be performed
 * @param count    Number of 64-bit words to write (1-16)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
__intrinsic
void mem_write64_swap_le_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Write data to memory from transfer register in little endian format
 * with byte swapping.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param count    Number of 64-bit words to write (1-16)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write64_swap_le_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/**Write data to memory from transfer register in little endian format
 * with byte swapping in indirect mode.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  Memory address at which operation should be performed
 * @param max_nn   Maximum number of 64-bit words to write (1-16)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
__intrinsic
void mem_write64_swap_le_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/**Write data to memory from transfer register in little endian format
 * with byte swapping in indirect mode.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param max_nn   Maximum number of 64-bit words to write (1-16)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write64_swap_le_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif




/** Write data to memory from transfer registers in bytes (big-endian).
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  32-bit memory address at which operation should be performed
 * @param count    Number of bytes to write (1-32)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
__intrinsic
void mem_write8_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Write data to memory from transfer registers in bytes (big-endian).
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param count    Number of bytes to write (1-32)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write8_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Write bytes of data to memory from transfer registers in indirect mode
 * (big-endian).
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  Memory address at which operation should be performed
 * @param max_nn   Maximum number of bytes to write (1-32)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_write8_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Write bytes of data to memory from transfer registers in indirect mode
 * (big-endian).
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param max_nn   Maximum number of bytes to write (1-32)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write8_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Write bytes of data to memory from transfer registers (little-endian).
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  32-bit memory address at which operation should be performed
 * @param count    Number of bytes to write (1-32))
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_write8_le_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Write bytes of data to memory from transfer registers (little-endian).
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param count    Number of bytes to write (1-32)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write8_le_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Write bytes of data to memory from transfer registers in indirect mode
 * (little-endian).
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  Memory address at which operation should be performed
 * @param max_nn   Maximum number of bytes to write (1-32)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_write8_le_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Write bytes of data to memory from transfer registers in indirect mode
 * (little-endian).
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param max_nn   Maximum number of bytes to write (1-32)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write8_le_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Write bytes to memory from transfer registers in big endian (LWBE) format
 * with byte swapping.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  32-bit memory address at which operation should be performed
 * @param count    Number of bytes to write (1-32)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
__intrinsic
void mem_write8_swap_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Write bytes to memory from transfer registers in big endian (LWBE) format
 * with byte swapping.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param count    Number of bytes to write (1-32)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write8_swap_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Write bytes of data to memory from transfer registers in big endian (LWBE) format
 * with byte swapping in indirect mode.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  Memory address at which operation should be performed
 * @param max_nn   Maximum number of bytes to write (1-32)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
__intrinsic
void mem_write8_swap_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Write bytes of data to memory from transfer registers in big endian (LWBE) format
 * with byte swapping in indirect mode.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param max_nn   Maximum number of bytes to write (1-32)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write8_swap_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Write bytes to memory from transfer registers in little endian format
 * with byte swapping.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  32-bit memory address at which operation should be performed
 * @param count    Number of bytes to write (1-32)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
__intrinsic
void mem_write8_swap_le_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Write bytes to memory from transfer registers in little endian format
 * with byte swapping.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param count    Number of bytes to write (1-32)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write8_swap_le_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Write bytes of data to memory from transfer registers in little endian format
 * with byte swapping in indirect mode.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  Memory address at which operation should be performed
 * @param max_nn   Maximum number of bytes to write (1-32)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
__intrinsic
void mem_write8_swap_le_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Write bytes of data to memory from transfer registers in little endian format
 * with byte swapping in indirect mode.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param max_nn   Maximum number of bytes to write (1-32)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write8_swap_le_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Read bytes of data from memory into transfer registers.
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address  32-bit memory address to read from
 * @param count    Number of bytes to read (1-32)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_read8_ptr32(
    __xread void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Read bytes of data from memory into transfer registers.
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address  40-bit memory address to read from
 * @param count    Number of bytes to read (1-32)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_read8_ptr40(
    __xread void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Read bytes of data from memory into transfer registers in indirect mode.
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address  Memory address to read from
 * @param max_nn   Maximum number of bytes to read (1-32)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
__intrinsic
void mem_read8_ind_ptr32(
    __xread void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Read bytes of data from memory into transfer registers in indirect mode.
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address  40-bit memory address to read from
 * @param max_nn   Maximum number of bytes to read (1-32)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_read8_ind_ptr40(
    __xread void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/**
 * @}
 * @name Atomic functions for MEM
 * @{
 */


/** Read data from memory into transfer registers (atomic).
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address 32-bit memory address to read from
 * @param count    Number of 32-bit words to read (1-8)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_read_atomic_ptr32(
    __xread void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Read data from memory into transfer registers (atomic).
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address  40-bit memory address to read from
 * @param count    Number of 32-bit words to read (1-8)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_read_atomic_ptr40(
    __xread void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Read data from memory into transfer registers in indirect mode (atomic).
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address  Memory address to read from
 * @param max_nn   Maximum number of 32-bit words to read (1-8)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_read_atomic_ind_ptr32(
    __xread void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Read data from memory into transfer registers in indirect mode (atomic).
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address  40-bit memory address to read from
 * @param max_nn   Maximum number of 32-bit words to read (1-8)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_read_atomic_ind_ptr40(
    __xread void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Memory compare_write.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  32-bit memory address at which operation should be performed
 * @param count    Number of 32-bit words to write (1-8)
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_ptr  Signal to raise upon completion
 *
 * Compare bottom 16 bits of the first write transfer register with the bottom 16 bits of memory location.
 * If they are equal, set the bottom 16 bits of memory to top 16 bits of the transfer register
 * and write the remaining write registers to the subsequent memory locations.
 * If the compare fails, increment the top 16 bits of memory location saturating at 0xffff.
 *
 * @note This function requires Silicon revision B0 or higher.
 *       See Errata 'MU Atomic Engine illegally sends Pull Signal for the compare_write_or_incr command and
 *       test_compare_and_write_or_incr command.'
 */
__intrinsic
void mem_compare_write_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Memory compare_write.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param count    Number of 32-bit words to write (1-8)
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_ptr  Signal to raise upon completion
 *
 * Compare bottom 16 bits of the first write transfer register with the bottom 16 bits of memory location.
 * If they are equal, set the bottom 16 bits of memory to top 16 bits of the transfer register
 * and write the remaining write registers to the subsequent memory locations.
 * If the compare fails, increment the top 16 bits of memory location saturating at 0xffff.
 *
 * @note This function requires Silicon revision B0 or higher.
 *       See Errata 'MU Atomic Engine illegally sends Pull Signal for the compare_write_or_incr command and
 *       test_compare_and_write_or_incr command.'
 */
#ifdef __PTR40
__intrinsic
void mem_compare_write_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Memory compare_write in indirect mode.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  Memory address at which operation should be performed
 * @param max_nn   Max number of 32-bit words to write (1-8)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Compare bottom 16 bits of the first write transfer register with the bottom 16 bits of memory location.
 * If they are equal, set the bottom 16 bits of memory to top 16 bits of the transfer register
 * and write the remaining write registers to the subsequent memory locations.
 * If the compare fails, increment the top 16 bits of memory location saturating at 0xffff.
 *
 * @note This function requires Silicon revision B0 or higher.
 *       See Errata 'MU Atomic Engine illegally sends Pull Signal for the compare_write_or_incr command and
 *       test_compare_and_write_or_incr command.'
 */
__intrinsic
void mem_compare_write_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );


/** Memory compare_write in indirect mode.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param max_nn   Max number of 32-bit words to write (1-8)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Compare bottom 16 bits of the first write transfer register with the bottom 16 bits of memory location.
 * If they are equal, set the bottom 16 bits of memory to top 16 bits of the transfer register
 * and write the remaining write registers to the subsequent memory locations.
 * If the compare fails, increment the top 16 bits of memory location saturating at 0xffff.
 *
 * @note This function requires Silicon revision B0 or higher.
 *       See Errata 'MU Atomic Engine illegally sends Pull Signal for the compare_write_or_incr command and
 *       test_compare_and_write_or_incr command.'
 */
#ifdef __PTR40
__intrinsic
void mem_compare_write_ind_ptr40(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Memory test_and_compare_write.
 *
 * @param val      Returned pre-modified value
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  32-bit memory address at which operation should be performed
 * @param count    Number of 32-bit words to write (1-8)
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the cmp_write instruction but it also returns a pre-modified
 * 32-bit word of the first memory location.
 * @see mem_compare_write()
 *
 * @note This function requires Silicon revision B0 or higher.
 *       See Errata 'MU Atomic Engine illegally sends Pull Signal for the compare_write_or_incr command and
 *       test_compare_and_write_or_incr command.'
 */
__intrinsic
void mem_test_and_compare_write_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );

/** Memory test_and_compare_write.
 *
 * @param val      Returned pre-modified value
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param count    Number of 32-bit words to write (1-8)
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the cmp_write instruction but it also returns a pre-modified
 * 32-bit word of the first memory location.
 * @see mem_compare_write()
 *
 * @note This function requires Silicon revision B0 or higher.
 *       See Errata 'MU Atomic Engine illegally sends Pull Signal for the compare_write_or_incr command and
 *       test_compare_and_write_or_incr command.'
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_compare_write_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Memory test_and_compare_write in indirect mode.
 *
 * @param val      Returned pre-modified value
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  Memory address at which operation should be performed
 * @param max_nn   Max number of 32-bit words to write (1-8)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the cmp_write_ind instruction but it also returns a pre-modified
 * 32-bit word of the first memory location.
 * @see mem_compare_write_ind()
 *
 * @note This function requires Silicon revision B0 or higher.
 *       See Errata 'MU Atomic Engine illegally sends Pull Signal for the compare_write_or_incr command and
 *       test_compare_and_write_or_incr command.'
 */
__intrinsic
void mem_test_and_compare_write_ind_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );


/** Memory test_and_compare_write in indirect mode.
 *
 * @param val      Returned pre-modified value
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param max_nn   Max number of 32-bit words to write (1-8)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the cmp_write_ind instruction but it also returns a pre-modified
 * 32-bit word of the first memory location.
 * @see mem_compare_write_ind()
 *
 * @note This function requires Silicon revision B0 or higher.
 *       See Errata 'MU Atomic Engine illegally sends Pull Signal for the compare_write_or_incr command and
 *       test_compare_and_write_or_incr command.'
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_compare_write_ind_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif  /* __PTR40 */


/** Write data to memory from transfer registers (atomic).
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  32-bit memory address at which operation should be performed
 * @param count    Number of 32-bit words to write (1-8)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_write_atomic_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Write data to memory from transfer registers (atomic).
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param count    Number of 32-bit words to write (1-8)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write_atomic_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Write data to memory from transfer registers in indirect mode (atomic).
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param max_nn   Maximum number of 32-bit words to write (1-8)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write_atomic_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Write data to memory from transfer registers in indirect mode (atomic).
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  32-bit memory address at which operation should be performed
 * @param max_nn   Maximum number of 32-bit words to write (1-8)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_write_atomic_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Memory swap.
 *
 * @param val      Returned pre-modified value
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  32-bit memory address at which operation should be performed
 * @param count    Number of 32-bit words to write (1-8)
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the write_atomic instruction but it also returns premodified
 * memory values in the read transfer registers.
 * @see mem_write_atomic()
 */
__intrinsic
void mem_swap_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );

/** Memory swap.
 *
 * @param val      Returned pre-modified value
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param count    Number of 32-bit words to write (1-8)
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the write_atomic instruction but it also returns premodified
 * memory values in the read transfer registers.
 * @see mem_write_atomic()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_swap_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Memory swap in indirect mode.
 *
 * @param val      Returned pre-modified value
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  Memory address at which should be performed
 * @param max_nn   Maximum number of 32-bit words to write (1-8)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the write_atomic_ind instruction but it also returns premodified
 * memory values in the read transfer registers.
 * @see mem_write_atomic_ind()
 */
__intrinsic
void mem_swap_ind_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );

/** Memory swap in indirect mode.
 *
 * @param val      Returned pre-modified value
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which should be performed
 * @param max_nn   Maximum number of 32-bit words to write (1-8)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the write_atomic_ind instruction but it also returns premodified
 * memory values in the read transfer registers.
 * @see mem_write_atomic_ind()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_swap_ind_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Write atomic immediate.
 *
 * @param data     Immediate data to swap
 * @param address  32-bit memory address at which operation should be performed
 * @param count    Number of 32-bit words to write (1-8)
 *
 * @note Valid range for data is between 0 and 0x7f for 32xx indirect format and
 *       between 0 and 0xffff for 6xxx indirect format.
 *
 * Same as the write_atomic instruction but the value written to memory
 * is specified as the immediate data.
 * @see mem_write_atomic()
 *
 */
__intrinsic
void mem_write_atomic_imm_ptr32(
    unsigned int data,
    volatile void __addr32 __mem *address,
    unsigned int count
    );

/** Write atomic immediate.
 *
 * @param data     Immediate data to swap
 * @param address  40-bit memory address at which operation should be performed
 * @param count    Number of 32-bit words to write (1-8)
 *
 * @note Valid range for data is between 0 and 0x7f for 32xx indirect format and
 *       between 0 and 0xffff for 6xxx indirect format.
 *
 * Same as the write_atomic instruction but the value written to memory
 * is specified as the immediate data.
 * @see mem_write_atomic()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write_atomic_imm_ptr40(
    unsigned int data,
    volatile void __addr40 __mem *address,
    unsigned int count
    );
#endif

/** Swap immediate.
 *
 * @param data     Immediate data to swap
 * @param rd_back  Xfer register to read back
 * @param address  32-bit memory address at which operation should be performed
 * @param count    Number of 32-bit words to write (1-8)
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_ptr  Signal to raise upon completion
 *
 *
 * Same as the swap instruction but it also returns the premodified
 * memory values in the read transfer registers.
 * @see mem_swap_ptr32()
 *
 */
__intrinsic
void mem_swap_imm_ptr32(
    unsigned int data,
    __xread void *rd_back,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Swap immediate.
 *
 * @param data     Immediate data to swap (0 - 0x7f)
 * @param rd_back  Xfer register to read back
 * @param address  40-bit memory address at which operation should be performed
 * @param count    Number of 32-bit words to write (1-8)
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_ptr  Signal to raise upon completion
 *
 *
 * Same as the swap instruction but it also returns the premodified
 * memory values in the read transfer registers.
 * @see mem_swap_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_swap_imm_ptr40(
    unsigned int data,
    __xread void *rd_back,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif

/** Set bits in memory from bits set in transfer registers.
 *
 * @param data     Data to set in Memory
 * @param address  Memory address to set to given data
 * @param count    Number of 32-bit words to set (1-8)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 * Set bits specified in write transfers registers to a number of 32-bit memory words.
 */
__intrinsic
void mem_set_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Set bits in memory from bits set in transfer registers.
 *
 * @param data     Data to set in Memory
 * @param address  40-bit memory address to set to given data
 * @param count    Number of 32-bit words to set (1-8)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 * Set bits specified in write transfers registers to a number of 32-bit memory words.
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_set_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Set bits in memory as specified by the bits set in Xfer register(s) using
 * indirect format.
 *
 * @param data     Xfer register(s) specifying the bits to be set
 * @param address  Memory address to start setting bits in
 * @param max_nn   Maximum number of 32-bit words to set (1-8)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 * The byte mask in the indirect_ref word can be used to mask the operation but
 * is usually not used as clearing bits in the transfer registers has a
 * similar outcome.
 *
 * The operation performed on each 32-bit memory location is:
 *
 * @code
 * memory = memory | data
 * @endcode
 */
__intrinsic
void mem_set_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Set bits in memory as specified by the bits set in Xfer register(s) using
 * indirect format.
 *
 * @param data     Xfer register(s) specifying the bits to be set
 * @param address  40-bit memory address to start setting bits in
 * @param max_nn   Maximum number of 32-bit words to set (1-8)
 * @param ind      Indirect word
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 * The byte mask in the indirect_ref word can be used to mask the operation but
 * is usually not used as clearing bits in the transfer registers has a
 * similar outcome.
 *
 * The operation performed on each 32-bit memory location is:
 *
 * @code
 * memory = memory | data
 * @endcode
 *
 */
#ifdef __PTR40
__intrinsic
void mem_set_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Set bits in memory from bits set in Xfer register(s) and return
 * pre-modified values in read Xfer register(s).
 *
 * @param val           Xfer register(s) returning pre-modified Memory values
 * @param data          Xfer register(s) specifying the bits to be set
 * @param address       Memory address to start setting bits in
 * @param count         Number of 32-bit words to set (1-8)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * The operation performed on each 32-bit memory location is:
 *
 * @code
 * val = memory
 * memory = memory | data
 * @endcode
 */
__intrinsic
void mem_test_and_set_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );

/** Set bits in memory from bits set in Xfer register(s) and return
 * pre-modified values in read Xfer register(s).
 *
 * @param val           Xfer register(s) returning pre-modified Memory values
 * @param data          Xfer register(s) specifying the bits to be set
 * @param address       40-bit memory address to start setting bits in
 * @param count         Number of 32-bit words to set (1-8)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * The operation performed on each 32-bit memory location is:
 *
 * @code
 * val = memory
 * memory = memory | data
 * @endcode
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_set_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Set bits in memory from bits set in Xfer register(s) and return
 * pre-modified values in read transfer register(s) using indirect format.
 *
 * @param val           Xfer register(s) returning pre-modified Memory values
 * @param data          Xfer register(s) containing the bits to be set
 * @param address       Memory address to start setting bits
 * @param max_nn        Number of 32-bit words to set (1-8)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * The operation performed on each 32-bit memory location is:
 *
 * @code
 * val = memory
 * memory = memory | data
 * @endcode
 */
__intrinsic
void mem_test_and_set_ind_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );

/** Set bits in memory from bits set in Xfer register(s) and return
 * pre-modified values in read transfer register(s) using indirect format.
 *
 * @param val           Xfer register(s) returning pre-modified Memory values
 * @param data          Xfer register(s) containing the bits to be set
 * @param address       40-bit memory address to start setting bits
 * @param max_nn        Number of 32-bit words to set (1-8)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * The operation performed on each 32-bit memory location is:
 *
 * @code
 * val = memory
 * memory = memory | data
 * @endcode
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_set_ind_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Set bits in memory from immediate 32-bit word.
 *
 * @param data          Immediate data to set in Memory
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to set (1-8)
 *
 * @note Valid range for data is between 0 and 0x7f for 32xx indirect format and
 *       between 0 and 0xffff for 6xxx indirect format.
 *
 * The operation performed on each 32-bit memory location is:
 *
 * @code
 * memory = memory | data
 * @endcode
 *
 */
__intrinsic
void mem_set_imm_ptr32(
    unsigned int data,
    volatile void __addr32 __mem *address,
    unsigned int count
    );


/** Set bits in memory from immediate 32-bit word.
 *
 * @param data          Immediate data to set in Memory
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to set (1-8)
 *
 * @note Valid range for data is between 0 and 0x7f for 32xx indirect format and
 *       between 0 and 0xffff for 6xxx indirect format.
 *
 * The operation performed on each 32-bit memory location is:
 *
 * @code
 * memory = memory | data
 * @endcode
 *
 */
#ifdef __PTR40
__intrinsic
void mem_set_imm_ptr40(
    unsigned int data,
    volatile void __addr40 __mem *address,
    unsigned int count
    );
#endif

/** Set bits in memory from bits in immediate 32-bit word and return
 * pre-modified values in read transfer register(s).
 *
 * @param data          Immediate data to set in Memory (0x0 - 0x7f)
 * @param rd_back       Xfer register(s) for read back
 * @param address       Memory address to start setting bits
 * @param count         Number of 32-bit words to set (1-8)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the set_imm instruction but it also returns the premodified
 * memory values in the read transfer registers.
 * @see mem_set_imm_ptr32()

 * The operation performed on each 32-bit memory location is:
 *
 * @code
 * rd_back = memory
 * memory = memory | data
 * @endcode
 *
 */
__intrinsic
void mem_test_and_set_imm_ptr32(
    unsigned int data,
    __xread void *rd_back,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Set bits in memory from bits in immediate 32-bit word and return
 * pre-modified values in read transfer register(s).
 *
 * @param data          Immediate data to set in Memory (0x0 - 0x7f)
 * @param rd_back       Xfer register(s) for read back
 * @param address       40-bit memory address to start setting bits
 * @param count         Number of 32-bit words to set (1-8)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the set_imm instruction but it also returns the premodified
 * memory values in the read transfer registers.
 * @see mem_set_imm_ptr32()

 * The operation performed on each 32-bit memory location is:
 *
 * @code
 * rd_back = memory
 * memory = memory | data
 * @endcode
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_set_imm_ptr40(
    unsigned int data,
    __xread void *rd_back,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif

/** Clear bits in memory as specified by the bits set in Xfer register(s).
 *
 * @param data     Xfer register(s) specifying the bits to be cleared
 * @param address  32-bit memory address to start clearing bits in
 * @param count    Number of 32-bit words to set (1-8)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 * The operation performed on each 32-bit memory location is:
 *
 * @code
 * memory = memory & ~data
 * @endcode
 *
 */
__intrinsic
void mem_clr_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Clear bits in memory as specified by the bits set in Xfer register(s).
 *
 * @param data     Xfer register(s) specifying the bits to be cleared
 * @param address  40-bit memory address to start clearing bits in
 * @param count    Number of 32-bit words to set (1-8)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 * The operation performed on each 32-bit memory location is:
 *
 * @code
 * memory = memory & ~data
 * @endcode
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_clr_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Clear bits in memory as specified by the bits set in Xfer register(s) using
 * indirect format.
 *
 * @param data      Xfer register(s) specifying the bits to be cleared
 * @param address   Memory address to start clearing bits in
 * @param max_nn    Max number of 32-bit words to clear (1-8)
 * @param ind       Indirect word
 * @param sync      Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr   Signal to raise upon completion
 *
 * The byte mask in the indirect_ref word can be used to mask the operation but
 * is usually not used as clearing bits in the transfer registers has a
 * similar outcome.
 *
 * The operation performed on each 32-bit memory location is:
 *
 * @code
 * memory = memory & ~data
 * @endcode
 *
 */
__intrinsic
void mem_clr_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Clear bits in memory as specified by the bits set in Xfer register(s) using
 * indirect format.
 *
 * @param data      Xfer register(s) specifying the bits to be cleared
 * @param address   40-bit memory address to start clearing bits in
 * @param max_nn    Max number of 32-bit words to clear (1-8)
 * @param ind       Indirect word
 * @param sync      Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr   Signal to raise upon completion
 *
 * The byte mask in the indirect_ref word can be used to mask the operation but
 * is usually not used as clearing bits in the transfer registers has a
 * similar outcome.
 *
 * The operation performed on each 32-bit memory location is:
 *
 * @code
 * memory = memory & ~data
 * @endcode
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_clr_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Memory test and clear.
 *
 * @param val           Returned pre-modified value
 * @param data          Mask of bits to clear
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to clear (1-8)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the clr instruction but it also returns the premodified memory
 * values in the read transfer registers.
 * @see mem_clr()
 *
 */
__intrinsic
void mem_test_and_clr_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );

/** Memory test and clear.
 *
 * @param val           Returned pre-modified value
 * @param data          Mask of bits to clear
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to clear (1-8)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the clr instruction but it also returns the premodified memory
 * values in the read transfer registers.
 * @see mem_clr()
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_clr_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Memory test and clear in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Mask of bits to clear
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to clear (1-8)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 */
__intrinsic
void mem_test_and_clr_ind_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );


/** Memory test and clear in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Mask of bits to clear
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to clear (1-8)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_clr_ind_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Clear bits in memory from immediate 32-bit word.
 *
 * @param data     Immediate data word specifying bits to clear in Memory
 * @param address  Memory address to start clearing bits
 * @param count    Number of 32-bit words to clear (1-8)
 *
 * @note Valid range for data is between 0 and 0x7f for 32xx indirect format and
 *       between 0 and 0xffff for 6xxx indirect format.
 *
 * Same as mem_clr() but the bit mask is specified as immediate data.
 *
 * The operation performed on each 32-bit memory location is:
 *
 * @code
 * memory = memory & ~data
 * @endcode
 *
 */
__intrinsic
void mem_clr_imm_ptr32(
    unsigned int data,
    volatile void __addr32 __mem *address,    /* address to write */
    unsigned int count                          /* number of 32-bit words to write */
    );

/** Clear bits in memory from immediate 32-bit word.
 *
 * @param data     Immediate data word specifying bits to clear in Memory
 * @param address  40-bit memory address to start clearing bits
 * @param count    Number of 32-bit words to clear (1-8)
 *
 * @note Valid range for data is between 0 and 0x7f for 32xx indirect format and
 *       between 0 and 0xffff for 6xxx indirect format.
 *
 * Same as mem_clr() but the bit mask is specified as immediate data.
 *
 * The operation performed on each 32-bit memory location is:
 *
 * @code
 * memory = memory & ~data
 * @endcode
 *
 */
#ifdef __PTR40
__intrinsic
void mem_clr_imm_ptr40(
    unsigned int data,
    volatile void __addr40 __mem *address,    /* address to write */
    unsigned int count                          /* number of 32-bit words to write */
    );
#endif

/** Clear bits in memory from bits in immediate 32-bit word and return
 * pre-modified values in read transfer register(s).
 *
 * @param data          Immediate data to clear in Memory (0x0 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to clear (1-8)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the clr_imm instruction but it also returns the premodified
 * memory values in the read transfer registers.
 * @see mem_clr_imm_ptr32()
 *
 */
__intrinsic
void mem_test_and_clr_imm_ptr32(
    unsigned int data,
    __xread void *rd_back,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Clear bits in memory from bits in immediate 32-bit word and return
 * pre-modified values in read transfer register(s).
 *
 * @param data          Immediate data to clear in Memory (0x0 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to clear (1-8)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the clr_imm instruction but it also returns the premodified
 * memory values in the read transfer registers.
 * @see mem_clr_imm_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_clr_imm_ptr40(
    unsigned int data,
    __xread void *rd_back,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif

/** Memory add32.
 *
 * @param data          Data to add
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to add (1-4)
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 */
__intrinsic
void mem_add32_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Memory add32.
 *
 * @param data          Data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to add (1-4)
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_add32_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Memory add32 in indirect mode.
 *
 * @param data          Data to add
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to add (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 */
__intrinsic
void mem_add32_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Memory add32 in indirect mode.
 *
 * @param data          Data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to add (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_add32_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Memory add64.
 *
 * @param data          Data to add
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to add (1-4)
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Add the 64-bit value(s) in the transfer registers to the data at the address.
 *
 */
__intrinsic
void mem_add64_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Memory add64.
 *
 * @param data          Data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to add (1-4)
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Add the 64-bit value(s) in the transfer registers to the data at the address.
 *
 */
#ifdef __PTR40
__intrinsic
void mem_add64_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif



/** Memory add64 in indirect mode.
 *
 * @param data          Data to add
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Max number of 64-bit words to add (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Note that length[2:2] in the indirect word has to be set to 0b1 for this 64-bit command.
 * See 6xxx databook for more information.
 *
 */
__intrinsic
void mem_add64_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Memory add64 in indirect mode.
 *
 * @param data          Data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Max number of 64-bit words to add (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Note that length[2:2] in the indirect word has to be set to 0b1 for this 64-bit command.
 * See 6xxx databook for more information.
 *
 */
#ifdef __PTR40
__intrinsic
void mem_add64_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif



/** Memory test and add32.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to add
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to add (1-4)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the add32 instruction but it also returns the premodified memory
 * values in the read transfer registers.
 * @see mem_add32()
 *
 */
__intrinsic
void mem_test_and_add32_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );

/** Memory test and add32.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to add (1-4)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the add32 instruction but it also returns the premodified memory
 * values in the read transfer registers.
 * @see mem_add32()
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_add32_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Memory test and add32 in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to add
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to add (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * @see mem_test_and_add32()
 *
 */
__intrinsic
void mem_test_and_add32_ind_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );

/** Memory test and add32 in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to add (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * @see mem_test_and_add32()
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_add32_ind_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Memory test and add64.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to add
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to write (1-4)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the add64 instruction but it also returns the premodified
 * memory values in the read transfer registers.
 * @see mem_add64()
 *
 */
__intrinsic
void mem_test_and_add64_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );

/** Memory test and add64.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to write (1-4)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the add64 instruction but it also returns the premodified
 * memory values in the read transfer registers.
 * @see mem_add64()
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_add64_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Memory test and add64 in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to add
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Max number of 64-bit words to write (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Note that length[2:2] in the indirect word has to be set to 0b1 for this 64-bit command.
 * See 6xxx databook for more information.
 *
 * @see mem_test_and_add64()
 *
 */
__intrinsic
void mem_test_and_add64_ind_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );

/** Memory test and add64 in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Max number of 64-bit words to write (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Note that length[2:2] in the indirect word has to be set to 0b1 for this 64-bit command.
 * See 6xxx databook for more information.
 *
 * @see mem_test_and_add64()
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_add64_ind_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Memory add32 immediate.
 *
 * @param data          Immediate data to add
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to write
 *
 * @note Valid range for data is between -0x80 and 0x7f for 32xx indirect format and
 *       between -0x8000 and 0x7fff for 6xxx indirect format.
 *
 * Same as the add32 instruction but the data to be added to memory is specified as
 * the immediate data and the operation is applied only to a single 32-bit memory word.
 *
 */
__intrinsic
void mem_add32_imm_ptr32(
    int data,
    volatile void __addr32 __mem *address,    /* address to write */
    unsigned int count                          /* number of 32-bit words to write */
    );

/** Memory increment32.
 *
 * @param address       32-bit memory address at which operation should be performed
 *
 * Same as add32_imm_ptr32(1,address,1) without using a signal or transfer register.
 *
 * @note: Calling this function at a high rate can stall the ME
 *
 */
__intrinsic
void mem_incr32_ptr32(
    volatile void __addr32 __mem *address     /* address to increment */
    );

/** Memory add32 immediate.
 *
 * @param data          Immediate data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to write
 *
 * @note Valid range for data is between -0x80 and 0x7f for 32xx indirect format and
 *       between -0x8000 and 0x7fff for 6xxx indirect format.
 *
 * Same as the add32 instruction but the data to be added to memory is specified as
 * the immediate data and the operation is applied only to a single 32-bit memory word.
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_add32_imm_ptr40(
    int data,
    volatile void __addr40 __mem *address,    /* address to write */
    unsigned int count                          /* number of 32-bit words to write */
    );
#endif

/** Memory increment32.
 *
 * @param address       32-bit memory address at which operation should be performed
 *
 * Same as add32_imm_ptr32(1,address,1) without using a signal or transfer register.
 *
 * @note: Calling this function at a high rate can stall the ME
 *
 *
 */
#ifdef __PTR40
__intrinsic
void mem_incr32_ptr40(
    volatile void __addr40 __mem *address /* address to increment */
    );
#endif

/** Memory test and add32 immediate.
 *
 * @param data          Immediate data to add (-0x80 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to write
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the add32_imm instruction but it also returns the premodified
 * memory value in the read transfer register.
 * @see mem_add32_imm_ptr32()
 *
 */
__intrinsic
void mem_test_and_add32_imm_ptr32(
    int data,                                           /* immediate data to add */
    __xread void *rd_back,                 /* address to read back */
    volatile void __addr32 __mem *address,   /* address to write */
    unsigned int count,                                 /* number of 32-bit words to write */
    sync_t sync,                                        /* must be sig_done */
    SIGNAL *sig_ptr                                     /* signal to raise upon completion */
    );

/** Memory test and add32 immediate.
 *
 * @param data          Immediate data to add (-0x80 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to write
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the add32_imm instruction but it also returns the premodified
 * memory value in the read transfer register.
 * @see mem_add32_imm_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_add32_imm_ptr40(
    int data,                                   /* immediate data to add */
    __xread void *rd_back,         /* address to read back */
    volatile void __addr40 __mem *address,    /* address to write */
    unsigned int count,                         /* number of 32-bit words to write */
    sync_t sync,                                /* must be sig_done */
    SIGNAL *sig_ptr                             /* signal to raise upon completion */
    );
#endif

/** Memory add64 immediate.
 *
 * @param data          Immediate data to add
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to add
 *
 * @note Valid range for data is between -0x80 and 0x7f for 32xx indirect format and
 *       between -0x8000 and 0x7fff for 6xxx indirect format.
 *
 * Same as the add64 instruction but the data to be added to memory is specified as
 * the immediate data and the operation is applied only to a single 64-bit memory word.
 *
 */
__intrinsic
void mem_add64_imm_ptr32(
    int data,
    volatile void __addr32 __mem *address,
    unsigned int count
    );

/** Memory increment64.
 *
 * @param address       32-bit memory address at which operation should be performed
 *
 * Same as add64_imm_ptr32(1,address,1) without using a signal or transfer register.
 *
 * @note: Calling this function at a high rate can stall the ME
 *
 */
__intrinsic
void mem_incr64_ptr32(
    volatile void __addr32 __mem *address /* address to increment */
    );

/** Memory add64 immediate.
 *
 * @param data          Immediate data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to add
 *
 * @note Valid range for data is between -0x80 and 0x7f for 32xx indirect format and
 *       between -0x8000 and 0x7fff for 6xxx indirect format.
 *
 * Same as the add64 instruction but the data to be added to memory is specified as
 * the immediate data and the operation is applied only to a single 64-bit memory word.
 *
 */
#ifdef __PTR40
__intrinsic
void mem_add64_imm_ptr40(
    int data,
    volatile void __addr40 __mem *address,
    unsigned int count
    );
#endif

/** Memory increment64.
 *
 * @param address       32-bit memory address at which operation should be performed
 *
 * Same as add64_imm_ptr32(1,address,1) without using a signal or transfer register.
 *
 * @note: Calling this function at a high rate can stall the ME
 *
 */
#ifdef __PTR40
__intrinsic
void mem_incr64_ptr40(
    volatile void __addr40 __mem *address /* address to increment */
    );
#endif

/** Memory test and add64 immediate.
 *
 * @param data          Immediate data to add (-0x80 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to add
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the add64_imm instruction but it also returns the premodified
 * memory values in the read transfer register.
 * @see mem_add64_imm_ptr32()
 *
 */
__intrinsic
void mem_test_and_add64_imm_ptr32(
    int data,
    __xread void *rd_back,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Memory test and add64 immediate.
 *
 * @param data          Immediate data to add (-0x80 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to add
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the add64_imm instruction but it also returns the premodified
 * memory values in the read transfer register.
 * @see mem_add64_imm_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_add64_imm_ptr40(
    int data,
    __xread void *rd_back,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif

/** Memory add32 with saturation.
 *
 * @param data          Data to add
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to write (1-4)
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Add the signed value in the transfer registers to the data at the address.
 * Addition with results of < 0 will saturate the result in the value in memory at 0x0000 0000.
 * Positive number addition resulting in a value of > 0xFFFF FFFF,
 * will saturate the result at 0xFFFF FFFF.
 *
 */
__intrinsic
void mem_add32_sat_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Memory add32 with saturation.
 *
 * @param data          Data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to write (1-4)
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Add the signed value in the transfer registers to the data at the address.
 * Addition with results of < 0 will saturate the result in the value in memory at 0x0000 0000.
 * Positive number addition resulting in a value of > 0xFFFF FFFF,
 * will saturate the result at 0xFFFF FFFF.
 *
 */
#ifdef __PTR40
__intrinsic
void mem_add32_sat_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Memory add32 with saturation in indirect mode.
 *
 * @param data          Data to add
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to write (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * @see mem_add32_sat()
 *
 */
__intrinsic
void mem_add32_sat_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Memory add32 with saturation in indirect mode.
 *
 * @param data          Data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to write (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * @see mem_add32_sat()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_add32_sat_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Memory add64 with saturation.
 *
 * @param data          Data to add
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to add (1-4)
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Add the signed 64-bit value in the transfer registers to the data at the address.
 * Addition with results of < 0 will saturate the result in the value in memory at 0x0000 0000.
 * Positive number addition resulting in a value of > 0xFFFF FFFF FFFF FFFF,
 * will saturate the result at 0xFFFF FFFF FFFF FFFF.
 *
 */
__intrinsic
void mem_add64_sat_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Memory add64 with saturation.
 *
 * @param data          Data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to add (1-4)
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Add the signed 64-bit value in the transfer registers to the data at the address.
 * Addition with results of < 0 will saturate the result in the value in memory at 0x0000 0000.
 * Positive number addition resulting in a value of > 0xFFFF FFFF FFFF FFFF,
 * will saturate the result at 0xFFFF FFFF FFFF FFFF.
 *
 */
#ifdef __PTR40
__intrinsic
void mem_add64_sat_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Memory add64 with saturation in indirect mode.
 *
 * @param data          Data to add
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Max number of 64-bit words to add (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Note that length[2:2] in the indirect word has to be set to 0b1 for this 64-bit command.
 * See 6xxx databook for more information.
 *
 * @see mem_add64_sat()
 *
 */
__intrinsic
void mem_add64_sat_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Memory add64 with saturation in indirect mode.
 *
 * @param data          Data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Max number of 64-bit words to add (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Note that length[2:2] in the indirect word has to be set to 0b1 for this 64-bit command.
 * See 6xxx databook for more information.
 *
 * @see mem_add64_sat()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_add64_sat_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Memory test and add32 with saturation.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to add
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to write (1-4)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the add32_sat instruction but it also returns the premodified
 * memory values in the read transfer registers.
 * @see mem_add32_sat_ptr32()
 *
 */
__intrinsic
void mem_test_and_add32_sat_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );


/** Memory test and add32 with saturation.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to write (1-4)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the add32_sat instruction but it also returns the premodified
 * memory values in the read transfer registers.
 * @see mem_add32_sat_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_add32_sat_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Memory test and add32 with saturation in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to add
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to add (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * @see mem_test_and_add32_sat()
 *
 */
__intrinsic
void mem_test_and_add32_sat_ind_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );

/** Memory test and add32 with saturation in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to add (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * @see mem_test_and_add32_sat()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_add32_sat_ind_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Memory test and add64 with saturation.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to add
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to add (1-4)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the add64_sat instruction but it also returns the premodified
 * memory values in the read transfer registers.
 * @see mem_add64_sat_ptr32()
 *
 */
__intrinsic
void mem_test_and_add64_sat_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );

/** Memory test and add64 with saturation.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to add (1-4)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the add64_sat instruction but it also returns the premodified
 * memory values in the read transfer registers.
 * @see mem_add64_sat_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_add64_sat_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Memory test and add64 with saturation in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to add
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Max number of 64-bit words to add (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Note that length[2:2] in the indirect word has to be set to 0b1 for this 64-bit command.
 * See 6xxx databook for more information.
 *
 * @see mem_test_and_add64_sat()
 *
 */
__intrinsic
void mem_test_and_add64_sat_ind_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );

/** Memory test and add64 with saturation in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Max number of 64-bit words to add (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Note that length[2:2] in the indirect word has to be set to 0b1 for this 64-bit command.
 * See 6xxx databook for more information.
 *
 * @see mem_test_and_add64_sat()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_add64_sat_ind_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif



/** Memory add32 immediate with saturation.
 *
 * @param data          Immediate data to add
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to add
 *
 * @note Valid range for data is between -0x80 and 0x7f for 32xx indirect format and
 *       between -0x8000 and 0x7fff for 6xxx indirect format.
 *
 * Same as the add32_sat instruction but the data to be added to memory is specified
 * as the immediate data and the operation is applied only to a single 32-bit memory word.
 * @see mem_add32_sat_ptr32()
 *
 */
__intrinsic
void mem_add32_imm_sat_ptr32(
    int data,
    volatile void __addr32 __mem *address,
    unsigned int count
    );


/** Memory add32 immediate with saturation.
 *
 * @param data          Immediate data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to add
 *
 * @note Valid range for data is between -0x80 and 0x7f for 32xx indirect format and
 *       between -0x8000 and 0x7fff for 6xxx indirect format.
 *
 * Same as the add32_sat instruction but the data to be added to memory is specified
 * as the immediate data and the operation is applied only to a single 32-bit memory word.
 * @see mem_add32_sat_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_add32_imm_sat_ptr40(
    int data,
    volatile void __addr40 __mem *address,
    unsigned int count
    );
#endif

/** Memory test and add32 immediate with saturation.
 *
 * @param data          Immediate data to add (-0x80 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to add
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the add32_imm_sat instruction but it also returns the premodified
 * memory values in the read transfer register.
 * @see mem_add32_imm_sat_ptr32()
 *
 */
__intrinsic
void mem_test_and_add32_imm_sat_ptr32(
    int data,
    __xread void *rd_back,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Memory test and add32 immediate with saturation.
 *
 * @param data          Immediate data to add (-0x80 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to add
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the add32_imm_sat instruction but it also returns the premodified
 * memory values in the read transfer register.
 * @see mem_add32_imm_sat_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_add32_imm_sat_ptr40(
    int data,
    __xread void *rd_back,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif

/** Memory add64 immediate with saturation.
 *
 * @param data          Immediate data to add
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to add
 *
 * @note Valid range for data is between -0x80 and 0x7f for 32xx indirect format and
 *       between -0x8000 and 0x7fff for 6xxx indirect format.
 *
 * Same as the add64_sat instruction but the data to be added to memory
 * is specified as the immediate data and the operation is applied only to
 * a single 64-bit memory word.
 * @see mem_add64_sat_ptr32()
 *
 */
__intrinsic
void mem_add64_imm_sat_ptr32(
    int data,
    volatile void __addr32 __mem *address,
    unsigned int count
    );

/** Memory add64 immediate with saturation.
 *
 * @param data          Immediate data to add
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to add
 *
 * @note Valid range for data is between -0x80 and 0x7f for 32xx indirect format and
 *       between -0x8000 and 0x7fff for 6xxx indirect format.
 *
 * Same as the add64_sat instruction but the data to be added to memory
 * is specified as the immediate data and the operation is applied only to
 * a single 64-bit memory word.
 * @see mem_add64_sat_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_add64_imm_sat_ptr40(
    int data,
    volatile void __addr40 __mem *address,
    unsigned int count
    );
#endif

/** Memory test and add64 immediate with saturation.
 *
 * @param data          Immediate data to add (-0x80 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to add
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the add64_imm instruction but it also returns the premodified
 * memory values in the read transfer register.
 * @see mem_add64_imm_ptr32()
 *
 */
__intrinsic
void mem_test_and_add64_imm_sat_ptr32(
    int data,
    __xread void *rd_back,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Memory test and add64 immediate with saturation.
 *
 * @param data          Immediate data to add (-0x80 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to add
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the add64_imm instruction but it also returns the premodified
 * memory values in the read transfer register.
 * @see mem_add64_imm_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_add64_imm_sat_ptr40(
    int data,
    __xread void *rd_back,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif

/** Memory sub32.
 *
 * @param data          Data to subtract
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to subtract (1-4)
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * @note Valid range for data is between -0x80 and 0x7f for 32xx indirect format and
 *       between -0x8000 and 0x7fff for 6xxx indirect format.
 *
 * Subtract the 2s complement value in the transfer registers from the data
 * at the address, which is treated as an unsigned number.
 *
 */
__intrinsic
void mem_sub32_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Memory sub32.
 *
 * @param data          Data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to subtract (1-4)
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Subtract the 2s complement value in the transfer registers from the data
 * at the address, which is treated as an unsigned number.
 *
 */
#ifdef __PTR40
__intrinsic
void mem_sub32_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Memory sub32 in indirect mode.
 *
 * @param data          Data to subtract
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to subtract (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * @see mem_sub32()
 *
 */
__intrinsic
void mem_sub32_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Memory sub32 in indirect mode.
 *
 * @param data          Data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to subtract (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * @see mem_sub32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_sub32_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Memory sub64.
 *
 * @param data          Data to subtract
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to subtract (1-4)
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Subtract the value in the transfer registers from the data at the address.
 *
 */
__intrinsic
void mem_sub64_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Memory sub64.
 *
 * @param data          Data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to subtract (1-4)
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Subtract the value in the transfer registers from the data at the address.
 *
 */
#ifdef __PTR40
__intrinsic
void mem_sub64_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Memory sub64 in indirect mode.
 *
 * @param data          Data to subtract
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Max number of 64-bit words to subtract (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Note that length[2:2] in the indirect word has to be set to 0b1 for this 64-bit command.
 * See 6xxx databook for more information.
 *
 * @see mem_sub64()
 *
 */
__intrinsic
void mem_sub64_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Memory sub64 in indirect mode.
 *
 * @param data          Data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Max number of 64-bit words to subtract (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Note that length[2:2] in the indirect word has to be set to 0b1 for this 64-bit command.
 * See 6xxx databook for more information.
 *
 * @see mem_sub64()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_sub64_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Memory test and sub32.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to subtract
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to subtract (1-4)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the sub32 instruction but it also returns the premodified memory
 * values in the read transfer registers.
 * @see mem_sub32()
 *
 */
__intrinsic
void mem_test_and_sub32_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );


/** Memory test and sub32.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to subtract (1-4)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the sub32 instruction but it also returns the premodified memory
 * values in the read transfer registers.
 * @see mem_sub32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_sub32_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Memory test and sub32 in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to subtract
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to subtract (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * @see mem_test_and_sub32()
 *
 */
__intrinsic
void mem_test_and_sub32_ind_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );


/** Memory test and sub32 in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to subtract (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * @see mem_test_and_sub32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_sub32_ind_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Memory test and sub64.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to subtract
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to subtract (1-4)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the sub64 instruction but it also returns the premodified memory
 * values in the read transfer registers.
 * @see mem_sub64()
 *
 */
__intrinsic
void mem_test_and_sub64_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );


/** Memory test and sub64.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to subtract (1-4)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the sub64 instruction but it also returns the premodified memory
 * values in the read transfer registers.
 * @see mem_sub64()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_sub64_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Memory test and sub64 in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to subtract
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Max number of 64-bit words to subtract (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Note that length[2:2] in the indirect word has to be set to 0b1 for this 64-bit command.
 * See 6xxx databook for more information.
 *
 * @see mem_test_and_sub64()
 *
 */
__intrinsic
void mem_test_and_sub64_ind_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
);


/** Memory test and sub64 in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Max number of 64-bit words to subtract (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Note that length[2:2] in the indirect word has to be set to 0b1 for this 64-bit command.
 * See 6xxx databook for more information.
 *
 * @see mem_test_and_sub64()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_sub64_ind_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
);
#endif


/** Memory sub32 immediate.
 *
 * @param data          Immediate data to subtract
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to subtract
 *
 * @note Valid range for data is between -0x80 and 0x7f for 32xx indirect format and
 *       between -0x8000 and 0x7fff for 6xxx indirect format.
 *
 * Same as the sub32 instruction but the data to be subtracted to memory is specified as
 * the immediate data and the operation is applied only to a single 32-bit memory word.
 *
 */
__intrinsic
void mem_sub32_imm_ptr32(
    int data,
    volatile void __addr32 __mem *address,
    unsigned int count
    );

/** Memory decrement32.
 *
 * @param address       32-bit memory address at which operation should be performed
 *
 * Same as sub32_imm_ptr32(1,address,1) without using a signal or transfer register.
 *
 * @note: Calling this function at a high rate can stall the ME
 *
 */
__intrinsic
void mem_decr32_ptr32(
    volatile void __addr32 __mem *address     /* address to decrement */
    );

/** Memory sub32 immediate.
 *
 * @param data          Immediate data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to subtract
 *
 * @note Valid range for data is between -0x80 and 0x7f for 32xx indirect format and
 *       between -0x8000 and 0x7fff for 6xxx indirect format.
 *
 * Same as the sub32 instruction but the data to be subtracted to memory is specified as
 * the immediate data and the operation is applied only to a single 32-bit memory word.
 *
 */
#ifdef __PTR40
__intrinsic
void mem_sub32_imm_ptr40(
    int data,
    volatile void __addr40 __mem *address,
    unsigned int count
    );
#endif

/** Memory decrement32.
 *
 * @param address       32-bit memory address at which operation should be performed
 *
 * Same as sub32_imm_ptr32(1,address,1) without using a signal or transfer register.
 *
 * @note: Calling this function at a high rate can stall the ME
 *
 */
#ifdef __PTR40
__intrinsic
void mem_decr32_ptr40(
    volatile void __addr40 __mem *address     /* address to decrement */
    );
#endif

/** Memory test and sub32 immediate.
 *
 * @param data          Immediate data to subtract (-0x80 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to subtract
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the sub32_imm instruction but it also returns the premodified
 * memory values in the read transfer register.
 * @see mem_sub32_imm_ptr32()
 *
 */
__intrinsic
void mem_test_and_sub32_imm_ptr32(
    int data,
    __xread void *rd_back,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Memory test and sub32 immediate.
 *
 * @param data          Immediate data to subtract (-0x80 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to subtract
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the sub32_imm instruction but it also returns the premodified
 * memory values in the read transfer register.
 * @see mem_sub32_imm_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_sub32_imm_ptr40(
    int data,
    __xread void *rd_back,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif

/** Memory sub64 immediate.
 *
 * @param data          Immediate data to subtract
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to subtract
 *
 * @note Valid range for data is between -0x80 and 0x7f for 32xx indirect format and
 *       between -0x8000 and 0x7fff for 6xxx indirect format.
 *
 * Same as the sub64 instruction but the data to be subtracted from memory is
 * specified as the immediate data.
 *
 */
__intrinsic
void mem_sub64_imm_ptr32(
    int data,
    volatile void __addr32 __mem *address,
    unsigned int count
    );

/** Memory decrement64.
 *
 * @param address       32-bit memory address at which operation should be performed
 *
 * Same as sub64_imm_ptr32(1,address,1) without using a signal or transfer register.
 *
 * @note: Calling this function at a high rate can stall the ME
 *
 */
__intrinsic
void mem_decr64_ptr32(
    volatile void __addr32 __mem *address     /* address to decrement */
    );

/** Memory sub64 immediate.
 *
 * @param data          Immediate data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to subtract
 *
 * @note Valid range for data is between -0x80 and 0x7f for 32xx indirect format and
 *       between -0x8000 and 0x7fff for 6xxx indirect format.
 *
 * Same as the sub64 instruction but the data to be subtracted from memory is
 * specified as the immediate data.
 *
 */
#ifdef __PTR40
__intrinsic
void mem_sub64_imm_ptr40(
    int data,
    volatile void __addr40 __mem *address,
    unsigned int count
    );
#endif

/** Memory decrement64.
 *
 * @param address       32-bit memory address at which operation should be performed
 *
 * Same as sub64_imm_ptr32(1,address,1) without using a signal or transfer register.
 *
 * @note: Calling this function at a high rate can stall the ME
 *
 */
#ifdef __PTR40
__intrinsic
void mem_decr64_ptr40(
    volatile void __addr40 __mem *address     /* address to decrement */
    );
#endif

/** Memory test and sub64 immediate.
 *
 * @param data          Immediate data to subtract (-0x80 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to subtract
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the sub64_imm instruction but it also returns the premodified
 * memory values in the read transfer register.
 * @see mem_sub64_imm_ptr32()
 *
 */
__intrinsic
void mem_test_and_sub64_imm_ptr32(
    int data,
    __xread void *rd_back,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Memory test and sub64 immediate.
 *
 * @param data          Immediate data to subtract (-0x80 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to subtract
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the sub64_imm instruction but it also returns the premodified
 * memory values in the read transfer register.
 * @see mem_sub64_imm_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_sub64_imm_ptr40(
    int data,
    __xread void *rd_back,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif

/** Memory sub32 with saturation.
 *
 * @param data          Data to subtract
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to subtract (1-4)
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Subtract the signed value in the transfer registers from the data at the address.
 * Subtraction with results of < 0 will saturate the result in the
 * value in memory at 0x0000 0000.
 *
 */
__intrinsic
void mem_sub32_sat_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Memory sub32 with saturation.
 *
 * @param data          Data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to subtract (1-4)
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Subtract the signed value in the transfer registers from the data at the address.
 * Subtraction with results of < 0 will saturate the result in the
 * value in memory at 0x0000 0000.
 *
 */
#ifdef __PTR40
__intrinsic
void mem_sub32_sat_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Memory sub32 with saturation in indirect mode.
 *
 * @param data          Data to subtract
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to subtract (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * @see mem_sub32_sat()
 *
 */
__intrinsic
void mem_sub32_sat_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Memory sub32 with saturation in indirect mode.
 *
 * @param data          Data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to subtract (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * @see mem_sub32_sat()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_sub32_sat_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Memory sub64 with saturation.
 *
 * @param data          Data to subtract
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to subtract (1-4)
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Subtract the signed 64-bit value in the transfer registers from the data at the address.
 * Subtraction with results of < 0 will saturate the result
 * in the value in memory at 0x0000 0000.
 *
 */
__intrinsic
void mem_sub64_sat_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Memory sub64 with saturation.
 *
 * @param data          Data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to subtract (1-4)
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Subtract the signed 64-bit value in the transfer registers from the data at the address.
 * Subtraction with results of < 0 will saturate the result
 * in the value in memory at 0x0000 0000.
 *
 */
#ifdef __PTR40
__intrinsic
void mem_sub64_sat_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Memory sub64 with saturation in indirect mode.
 *
 * @param data          Data to subtract
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Max number of 64-bit words to subtract (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Note that length[2:2] in the indirect word has to be set to 0b1 for this 64-bit command.
 * See 6xxx databook for more information.
 *
 * @see mem_sub64_sat()
 *
 */
__intrinsic
void mem_sub64_sat_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Memory sub64 with saturation in indirect mode.
 *
 * @param data          Data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Max number of 64-bit words to subtract (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Note that length[2:2] in the indirect word has to be set to 0b1 for this 64-bit command.
 * See 6xxx databook for more information.
 *
 * @see mem_sub64_sat()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_sub64_sat_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Memory test and sub32 with saturation.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to subtract
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to subtract (1-4)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the sub32_sat instruction but it also returns the premodified
 * memory values in the read transfer registers.
 * @see mem_sub32_sat_ptr32()
 *
 */
__intrinsic
void mem_test_and_sub32_sat_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );


/** Memory test and sub32 with saturation.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to subtract (1-4)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the sub32_sat instruction but it also returns the premodified
 * memory values in the read transfer registers.
 * @see mem_sub32_sat_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_sub32_sat_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Memory test and sub32 with saturation in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to subtract
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to subtract (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * @see mem_test_and_sub32_sat()
 *
 */
__intrinsic
void mem_test_and_sub32_sat_ind_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );


/** Memory test and sub32 with saturation in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to subtract (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * @see mem_test_and_sub32_sat()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_sub32_sat_ind_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Memory test and sub64 with saturation.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to subtract
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to subtract (1-4)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the sub64_sat instruction but it also returns the premodified
 * memory values in the read transfer registers.
 * @see mem_sub64_sat_ptr32()
 *
 */
__intrinsic
void mem_test_and_sub64_sat_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );


/** Memory test and sub64 with saturation.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to subtract (1-4)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the sub64_sat instruction but it also returns the premodified
 * memory values in the read transfer registers.
 * @see mem_sub64_sat_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_sub64_sat_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Memory test and sub64 with saturation in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to subtract
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Max number of 64-bit words to subtract (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Note that length[2:2] in the indirect word has to be set to 0b1 for this 64-bit command.
 * See 6xxx databook for more information.
 *
 * @see mem_test_and_sub64_sat()
 *
 */
__intrinsic
void mem_test_and_sub64_sat_ind_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );


/** Memory test and sub64 with saturation in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Max number of 64-bit words to subtract (1-4)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Note that length[2:2] in the indirect word has to be set to 0b1 for this 64-bit command.
 * See 6xxx databook for more information.
 *
 * @see mem_test_and_sub64_sat()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_sub64_sat_ind_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Memory sub32 immediate with saturation.
 *
 * @param data          Immediate data to subtract
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to subtract
 *
 * Same as the sub32_sat instruction, but the data to be subtracted from memory is specified as
 * the immediate data and the operation is applied only to a single 32-bit memory word.
 * @see mem_sub32_sat_ptr32()
 *
 */
__intrinsic
void mem_sub32_imm_sat_ptr32(
    int data,
    volatile void __addr32 __mem *address,
    unsigned int count
    );


/** Memory sub32 immediate with saturation.
 *
 * @param data          Immediate data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to subtract
 *
 * Same as the sub32_sat instruction, but the data to be subtracted from memory is specified as
 * the immediate data and the operation is applied only to a single 32-bit memory word.
 * @see mem_sub32_sat_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_sub32_imm_sat_ptr40(
    int data,
    volatile void __addr40 __mem *address,
    unsigned int count
    );
#endif

/** Memory test and sub32 immediate with saturation.
 *
 * @param data          Immediate data to subtract (-0x80 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to subtract
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the sub32_imm_sat instruction but it also returns the premodified
 * memory values in the read transfer register.
 * @see mem_sub32_imm_sat_ptr32()
 *
 */
__intrinsic
void mem_test_and_sub32_imm_sat_ptr32(
    int data,
    __xread void *rd_back,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Memory test and sub32 immediate with saturation.
 *
 * @param data          Immediate data to subtract (-0x80 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to subtract
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the sub32_imm_sat instruction but it also returns the premodified
 * memory values in the read transfer register.
 * @see mem_sub32_imm_sat_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_sub32_imm_sat_ptr40(
    int data,
    __xread void *rd_back,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif

/** Memory sub64 immediate with saturation.
 *
 * @param data          Immediate data to subtract
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to subtract
 *
 * @note Valid range for data is between -0x80 and 0x7f for 32xx indirect format and
 *       between -0x8000 and 0x7fff for 6xxx indirect format.
 *
 * Same as the sub64_sat instruction but the data to be subtracted from memory
 * is specified as the immediate data.
 * @see mem_sub64_sat_ptr32()
 *
 */
__intrinsic
void mem_sub64_imm_sat_ptr32(
    int data,
    volatile void __addr32 __mem *address,
    unsigned int count
    );

/** Memory sub64 immediate with saturation.
 *
 * @param data          Immediate data to subtract
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to subtract
 *
 * @note Valid range for data is between -0x80 and 0x7f for 32xx indirect format and
 *       between -0x8000 and 0x7fff for 6xxx indirect format.
 *
 * Same as the sub64_sat instruction but the data to be subtracted from memory
 * is specified as the immediate data.
 * @see mem_sub64_sat_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_sub64_imm_sat_ptr40(
    int data,
    volatile void __addr40 __mem *address,
    unsigned int count
    );
#endif

/** Memory test and sub64 immediate with saturation.
 *
 * @param data          Immediate data to subtract (-0x80 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to subtract
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the sub64_imm_sat instruction but it also returns the
 * premodified memory values in the read transfer register.
 * @see mem_sub64_imm_sat_ptr32()
 *
 */
__intrinsic
void mem_test_and_sub64_imm_sat_ptr32(
    int data,
    __xread void *rd_back,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Memory test and sub64 immediate with saturation.
 *
 * @param data          Immediate data to subtract (-0x80 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 64-bit words to subtract
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the sub64_imm_sat instruction but it also returns the
 * premodified memory values in the read transfer register.
 * @see mem_sub64_imm_sat_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_sub64_imm_sat_ptr40(
    int data,
    __xread void *rd_back,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif

/** XOR in Memory from transfer registers.
 *
 * @param data     Data (byte mask) to xor in Memory
 * @param address 32-bit memory address to xor to given data
 * @param count    Number of 32-bit words to XOR (1-8)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 * Do an exclusive OR operation between write transfer registers and a number of 32-bit memory words.
 * A byte mask specifies which memory bytes are affected for all memory words.
 *
 */
__intrinsic
void mem_xor_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** XOR in Memory from transfer registers.
 *
 * @param data     Data (byte mask) to xor in Memory
 * @param address  40-bit memory address to xor to given data
 * @param count    Number of 32-bit words to XOR (1-8)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 * Do an exclusive OR operation between write transfer registers and a number of 32-bit memory words.
 * A byte mask specifies which memory bytes are affected for all memory words.
 *
 */
#ifdef __PTR40
__intrinsic
void mem_xor_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** XOR in Memory from transfer registers in indirect mode.
 *
 * @param data      Data (byte mask) to xor in Memory
 * @param address   Memory address to xor to given data
 * @param max_nn    Max number of 32-bit words to XOR (1-8)
 * @param ind       Indirect word
 * @param sync      Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr   Signal to raise upon completion
 *
 * @see mem_xor()
 *
 */
__intrinsic
void mem_xor_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** XOR in Memory from transfer registers in indirect mode.
 *
 * @param data      Data (byte mask) to xor in Memory
 * @param address   40-bit memory address to xor to given data
 * @param max_nn    Max number of 32-bit words to XOR (1-8)
 * @param ind       Indirect word
 * @param sync      Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr   Signal to raise upon completion
 *
 * @see mem_xor()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_xor_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** XOR data in Memory from transfer registers and return pre-modified value
 * in transfer register.
 *
 * @param val           Returned pre-modified value
 * @param data          Data (byte mask) to xor in Memory
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to XOR (1-8)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the xor instruction but it also returns the premodified memory
 * values to the read transfer registers.
 * @see mem_xor_ptr32()
 *
 */
__intrinsic
void mem_test_and_xor_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );


/** XOR data in Memory from transfer registers and return pre-modified value
 * in transfer register.
 *
 * @param val           Returned pre-modified value
 * @param data          Data (byte mask) to xor in Memory
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to XOR (1-8)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the xor instruction but it also returns the premodified memory
 * values to the read transfer registers.
 * @see mem_xor_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_xor_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** XOR data into Memory from transfer registers and return pre-modified value
 * in transfer register in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to XOR into Memory
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to XOR (1-8)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * @see mem_test_and_xor()
 *
 */
__intrinsic
void mem_test_and_xor_ind_ptr32(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );


/** XOR data into Memory from transfer registers and return pre-modified value
 * in transfer register in indirect mode.
 *
 * @param val           Returned pre-modified value
 * @param data          Data to XOR into Memory
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Max number of 32-bit words to XOR (1-8)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * @see mem_test_and_xor()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_xor_ind_ptr40(
    __xread unsigned int *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Memory XOR immediate.
 *
 * @param data     Immediate data to xor in Memory (0x0 - 0x7f)
 * @param address  32-bit memory address to xor to given data
 * @param count    Number of 32-bit words to set (1-8)
 *
 * Same as the xor instruction but the bit mask is specified as the immediate data.
 * @see mem_xor_ptr32()
 *
 */
__intrinsic
void mem_xor_imm_ptr32(
    unsigned int data,
    volatile void __addr32 __mem *address,
    unsigned int count
    );


/** Memory XOR immediate.
 *
 * @param data     Immediate data to xor in Memory (0x0 - 0x7f)
 * @param address  40-bit memory address to xor to given data
 * @param count    Number of 32-bit words to set (1-8)
 *
 * Same as the xor instruction but the bit mask is specified as the immediate data.
 * @see mem_xor_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_xor_imm_ptr40(
    unsigned int data,
    volatile void __addr40 __mem *address,
    unsigned int count
    );
#endif

/** Memory test and xor immediate.
 *
 * @param data          Immediate data to xor in Memory (0x0 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to xor (1-8)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the xor_imm instruction but it also returns the premodified
 * memory values in the read transfer registers.
 * @see mem_xor_imm_ptr32()
 *
 */
__intrinsic
void mem_test_and_xor_imm_ptr32(
    unsigned int data,
    __xread void *rd_back,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Memory test and xor immediate.
 *
 * @param data          Immediate data to xor in Memory (0x0 - 0x7f)
 * @param rd_back       Xfer register to read back
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to xor (1-8)
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal to raise upon completion
 *
 * Same as the xor_imm instruction but it also returns the premodified
 * memory values in the read transfer registers.
 * @see mem_xor_imm_ptr32()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_and_xor_imm_ptr40(
    unsigned int data,
    __xread void *rd_back,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif



/** Memory mask compare write
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  32-bit memory address at which operation should be performed
 * @param mask     4-bit mask of which 4 bytes to compare
 * @param count    Number of 32-bit words to write (1-8)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 * This command takes memory data (32-bits at a time) and data in xfer registers and it compares
 * the four bytes for equality. If the bytes in the memory and data indicated by the byte mask are equal,
 * then the whole data word overwrites the memory.
 * For example, if the byte mask is 4b1000, then the memory is overwritten ONLY if the bits [8;24] of the
 * memory and the pull data are equal. If the byte mask were 4b0110, then the middle two bytes (i.e. bits [16;8]) of
 * the memory and pull data would have to be equal for the memory to be overwritten.
 *
 */
__intrinsic
void mem_mask_compare_write_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int mask,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Memory mask compare write
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40 bit memory address at which operation should be performed
 * @param mask     4-bit mask of which 4 bytes to compare, 0x0 and 0xf is not allowed
 * @param count    Number of 32-bit words to write (1-8)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 * This command takes memory data (32-bits at a time) and data in xfer registers and it compares
 * the four bytes for equality. If the bytes in the memory and data indicated by the byte mask are equal,
 * then the whole data word overwrites the memory.
 * For example, if the byte mask is 4b1000, then the memory is overwritten ONLY if the bits [8;24] of the
 * memory and the pull data are equal. If the byte mask were 4b0110, then the middle two bytes (i.e. bits [16;8]) of
 * the memory and pull data would have to be equal for the memory to be overwritten.
 *
 */
#ifdef __PTR40
__intrinsic
void mem_mask_compare_write_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int mask,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif

/**  Memory compare write using mask to compare.
 *
 * @param val      Returned pre-modified value
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  32-bit memory address at which operation should be performed
 * @param mask     4-bit mask of which 4 bytes to compare, 0x0 and 0xf is not allowed
 * @param count    Number of 32-bit words to write (1-8)
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the mem_mask_compare_write instruction but it also returns a pre-modified
 * 32-bit word of the first memory location.
 * @see mem_mask_compare_write()
 *
 */
__intrinsic
void mem_test_mask_and_compare_write_ptr32(
    __xread void *val,
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int mask,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );

/** Memory compare write using mask to compare.
 *
 * @param val      Returned pre-modified value
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param mask     4-bit mask of which 4 bytes to compare, 0x0 and 0xf is not allowed
 * @param count    Number of 32-bit words to write (1-8)
 * @param sync     Type of synchronization to use (must be sig_done)
 * @param sig_pair_ptr  Signal pair to raise upon completion
 *
 * Same as the mem_mask_compare_write instruction but it also returns a pre-modified
 * 32-bit word of the first memory location.
 * @see mem_mask_compare_write_ptr40()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_test_mask_and_compare_write_ptr40(
    __xread void *val,
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int mask,
    unsigned int count,
    sync_t sync,
    SIGNAL_PAIR *sig_pair_ptr
    );
#endif


/** Write data to memory from transfer registers.
 *
 * @param data          Xfer register(s) containing data to write to memory
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to write (1-32)
 * @param sync          Type of synchronization to use  (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 */
__intrinsic
void mem_write32_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Write data to memory from transfer registers.
 *
 * @param data          Xfer register(s) containing data to write to memory
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32bit words to write (1-32)
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write32_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Write 32-bit data to memory from transfer register with indirect mode and ptr32 addressing.
 *
 * @param data          Xfer register(s) containing data to write to memory
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Number of 32bit words to write (1-32)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal pair to raise upon completion
 *
 * @see mem_write32_ptr32()
 *
 */
__intrinsic
void mem_write32_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Write 32-bit data to memory from transfer register with indirect mode and ptr40 addressing
 *
 * @param data          Xfer register(s) containing data to write to memory
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Number of 32bit words to write (1-32)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal pair to raise upon completion
 *
 * @see mem_write32_ptr40()
 *
 */
#ifdef __PTR40
__intrinsic
 void mem_write32_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Write 32-bit data to memory from transfer register with byte swapping, indirect mode and ptr32 addressing.
 *
 * @param data          Xfer register(s) containing data to write to memory
 * @param address       Memory address at which operation should be performed
 * @param max_nn        Number of 32bit words to write (1-32)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal pair to raise upon completion
 *
 * @see mem_write32_swap_ptr32()
 *
 */
__intrinsic
void mem_write32_swap_ind_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Write 32-bit data to memory from transfer register with byte swapping, indirect mode and ptr40 addressing
 *
 * @param data          Xfer register(s) containing data to write to memory
 * @param address       40-bit memory address at which operation should be performed
 * @param max_nn        Number of 32bit words to write (1-32)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use (must be sig_done)
 * @param sig_ptr       Signal pair to raise upon completion
 *
 * @see mem_write32_swap_ptr40()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write32_swap_ind_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Write data to memory from transfer registers (little-endian).
 *
 * @param data          Xfer register(s) containing data to write to memory
 * @param address       32-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to write (1-32)
 * @param sync          Type of synchronization to use  (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 */
__intrinsic
void mem_write32_le_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Write data to memory from transfer registers (little-endian).
 *
 * @param data          Xfer register(s) containing data to write to memory
 * @param address       40-bit memory address at which operation should be performed
 * @param count         Number of 32-bit words to write (1-32)
 * @param sync          Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write32_le_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif



/** Read data from memory into transfer register.
 *
 * @param data          Xfer register(s) to store data read from memory
 * @param address       32-bit memory address to read from
 * @param count         Number of 32-bit words to read (1-32)
 * @param sync          Type of synchronization to use  (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 */
__intrinsic
void mem_read32_ptr32(
    __xread void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Read data from memory into transfer register.
 *
 * @param data          Xfer register(s) to store data read from memory
 * @param address       40-bit memory address to read from
 * @param count         Number of 32-bit words to read (1-32)
 * @param sync          Type of synchronization to use  (sig_done or ctx_swap)
 * @param sig_ptr       Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_read32_ptr40(
    __xread void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Read 32-bit data from memory into transfer register with indirect mode and ptr32 addressing.
 *
 * @param data          Xfer register(s) to store data read from memory
 * @param address       32-bit memory address to read from
 * @param max_nn        Number of 32-bit words to read (1-32)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use  (sig_done or ctx_swap)
 * @param sig_ptr       Signal pair to raise upon completion
 *
 * @see mem_read32_ptr32()
 *
 */
__intrinsic
 void mem_read32_ind_ptr32(
    __xread void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Read 32-bit data from memory into transfer register with indirect mode and ptr40 addressing
 *
 * @param data          Xfer register(s) to store data read from memory
 * @param address       40-bit memory address to read from
 * @param max_nn        Number of 32-bit words to read (1-32)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use  (sig_done or ctx_swap)
 * @param sig_ptr       Signal pair to raise upon completion
 *
 * @see mem_read32_ptr40()
 *
 */
#ifdef __PTR40
__intrinsic
 void mem_read32_ind_ptr40(
    __xread void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Read data from memory into transfer registers (little-endian).
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address 32-bit memory address to read from
 * @param count    Number of 32-bit words to read (1-32)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_read32_le_ptr32(
    __xread void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Read data from memory into transfer registers (little-endian).
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address  40-bit memory address to read from
 * @param count    Number of 32-bit words to read (1-32)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_read32_le_ptr40(
    __xread void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif



/** Read data from memory with byte swapping into transfer registers.
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address 32-bit memory address to read from
 * @param count    Number of 32-bit words to read (1-32)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_read32_swap_ptr32(
    __xread void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Read data from memory with byte swapping into transfer registers.
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address  40-bit memory address to read from
 * @param count    Number of 32-bit words to read (1-32)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_read32_swap_ptr40(
    __xread void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Read 32-bit data from memory into transfer register with byte swapping, indirect mode and ptr32 addressing.
 *
 * @param data          Xfer register(s) to store data read from memory
 * @param address       32-bit memory address to read from
 * @param max_nn        Number of 32-bit words to read (1-32)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use  (sig_done or ctx_swap)
 * @param sig_ptr       Signal pair to raise upon completion
 *
 * @see mem_read32_swap_ptr32()
 *
 */
__intrinsic
void mem_read32_swap_ind_ptr32(
    __xread void *data,
    volatile void __addr32 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );


/** Read 32-bit data from memory into transfer register with byte swapping, indirect mode and ptr40 addressing
 *
 * @param data          Xfer register(s) to store data read from memory
 * @param address       40-bit memory address to read from
 * @param max_nn        Number of 32-bit words to read (1-32)
 * @param ind           Indirect word
 * @param sync          Type of synchronization to use  (sig_done or ctx_swap)
 * @param sig_ptr       Signal pair to raise upon completion
 *
 * @see mem_read32_swap_ptr40()
 *
 */
#ifdef __PTR40
__intrinsic
void mem_read32_swap_ind_ptr40(
    __xread void *data,
    volatile void __addr40 __mem *address,
    unsigned int max_nn,
    generic_ind_t ind,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Read data from memory with byte swapping into transfer registers (little-endian).
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address 32-bit memory address to read from
 * @param count    Number of 32-bit words to read (1-32)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_read32_swap_le_ptr32(
    __xread void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Read data from memory with byte swapping into transfer registers (little-endian).
 *
 * @param data     Xfer register(s) to store data read from memory
 * @param address  40-bit memory address to read from
 * @param count    Number of 32-bit words to read (1-32)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_read32_swap_le_ptr40(
    __xread void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif



/** Write data to memory with byte swapping into transfer registers.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  32-bit memory address at which operation should be performed
 * @param count    Number of 32-bit words to write (1-32)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_write32_swap_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Write data to memory with byte swapping into transfer registers.
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param count    Number of 32-bit words to write (1-32)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write32_swap_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif


/** Write data to memory with byte swapping into transfer registers (little-endian).
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  32-bit memory address at which operation should be performed
 * @param count    Number of 32-bit words to write (1-32)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 */
__intrinsic
void mem_write32_swap_le_ptr32(
    __xwrite void *data,
    volatile void __addr32 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );

/** Write data to memory with byte swapping into transfer registers (little-endian).
 *
 * @param data     Xfer register(s) containing data to write to memory
 * @param address  40-bit memory address at which operation should be performed
 * @param count    Number of 32-bit words to write (1-32)
 * @param sync     Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr  Signal to raise upon completion
 *
 */
#ifdef __PTR40
__intrinsic
void mem_write32_swap_le_ptr40(
    __xwrite void *data,
    volatile void __addr40 __mem *address,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
    );
#endif



/*
 * 8-bit commands
 */
/** 8-bit read from memory into transfer registers in bytes (big-endian).
 *
 * Same as: @see mem_read8_ptr32()
 */
#define mem_read8_be_ptr32              mem_read8_ptr32

/** 8-bit read from memory into transfer registers in bytes (big-endian).
 *
 * Same as: @see mem_read8_ptr40()
 */
#define mem_read8_be_ptr40              mem_read8_ptr40

/** 8-bit read from memory into transfer registers in bytes (big-endian), with indirect
 *
 * Same as: @see mem_read8_ind_ptr32()
 */
#define mem_read8_be_ind_ptr32          mem_read8_ind_ptr32

/** 8-bit read from memory into transfer registers in bytes (big-endian), with indirect
 *
 * Same as: @see mem_read8_ind_ptr40()
 */
#define mem_read8_be_ind_ptr40          mem_read8_ind_ptr40



/** 8-bit write to memory from transfer registers in bytes (big-endian).
 *
 * Same as: @see mem_write8_ptr32()
 */
#define mem_write8_be_ptr32             mem_write8_ptr32

/** 8-bit write to memory from transfer registers in bytes (big-endian).
 *
 * Same as: @see mem_write8_ptr40()
 */
#define mem_write8_be_ptr40             mem_write8_ptr40

/** 8-bit write to memory from transfer registers in bytes (big-endian).
 *
 * Same as: @see mem_write8_ind_ptr32()
 */
#define mem_write8_be_ind_ptr32         mem_write8_ind_ptr32

/** 8-bit write to memory from transfer registers in bytes (big-endian).
 *
 * Same as: @see mem_write8_ind_ptr40()
 */
#define mem_write8_be_ind_ptr40         mem_write8_ind_ptr40



/** 8-bit write to memory from transfer registers in bytes (big-endian) with byte swapping.
 *
 * Same as: @see mem_write8_swap_ptr32()
 */
#define mem_write8_swap_be_ptr32        mem_write8_swap_ptr32

/** 8-bit write to memory from transfer registers in bytes (big-endian) with byte swapping.
 *
 * Same as: @see mem_write8_swap_ptr40()
 */
#define mem_write8_swap_be_ptr40        mem_write8_swap_ptr40


/** 8-bit write to memory from transfer registers in bytes (big-endian) with byte swapping and indirect
 *
 * Same as: @see mem_write8_swap_ind_ptr32()
 */
#define mem_write8_swap_be_ind_ptr32    mem_write8_swap_ind_ptr32

/** 8-bit write to memory from transfer registers in bytes (big-endian) with byte swapping and indirect
 *
 * Same as: @see mem_write8_swap_ind_ptr40()
 */
#define mem_write8_swap_be_ind_ptr40    mem_write8_swap_ind_ptr40


/*
 * 32-bit commands
 */

/** 32-bit read from memory into transfer registers in bytes (big-endian).
 *
 * Same as: @see mem_read32_ptr32()
 */
#define mem_read32_be_ptr32             mem_read32_ptr32

/** 32-bit read from memory into transfer registers in bytes (big-endian).
 *
 * Same as: @see mem_read32_ptr40()
 */
#define mem_read32_be_ptr40             mem_read32_ptr40

/** 32-bit read from memory into transfer registers in bytes (big-endian), with indirect
 *
 * Same as: @see mem_read32_ind_ptr32()
 */
#define mem_read32_be_ind_ptr32         mem_read32_ind_ptr32

/** 32-bit read from memory into transfer registers in bytes (big-endian), with indirect
 *
 * Same as: @see mem_read32_ind_ptr40()
 */
#define mem_read32_be_ind_ptr40         mem_read32_ind_ptr40



/** 32-bit read from memory into transfer registers in bytes (big-endian) with byte swapping.
 *
 * Same as: @see mem_read32_swap_ptr32()
 */
#define mem_read32_swap_be_ptr32        mem_read32_swap_ptr32

/** 32-bit read from memory into transfer registers in bytes (big-endian) with byte swapping.
 *
 * Same as: @see mem_read32_swap_ptr40()
 */
#define mem_read32_swap_be_ptr40        mem_read32_swap_ptr40

/** 32-bit read from memory into transfer registers in bytes (big-endian), with indirect and byte swapping
 *
 * Same as: @see mem_read32_swap_ind_ptr32()
 */
#define mem_read32_swap_be_ind_ptr32    mem_read32_swap_ind_ptr32

/** 32-bit read from memory into transfer registers in bytes (big-endian), with indirect and byte swapping
 *
 * Same as: @see mem_read32_swap_ind_ptr40()
 */
#define mem_read32_swap_be_ind_ptr40    mem_read32_swap_ind_ptr40



/** 32-bit write to memory from transfer registers in bytes (big-endian).
 *
 * Same as: @see mem_write32_ptr32()
 */
#define mem_write32_be_ptr32            mem_write32_ptr32

/** 32-bit write to memory from transfer registers in bytes (big-endian).
 *
 * Same as: @see mem_write32_ptr40()
 */
#define mem_write32_be_ptr40            mem_write32_ptr40

/** 32-bit write to memory from transfer registers in bytes (big-endian), with indirect
 *
 * Same as: @see mem_write32_ind_ptr32()
 */
#define mem_write32_be_ind_ptr32        mem_write32_ind_ptr32

/** 32-bit write to memory from transfer registers in bytes (big-endian), with indirect
 *
 * Same as: @see mem_write32_ind_ptr40()
 */
#define mem_write32_be_ind_ptr40        mem_write32_ind_ptr40



/** 32-bit write from memory into transfer registers in bytes (big-endian) with byte swapping.
 *
 * Same as: @see mem_write32_swap_ptr32()
 */
#define mem_write32_swap_be_ptr32       mem_write32_swap_ptr32

/** 32-bit write from memory into transfer registers in bytes (big-endian) with byte swapping.
 *
 * Same as: @see mem_write32_swap_ptr40()
 */
#define mem_write32_swap_be_ptr40       mem_write32_swap_ptr40

/** 32-bit write to memory from transfer registers in bytes (big-endian), with indirect and byte swapping
 *
 * Same as: @see mem_write32_swap_ind_ptr32()
 */
#define mem_write32_swap_be_ind_ptr32   mem_write32_swap_ind_ptr32

/** 32-bit write to memory from transfer registers in bytes (big-endian), with indirect and byte swapping
 *
 * Same as: @see mem_write32_swap_ind_ptr40()
 */
#define mem_write32_swap_be_ind_ptr40   mem_write32_swap_ind_ptr40



/*
 * 64-bit commands
 */
/** 64-bit read from memory into transfer registers in bytes (big-endian).
 *
 * Same as: @see mem_read64_ptr32()
 */
#define mem_read64_be_ptr32             mem_read64_ptr32

/** 64-bit read from memory into transfer registers in bytes (big-endian).
 *
 * Same as: @see mem_read64_ptr40()
 */
#define mem_read64_be_ptr40             mem_read64_ptr40

/** 64-bit read from memory into transfer registers in indirect mode (big-endian).
 *
 * Same as: @see mem_read64_ind_ptr40()
 */
#define mem_read64_be_ind_ptr32         mem_read64_ind_ptr32

/** 64-bit read from memory into transfer registers in indirect mode (big-endian).
 *
 * Same as: @see mem_read64_ind_ptr40()
 */
#define mem_read64_be_ind_ptr40         mem_read64_ind_ptr40



/** 64-bit read from memory into transfer registers in bytes (big-endian) with byte swapping.
 *
 * Same as: @see mem_read64_swap_ptr32()
 */
#define mem_read64_swap_be_ptr32        mem_read64_swap_ptr32

/** 64-bit read from memory into transfer registers in bytes (big-endian) with byte swapping.
 *
 * Same as: @see mem_read64_swap_ptr40()
 */
#define mem_read64_swap_be_ptr40        mem_read64_swap_ptr40

/** Read data from memory with byte swapping into transfer registers in indirect mode (big-endian).
 *
 * Same as: @see mem_read64_swap_ptr32()
 */
#define mem_read64_swap_be_ind_ptr32    mem_read64_swap_ind_ptr32

/** Read data from memory with byte swapping into transfer registers in indirect mode (big-endian).
 *
 * Same as: @see mem_read64_swap_ptr40()
 */
#define mem_read64_swap_be_ind_ptr40    mem_read64_swap_ind_ptr40



/** 64-bit write to memory from transfer registers in bytes (big-endian).
 *
 * @see mem_write64_ptr32
 */
#define mem_write64_be_ptr32            mem_write64_ptr32

/** 64-bit write to memory from transfer registers in bytes (big-endian).
 *
 * Same as: @see mem_write64_ptr40()
 */
#define mem_write64_be_ptr40            mem_write64_ptr40

/** 64-bit write to memory from transfer registers in bytes (big-endian), with indirect
 *
 * @see mem_write64_ind_ptr32
 */
#define mem_write64_be_ind_ptr32        mem_write64_ind_ptr32

/** 64-bit write to memory from transfer registers in bytes (big-endian), with indirect
 *
 * Same as: @see mem_write64_ind_ptr40()
 */
#define mem_write64_be_ind_ptr40        mem_write64_ind_ptr40



/** 64-bit write to memory from transfer registers in bytes (big-endian) with byte swapping.
 *
 * Same as:@see mem_write64_swap_ptr32()
 */
#define mem_write64_swap_be_ptr32       mem_write64_swap_ptr32

/** 64-bit write to memory from transfer registers in bytes (big-endian) with byte swapping.
 *
 * Same as: @see mem_write64_swap_ptr40()
 */
#define mem_write64_swap_be_ptr40       mem_write64_swap_ptr40

/** 64-bit write to memory from transfer registers in bytes (big-endian) with byte swapping, with indirect
 *
 * Same as:@see mem_write64_swap_ind_ptr32()
 */
#define mem_write64_swap_be_ind_ptr32   mem_write64_swap_ind_ptr32

/** 64-bit write to memory from transfer registers in bytes (big-endian) with byte swapping, with indirect
 *
 * Same as: @see mem_write64_swap_ind_ptr40()
 */
#define mem_write64_swap_be_ind_ptr40   mem_write64_swap_ind_ptr40

/** @}
 * @}
 */


/*
 * Define deprecated dram functions for backward compatibiliy
 */
#define dram_read                        mem_read64_ptr32
#define dram_read_ind                    mem_read64_ind_ptr32
#define dram_write                       mem_write64_ptr32
#define dram_write_ind                   mem_write64_ind_ptr32
#define dram_read_be                     mem_read64_be_ptr32
#define dram_read_be_ind                 mem_read64_be_ind_ptr32
#define dram_read_le                     mem_read64_le_ptr32
#define dram_read_le_ind                 mem_read64_le_ind_ptr32
#define dram_write_be                    mem_write64_be_ptr32
#define dram_write_be_ind                mem_write64_be_ind_ptr32
#define dram_write_le                    mem_write64_le_ptr32
#define dram_write_le_ind                mem_write64_le_ind_ptr32
#define dram_write_ind                   mem_write64_ind_ptr32
#define dram_write_swap_be               mem_write64_swap_be_ptr32
#define dram_write_swap_be_ind           mem_write64_swap_be_ind_ptr32
#define dram_write_swap_le               mem_write64_swap_le_ptr32
#define dram_write_swap_le_ind           mem_write64_swap_le_ind_ptr32
#define dram_write8_be                   mem_write8_be_ptr32
#define dram_write8_be_ind               mem_write8_be_ind_ptr32
#define dram_write8_le                   mem_write8_le_ptr32
#define dram_write8_le_ind               mem_write8_le_ind_ptr32
#define dram_write8_swap_be              mem_write8_swap_be_ptr32
#define dram_write8_swap_be_ind          mem_write8_swap_be_ind_ptr32
#define dram_write8_swap_le              mem_write8_swap_le_ptr32
#define dram_write8_swap_le_ind          mem_write8_swap_le_ind_ptr32
#define dram_read8                       mem_read8_ptr32
#define dram_read8_ind                   mem_read8_ind_ptr32
#define dram_read_atomic                 mem_read_atomic_ptr32
#define dram_read_atomic_ind             mem_read_atomic_ind_ptr32
#define dram_compare_write               mem_compare_write_ptr32
#define dram_compare_write_ind           mem_compare_write_ind_ptr32
#define dram_test_and_compare_write      mem_test_and_compare_write_ptr32
#define dram_test_and_compare_write_ind  mem_test_and_compare_write_ind_ptr32
#define dram_write_atomic                mem_write_atomic_ptr32
#define dram_write_atomic_ind            mem_write_atomic_ind_ptr32
#define dram_swap                        mem_swap_ptr32
#define dram_swap_ind                    mem_swap_ind_ptr32
#define dram_write_atomic_imm            mem_write_atomic_imm_ptr32
#define dram_swap_imm                    mem_swap_imm_ptr32
#define dram_set                         mem_set_ptr32
#define dram_set_ind                     mem_set_ind_ptr32
#define dram_test_and_set                mem_test_and_set_ptr32
#define dram_test_and_set_ind            mem_test_and_set_ind_ptr32
#define dram_set_imm                     mem_set_imm_ptr32
#define dram_test_and_set_imm            mem_test_and_set_imm_ptr32
#define dram_clr                         mem_clr_ptr32
#define dram_clr_ind                     mem_clr_ind_ptr32
#define dram_test_and_clr                mem_test_and_clr_ptr32
#define dram_test_and_clr_ind            mem_test_and_clr_ind_ptr32
#define dram_clr_imm                     mem_clr_imm_ptr32
#define dram_test_and_clr_imm            mem_test_and_clr_imm_ptr32
#define dram_add32                       mem_add32_ptr32
#define dram_add32_ind                   mem_add32_ind_ptr32
#define dram_add64                       mem_add64_ptr32
#define dram_add64_ind                   mem_add64_ind_ptr32
#define dram_test_and_add32              mem_test_and_add32_ptr32
#define dram_test_and_add32_ind          mem_test_and_add32_ind_ptr32
#define dram_test_and_add64              mem_test_and_add64_ptr32
#define dram_test_and_add64_ind          mem_test_and_add64_ind_ptr32
#define dram_add32_imm                   mem_add32_imm_ptr32
#define dram_test_and_add32_imm          mem_test_and_add32_imm_ptr32
#define dram_add64_imm                   mem_add64_imm_ptr32
#define dram_test_and_add64_imm          mem_test_and_add64_imm_ptr32
#define dram_add32_sat                   mem_add32_sat_ptr32
#define dram_add32_sat_ind               mem_add32_sat_ind_ptr32
#define dram_add64_sat                   mem_add64_sat_ptr32
#define dram_add64_sat_ind               mem_add64_sat_ind_ptr32
#define dram_test_and_add32_sat          mem_test_and_add32_sat_ptr32
#define dram_test_and_add32_sat_ind      mem_test_and_add32_sat_ind_ptr32
#define dram_test_and_add64_sat          mem_test_and_add64_sat_ptr32
#define dram_test_and_add64_sat_ind      mem_test_and_add64_sat_ind_ptr32
#define dram_add32_imm_sat               mem_add32_imm_sat_ptr32
#define dram_test_and_add32_imm_sat      mem_test_and_add32_imm_sat_ptr32
#define dram_add64_imm_sat               mem_add64_imm_sat_ptr32
#define dram_test_and_add64_imm_sat      mem_test_and_add64_imm_sat_ptr32
#define dram_sub32                       mem_sub32_ptr32
#define dram_sub32_ind                   mem_sub32_ind_ptr32
#define dram_sub64                       mem_sub64_ptr32
#define dram_sub64_ind                   mem_sub64_ind_ptr32
#define dram_test_and_sub32              mem_test_and_sub32_ptr32
#define dram_test_and_sub32_ind          mem_test_and_sub32_ind_ptr32
#define dram_test_and_sub64              mem_test_and_sub64_ptr32
#define dram_test_and_sub64_ind          mem_test_and_sub64_ind_ptr32
#define dram_sub32_imm                   mem_sub32_imm_ptr32
#define dram_test_and_sub32_imm          mem_test_and_sub32_imm_ptr32
#define dram_sub64_imm                   mem_sub64_imm_ptr32
#define dram_test_and_sub64_imm          mem_test_and_sub64_imm_ptr32
#define dram_sub32_sat                   mem_sub32_sat_ptr32
#define dram_sub32_sat_ind               mem_sub32_sat_ind_ptr32
#define dram_sub64_sat                   mem_sub64_sat_ptr32
#define dram_sub64_sat_ind               mem_sub64_sat_ind_ptr32
#define dram_test_and_sub32_sat          mem_test_and_sub32_sat_ptr32
#define dram_test_and_sub32_sat_ind      mem_test_and_sub32_sat_ind_ptr32
#define dram_test_and_sub64_sat          mem_test_and_sub64_sat_ptr32
#define dram_test_and_sub64_sat_ind      mem_test_and_sub64_sat_ind_ptr32
#define dram_sub32_imm_sat               mem_sub32_imm_sat_ptr32
#define dram_test_and_sub32_imm_sat      mem_test_and_sub32_imm_sat_ptr32
#define dram_sub64_imm_sat               mem_sub64_imm_sat_ptr32
#define dram_test_and_sub64_imm_sat      mem_test_and_sub64_imm_sat_ptr32
#define dram_xor                         mem_xor_ptr32
#define dram_xor_ind                     mem_xor_ind_ptr32
#define dram_test_and_xor                mem_test_and_xor_ptr32
#define dram_test_and_xor_ind            mem_test_and_xor_ind_ptr32
#define dram_xor_imm                     mem_xor_imm_ptr32
#define dram_test_and_xor_imm            mem_test_and_xor_imm_ptr32
#define dram_rbuf_read_ind               mem_rbuf_read_ind_ptr32
#define dram_tbuf_write_ind              mem_tbuf_write_ind_ptr32

#ifdef __PTR40
#define dram_read_ptr40                        mem_read64_ptr40
#define dram_read_ind_ptr40                    mem_read64_ind_ptr40
#define dram_write_ptr40                       mem_write64_ptr40
#define dram_write_ind_ptr40                   mem_write64_ind_ptr40
#define dram_read_be_ptr40                     mem_read64_be_ptr40
#define dram_read_be_ind_ptr40                 mem_read64_be_ind_ptr40
#define dram_read_le_ptr40                     mem_read64_le_ptr40
#define dram_read_le_ind_ptr40                 mem_read64_le_ind_ptr40
#define dram_write_be_ptr40                    mem_write64_be_ptr40
#define dram_write_be_ind_ptr40                mem_write64_be_ind_ptr40
#define dram_write_le_ptr40                    mem_write64_le_ptr40
#define dram_write_le_ind_ptr40                mem_write64_le_ind_ptr40
#define dram_write_ind_ptr40                   mem_write64_ind_ptr40
#define dram_write_swap_be_ptr40               mem_write64_swap_be_ptr40
#define dram_write_swap_be_ind_ptr40           mem_write64_swap_be_ind_ptr40
#define dram_write_swap_le_ptr40               mem_write64_swap_le_ptr40
#define dram_write_swap_le_ind_ptr40           mem_write64_swap_le_ind_ptr40
#define dram_write8_be_ptr40                   mem_write8_be_ptr40
#define dram_write8_be_ind_ptr40               mem_write8_be_ind_ptr40
#define dram_write8_le_ptr40                   mem_write8_le_ptr40
#define dram_write8_le_ind_ptr40               mem_write8_le_ind_ptr40
#define dram_write8_swap_be_ptr40              mem_write8_swap_be_ptr40
#define dram_write8_swap_be_ind_ptr40          mem_write8_swap_be_ind_ptr40
#define dram_write8_swap_le_ptr40              mem_write8_swap_le_ptr40
#define dram_write8_swap_le_ind_ptr40          mem_write8_swap_le_ind_ptr40
#define dram_read8_ptr40                       mem_read8_ptr40
#define dram_read8_ind_ptr40                   mem_read8_ind_ptr40
#define dram_read_atomic_ptr40                 mem_read_atomic_ptr40
#define dram_read_atomic_ind_ptr40             mem_read_atomic_ind_ptr40
#define dram_compare_write_ptr40               mem_compare_write_ptr40
#define dram_compare_write_ind_ptr40           mem_compare_write_ind_ptr40
#define dram_test_and_compare_write_ptr40      mem_test_and_compare_write_ptr40
#define dram_test_and_compare_write_ind_ptr40  mem_test_and_compare_write_ind_ptr40
#define dram_write_atomic_ptr40                mem_write_atomic_ptr40
#define dram_write_atomic_ind_ptr40            mem_write_atomic_ind_ptr40
#define dram_swap_ptr40                        mem_swap_ptr40
#define dram_swap_ind_ptr40                    mem_swap_ind_ptr40
#define dram_write_atomic_imm_ptr40            mem_write_atomic_imm_ptr40
#define dram_swap_imm_ptr40                    mem_swap_imm_ptr40
#define dram_set_ptr40                         mem_set_ptr40
#define dram_set_ind_ptr40                     mem_set_ind_ptr40
#define dram_test_and_set_ptr40                mem_test_and_set_ptr40
#define dram_test_and_set_ind_ptr40            mem_test_and_set_ind_ptr40
#define dram_set_imm_ptr40                     mem_set_imm_ptr40
#define dram_test_and_set_imm_ptr40            mem_test_and_set_imm_ptr40
#define dram_clr_ptr40                         mem_clr_ptr40
#define dram_clr_ind_ptr40                     mem_clr_ind_ptr40
#define dram_test_and_clr_ptr40                mem_test_and_clr_ptr40
#define dram_test_and_clr_ind_ptr40            mem_test_and_clr_ind_ptr40
#define dram_clr_imm_ptr40                     mem_clr_imm_ptr40
#define dram_test_and_clr_imm_ptr40            mem_test_and_clr_imm_ptr40
#define dram_add32_ptr40                       mem_add32_ptr40
#define dram_add32_ind_ptr40                   mem_add32_ind_ptr40
#define dram_add64_ptr40                       mem_add64_ptr40
#define dram_add64_ind_ptr40                   mem_add64_ind_ptr40
#define dram_test_and_add32_ptr40              mem_test_and_add32_ptr40
#define dram_test_and_add32_ptr40              mem_test_and_add32_ptr40
#define dram_test_and_add32_ptr40              mem_test_and_add32_ptr40
#define dram_test_and_add32_ind_ptr40          mem_test_and_add32_ind_ptr40
#define dram_test_and_add64_ptr40              mem_test_and_add64_ptr40
#define dram_test_and_add64_ind_ptr40          mem_test_and_add64_ind_ptr40
#define dram_add32_imm_ptr40                   mem_add32_imm_ptr40
#define dram_test_and_add32_imm_ptr40          mem_test_and_add32_imm_ptr40
#define dram_add64_imm_ptr40                   mem_add64_imm_ptr40
#define dram_test_and_add64_imm_ptr40          mem_test_and_add64_imm_ptr40
#define dram_add32_sat_ptr40                   mem_add32_sat_ptr40
#define dram_add32_sat_ind_ptr40               mem_add32_sat_ind_ptr40
#define dram_add64_sat_ptr40                   mem_add64_sat_ptr40
#define dram_add64_sat_ind_ptr40               mem_add64_sat_ind_ptr40
#define dram_test_and_add32_sat_ptr40          mem_test_and_add32_sat_ptr40
#define dram_test_and_add32_sat_ind_ptr40      mem_test_and_add32_sat_ind_ptr40
#define dram_test_and_add64_sat_ptr40          mem_test_and_add64_sat_ptr40
#define dram_test_and_add64_sat_ind_ptr40      mem_test_and_add64_sat_ind_ptr40
#define dram_add32_imm_sat_ptr40               mem_add32_imm_sat_ptr40
#define dram_test_and_add32_imm_sat_ptr40      mem_test_and_add32_imm_sat_ptr40
#define dram_add64_imm_sat_ptr40               mem_add64_imm_sat_ptr40
#define dram_test_and_add64_imm_sat_ptr40      mem_test_and_add64_imm_sat_ptr40
#define dram_sub32_ptr40                       mem_sub32_ptr40
#define dram_sub32_ind_ptr40                   mem_sub32_ind_ptr40
#define dram_sub64_ptr40                       mem_sub64_ptr40
#define dram_sub64_ind_ptr40                   mem_sub64_ind_ptr40
#define dram_test_and_sub32_ptr40              mem_test_and_sub32_ptr40
#define dram_test_and_sub32_ind_ptr40          mem_test_and_sub32_ind_ptr40
#define dram_test_and_sub64_ptr40              mem_test_and_sub64_ptr40
#define dram_test_and_sub64_ind_ptr40          mem_test_and_sub64_ind_ptr40
#define dram_sub32_imm_ptr40                   mem_sub32_imm_ptr40
#define dram_test_and_sub32_imm_ptr40          mem_test_and_sub32_imm_ptr40
#define dram_sub64_imm_ptr40                   mem_sub64_imm_ptr40
#define dram_test_and_sub64_imm_ptr40          mem_test_and_sub64_imm_ptr40
#define dram_sub32_sat_ptr40                   mem_sub32_sat_ptr40
#define dram_sub32_sat_ind_ptr40               mem_sub32_sat_ind_ptr40
#define dram_sub64_sat_ptr40                   mem_sub64_sat_ptr40
#define dram_sub64_sat_ind_ptr40               mem_sub64_sat_ind_ptr40
#define dram_test_and_sub32_sat_ptr40          mem_test_and_sub32_sat_ptr40
#define dram_test_and_sub32_sat_ind_ptr40      mem_test_and_sub32_sat_ind_ptr40
#define dram_test_and_sub64_sat_ptr40          mem_test_and_sub64_sat_ptr40
#define dram_test_and_sub64_sat_ind_ptr40      mem_test_and_sub64_sat_ind_ptr40
#define dram_sub32_imm_sat_ptr40               mem_sub32_imm_sat_ptr40
#define dram_test_and_sub32_imm_sat_ptr40      mem_test_and_sub32_imm_sat_ptr40
#define dram_sub64_imm_sat_ptr40               mem_sub64_imm_sat_ptr40
#define dram_test_and_sub64_imm_sat_ptr40      mem_test_and_sub64_imm_sat_ptr40
#define dram_xor_ptr40                         mem_xor_ptr40
#define dram_xor_ind_ptr40                     mem_xor_ind_ptr40
#define dram_test_and_xor_ptr40                mem_test_and_xor_ptr40
#define dram_test_and_xor_ind_ptr40            mem_test_and_xor_ind_ptr40
#define dram_xor_imm_ptr40                     mem_xor_imm_ptr40
#define dram_test_and_xor_imm_ptr40            mem_test_and_xor_imm_ptr40
#endif /* __PTR40 */

#include <nfp_mem_list.h>
#include <nfp_mem_microq.h>
#include <nfp_mem_lockq.h>
#include <nfp_mem_ring.h>
#include <nfp_mem_ticket.h>


#if (defined (__NFP_INDIRECT_REF_FORMAT_NFP3200) || defined(__NFP_INDIRECT_REF_FORMAT_NFP6000))
#include <nfp_mem_cam.h>
#include <nfp_mem_tcam.h>
#include <nfp_mem_lock.h>
#include <nfp_mem_workq.h>

#endif

#include <nfp_mem_lookup_engine.h>
#include <nfp_mem_load_balance_engine.h>
#include <nfp_mem_stats_engine.h>

#if (defined(__NFP_INDIRECT_REF_FORMAT_NFP6000))
    #include <nfp_mem_packet_engine.h>
#endif

#endif

