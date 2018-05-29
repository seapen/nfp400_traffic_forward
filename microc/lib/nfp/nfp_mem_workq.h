/*
 * Copyright (C) 2008-2014 Netronome Systems, Inc.  All rights reserved.
 */

#ifndef __NFP_MEM_WORKQ_H__
#define __NFP_MEM_WORKQ_H__

#ifndef NFP_LIB_ANY_NFCC_VERSION
    #if (!defined(__NFP_TOOL_NFCC) ||                       \
        (__NFP_TOOL_NFCC < NFP_SW_VERSION(5, 0, 0, 0)) ||   \
        (__NFP_TOOL_NFCC > NFP_SW_VERSION(6, 0, 2, 255)))
        #error "This standard library is not supported for the version of the SDK currently in use."
    #endif
#endif

#include <nfp_mem_ring.h>


/** @file nfp_mem_workq.h
 * @addtogroup MU_WorkQ MU WorkQ Intrinsics
 * @{
 */

/** @name Work Queue functions for MEM
 *  @{
 *
 * Work queues enable work to be scheduled among a pool of threads. Threads are added
 * to the work queue using the mem_workq_add_thread() intrinsic. The call will only return
 * when work is available or becomes available.
 *
 * Work is added to a work queue using mem_workq_add_work_imm() or mem_workq_add_work().
 * These calls will never block and overflow will occur when more work is added than
 * is consumed.
 *
 * Work queues are based on type 2 rings and the mem_ring_init() function can be used to
 * configure a new work queue before adding work or threads.
 *
 * Work can consist of 1 to 16 long words and should be the same size when added as when
 * consumed by mem_workq_add_thread().
 *
 * Below is an example of workq functions:
 *
 * @code
 *   // ring head and tail on i25 or emem1
 *   __emem_n(1) __addr40 __align(512*sizeof(unsigned int)) unsigned int mem_workq[512];
 *
 *   // place workq on emem1 with ring number 4
 *   unsigned int       mu_island = 1;
 *   unsigned int       ring_number =  (mu_island << 10) | 4;
 *   SIGNAL             signal;
 *
 *   mem_ring_init(ring_number, RING_SIZE_512, mem_workq, mem_workq, 0);
 *
 *   // Add work
 *   {
 *       __xwrite unsigned int          write_register;
 *       write_register = 0x01;
 *       mem_workq_add_work(ring_number, &write_register, 1, sig_done, &signal);
 *       __wait_for_all(&signal);
 *   }
 *
 *   // Add more work
 *   {
 *       unsigned int work = 0x123;
 *       mem_workq_add_work_imm(ring_number, work);
 *   }
 *
 *   {
 *       __xread unsigned int           read_register;
 *
 *       // Add thread, should get back 0x01
 *       mem_workq_add_thread(ring_number, &read_register, 1, ctx_swap, &signal);
 *
 *       if (read_register != 0x01)
 *       {
 *           return 0;        // We have an error
 *       }
 *
 *       // Add thread, should get back 0x123
 *       mem_workq_add_thread(ring_number, &read_register, 1, ctx_swap, &signal);
 *
 *       if (read_register != 0x123)
 *       {
 *           return 0;        // We have an error
 *       }
 *   }
 *
 *   return 1;
 *
 * @endcode
 */

/** Add work specified in transfer register(s) and place on the work queue.
 *
 * @param ring_number       MEM ring number to get data from (0-1023)
 * @param xfer              Transfer register(s) containing the work
 * @param count             Number of 32-bit words specifying the work (1 - 16)
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion.
 *
 * @note    No work queue overflow checking is performed.
 *
 */
__intrinsic
void mem_workq_add_work(
    unsigned int ring_number,
    __xwrite void *xfer,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** Add a single long word describing work on the work queue.
 *
 * @param ring_number       MEM ring number to put get data from (0-1023)
 * @param work_longword     32-bit word describing the work
 *
 * @note    No work queue overflow checking is performed and no signals are
 *          used.
 *
 *
 */
__intrinsic
void
mem_workq_add_work_imm(
    unsigned int ring_number,
    unsigned int work_longword
);

/** Fetch work from a work queue into transfer register(s).
 *
 * @param ring_number       MEM ring number to get data from (0-1023)
 * @param xfer              Transfer register(s) receiving the work
 * @param count             Number of 32-bit words to get (1 - 16)
 * @param sync              Type of synchronization to use (sig_done or ctx_swap)
 * @param sig_ptr           Signal to raise upon completion
 *
 * @note    This call will block until there is work on the queue.
 *
 */
__intrinsic
void mem_workq_add_thread(
    unsigned int ring_number,
    __xread unsigned int *xfer,
    unsigned int count,
    sync_t sync,
    SIGNAL *sig_ptr
);

/** @}
 * @}
 */

#endif /* __NFP_MEM_WORKQ_H__ */

