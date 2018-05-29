/*
 * Copyright (C) 2008-2014 Netronome Systems, Inc.  All rights reserved.
 */

/* NFP enhanced intrinsic function definitions */

#ifndef __NFP_COMPATIBILITY_H__
#define __NFP_COMPATIBILITY_H__

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

    /*
     * register types
     */
    #define __is_sram_read_reg      __is_read_reg
    #define __is_sram_write_reg     __is_write_reg
    #define __is_sram_reg           __is_xfer_reg
    #define sram_read_reg           read_reg
    #define sram_write_reg          write_reg
    #define sram_read_write_reg     read_write_reg

    #define __is_dram_read_reg      __is_read_reg
    #define __is_dram_write_reg     __is_write_reg
    #define __is_dram_reg           __is_xfer_reg
    #define dram_read_reg           read_reg
    #define dram_write_reg          write_reg
    #define dram_read_write_reg     read_write_reg


    #define __associate_sram_read_write_reg_pair_no_spill __associate_read_write_reg_pair_no_spill
    #define __associate_dram_read_write_reg_pair_no_spill __associate_read_write_reg_pair_no_spill

    /* architecture defines */
    #define __is_ixp_arch               __is_nfp_arch
    #define __is_ixp_arch_or_above      __is_nfp_arch_or_above


    /* indirect format */
#ifdef __NFP_INDIRECT_REF_FORMAT_NFP3200
    #define INDIRECT_FORMAT(nfp,ixp) nfp
#endif

    #define ptr40                   addr40      // i.e. __decspec(dram, ptr40) is mapped to __dram __addr40
    #define sdram                   dram        //  __decspec(sdram) is mapped to __dram
    #define mem_ptr                 mem         // name change in nfcc

    #define _rotr                   rotr        // name change
    #define _rotl                   rotl        // name change


    /*
     * memory region types
     */
    #define ua_set_8_dram           ua_set_8_mem
    #define ua_set_16_dram          ua_set_16_mem
    #define ua_set_32_dram          ua_set_32_mem
    #define ua_set_64_dram          ua_set_64_mem
    #define ua_get_u16_dram         ua_get_u16_mem
    #define ua_get_u32_dram         ua_get_u32_mem
    #define ua_get_s8_dram          ua_get_s8_mem
    #define ua_get_s16_dram         ua_get_s16_mem
    #define ua_get_s32_dram         ua_get_s32_mem
    #define ua_get_64_dram          ua_get_64_mem
    #define ua_get_u64_dram         ua_get_u64_mem
    #define ua_set_ptr40_16_dram    ua_set_ptr40_16_mem
    #define ua_set_ptr40_32_dram    ua_set_ptr40_32_mem
    #define ua_set_ptr40_64_dram    ua_set_ptr40_64_mem
    #define ua_get_ptr40_64_dram    ua_get_ptr40_64_mem
    #define ua_get_ptr40_32_dram    ua_get_ptr40_32_mem
    #define ua_get_ptr40_16_dram    ua_get_ptr40_16_mem
    #define ua_get_ptr40_8_dram     ua_get_ptr40_8_mem

    #define ua_memcpy_dram_dram     ua_memcpy_mem_mem
    #define ua_memcpy_dram_cls      ua_memcpy_mem_cls
    #define ua_memcpy_cls_dram      ua_memcpy_cls_mem
    #define ua_memcpy_lmem_dram     ua_memcpy_lmem_mem
    #define ua_memcpy_dram_lmem     ua_memcpy_mem_lmem

    #define __strto_l_ul_sdram      __strto_l_ul_mem

    #define memcpy_dram_dram        memcpy_mem_mem
    #define memcpy_dram_cls         memcpy_mem_cls
    #define memcpy_dram_lmem        memcpy_mem_lmem
    #define memcpy_cls_dram         memcpy_cls_mem
    #define memcpy_lmem_dram        memcpy_lmem_mem

    #define memmove_dram_dram       memmove_mem_mem
    #define memmove_lmem_dram       memmove_lmem_mem

    #define memset_dram             memset_mem

    #define memcmp_dram_dram        memcmp_mem_mem
    #define memcmp_dram_cls         memcmp_mem_cls
    #define memcmp_dram_lmem        memcmp_mem_lmem
    #define memcmp_cls_dram         memcmp_cls_mem
    #define memcmp_lmem_dram        memcmp_lmem_mem
    #define memchr_dram             memchr_mem

    #define strcpy_sdram            strcpy_mem
    #define strncpy_sdram           strncpy_mem
    #define strcat_sdram            strcat_mem
    #define strchr_sdram            strchr_mem

    #define strrchr_sdram           strrchr_mem
    #define strtok_sdram            strtok_mem
    #define strtol_sdram            strtol_mem
    #define strtoul_sdram           strtoul_mem
    #define strlen_sdram            strlen_mem
    #define strcmp_sdram            strcmp_mem
    #define strncmp_sdram           strncmp_mem
    #define strncat_sdram           strncat_mem

/*
 * Name change for CLS ring intrinsics.
 */
    #define cls_pop_safe_ring                   cls_ring_pop_safe
    #define cls_get_safe_ring                   cls_ring_get_safe
    #define cls_pop_ring                        cls_ring_pop
    #define cls_put_ring                        cls_ring_put
    #define cls_get_ring                        cls_ring_get
    #define cls_journal_ring                    cls_ring_journal

    #define cls_put_ring_ind                    cls_ring_put_ind
    #define cls_journal_ring_ind                cls_ring_journal_ind
    #define cls_get_ring_ind                    cls_ring_get_ind
    #define cls_pop_ring_ind                    cls_ring_pop_ind
    #define cls_get_safe_ring_ind               cls_ring_get_safe_ind
    #define cls_pop_safe_ring_ind               cls_ring_pop_safe_ind

/*
 * These intrinsics have a different interface for 32-bit addressing and 40-bit addressing.
 * The 40-bit addressing interface has an additional island id as parameter.
 */
    #define cls_ring_write                   cls_ring_write_ptr32
    #define cls_ring_read                    cls_ring_read_ptr32
    #define cls_ring_ordered_lock            cls_ring_ordered_lock_ptr32
    #define cls_ring_ordered_unlock          cls_ring_ordered_unlock_ptr32
    #define cls_ring_workq_add_thread        cls_ring_workq_add_thread_ptr32
    #define cls_ring_workq_add_work          cls_ring_workq_add_work_ptr32

/*
 * Name change for CLS reflect intrinsics.
 */
    #define cls_reflect_from_sig_src            cls_reflect_write_sig_local
    #define cls_reflect_from_sig_src_ptr40      cls_reflect_write_sig_local_ptr40
    #define cls_reflect_from_sig_dst            cls_reflect_write_sig_remote
    #define cls_reflect_from_sig_dst_ptr40      cls_reflect_write_sig_remote_ptr40
    #define cls_reflect_from_sig_both           cls_reflect_write_sig_both
    #define cls_reflect_from_sig_both_ptr40     cls_reflect_write_sig_both_ptr40
    #define cls_reflect_to_sig_src              cls_reflect_read_sig_remote
    #define cls_reflect_to_sig_src_ptr40        cls_reflect_read_sig_remote_ptr40
    #define cls_reflect_to_sig_dst              cls_reflect_read_sig_local
    #define cls_reflect_to_sig_dst_ptr40        cls_reflect_read_sig_local_ptr40
    #define cls_reflect_to_sig_both             cls_reflect_read_sig_both
    #define cls_reflect_to_sig_both_ptr40       cls_reflect_read_sig_both_ptr40
    #define cls_reflect_from_sig_src_ind_ptr40  cls_reflect_write_sig_local_ind_ptr40
    #define cls_reflect_from_sig_src_ind        cls_reflect_write_sig_local_ind
    #define cls_reflect_from_sig_dst_ind_ptr40  cls_reflect_write_sig_remote_ind_ptr40
    #define cls_reflect_from_sig_dst_ind        cls_reflect_write_sig_remote_ind
    #define cls_reflect_from_sig_both_ind_ptr40 cls_reflect_write_sig_both_ind_ptr40
    #define cls_reflect_from_sig_both_ind       cls_reflect_write_sig_both_ind
    #define cls_reflect_to_sig_src_ind_ptr40    cls_reflect_read_sig_remote_ind_ptr40
    #define cls_reflect_to_sig_src_ind          cls_reflect_read_sig_remote_ind
    #define cls_reflect_to_sig_dst_ind_ptr40    cls_reflect_read_sig_local_ind_ptr40
    #define cls_reflect_to_sig_dst_ind          cls_reflect_read_sig_local_ind
    #define cls_reflect_to_sig_both_ind_ptr40   cls_reflect_read_sig_both_ind_ptr40
    #define cls_reflect_to_sig_both_ind         cls_reflect_read_sig_both_ind

/*
 * Name change for MEM LB macros.
 */
    #define mem_lb_hash_seed_high               MEM_LB_HASH_SEED_LOW
    #define mem_lb_hash_seed_low                MEM_LB_HASH_SEED_LOW
    #define mem_lb_hash_base_addr_high          MEM_LB_HASH_BASE_ADDR_HIGH
    #define mem_lb_hash_base_addr_low           MEM_LB_HASH_BASE_ADDR_LOW
    #define mem_lb_hash_base_addr_from_desc     MEM_LB_HASH_BASE_ADDR_FROM_DESC
    #define mem_lb_hash_seed_from_desc          MEM_LB_HASH_SEED_FROM_DESC
    #define mem_lb_hash_base_addr_from_desc     MEM_LB_HASH_BASE_ADDR_FROM_DESC


/* Mapping between intrinsics with 32-bit addressing or 40-bit addressing depending on the compiler
* option of -addressing_default_32bit or -addressing_default_40bit (default)
*/

#ifdef __ADDRESSING_DEFAULT_32BIT


/*
 * PCIE
 */
    #define pcie_read                       pcie_read_ptr32
    #define pcie_write                      pcie_write_ptr32
    #define pcie_read_ind                   pcie_read_ind_ptr32
    #define pcie_write_ind                  pcie_write_ind_ptr32
    #define pcie_read_pci                   pcie_read_pci_ptr32
    #define pcie_write_pci                  pcie_write_pci_ptr32
    #define pcie_read_pci_ind               pcie_read_pci_ind_ptr32
    #define pcie_write_pci_ind              pcie_write_pci_ind_ptr32
    #define pcie_read_rid                   pcie_read_rid_ptr32
    #define pcie_write_rid                  pcie_write_rid_ptr32
    #define pcie_read_rid_ind               pcie_read_rid_ind_ptr32
    #define pcie_write_rid_ind              pcie_write_rid_ind_ptr32

/*
 * CLS
 */
    #define cls_read_be                     cls_read_be_ptr32
    #define cls_read_le                     cls_read_le_ptr32
    #define cls_read                        cls_read_ptr32
    #define cls_read_be_ind                 cls_read_be_ind_ptr32
    #define cls_read_le_ind                 cls_read_le_ind_ptr32
    #define cls_read_ind                    cls_read_ind_ptr32

    #define cls_write_be                    cls_write_be_ptr32
    #define cls_write_le                    cls_write_le_ptr32
    #define cls_write                       cls_write_ptr32
    #define cls_write_be_ind                cls_write_be_ind_ptr32
    #define cls_write_le_ind                cls_write_le_ind_ptr32
    #define cls_write_ind                   cls_write_ind_ptr32

    #define cls_write8_be                   cls_write8_be_ptr32
    #define cls_write8_le                   cls_write8_le_ptr32
    #define cls_write8                      cls_write8_ptr32

    #define cls_write8_le_ind               cls_write8_le_ind_ptr32
    #define cls_write8_be_ind               cls_write8_be_ind_ptr32
    #define cls_write8_ind                  cls_write8_ind_ptr32

    #define cls_clear_bits                  cls_clear_bits_ptr32
    #define cls_clear_bits_ind              cls_clear_bits_ind_ptr32
    #define cls_clear_bits_imm              cls_clear_bits_imm_ptr32

    #define cls_set_bits                    cls_set_bits_ptr32
    #define cls_set_bits_ind                cls_set_bits_ind_ptr32
    #define cls_set_bits_imm                cls_set_bits_imm_ptr32

    #define cls_xor_bits                    cls_xor_bits_ptr32
    #define cls_xor_bits_ind                cls_xor_bits_ind_ptr32

    #define cls_swap                        cls_swap_ptr32

    #define cls_add                         cls_add_ptr32
    #define cls_add_ind                     cls_add_ind_ptr32

    #define cls_test_and_add                cls_test_and_add_ptr32

    #define cls_add64                       cls_add64_ptr32
    #define cls_add64_ind                   cls_add64_ind_ptr32

    #define cls_add_sat                     cls_add_sat_ptr32
    #define cls_add_sat_ind                 cls_add_sat_ind_ptr32

    #define cls_add_imm                     cls_add_imm_ptr32
    #define cls_add_imm_sat                 cls_add_imm_sat_ptr32
    #define cls_add64_imm                   cls_add64_imm_ptr32

    #define cls_sub                          cls_sub_ptr32
    #define cls_sub_ind                      cls_sub_ind_ptr32
    #define cls_sub64                        cls_sub64_ptr32
    #define cls_sub64_ind                    cls_sub64_ind_ptr32
    #define cls_sub_sat                      cls_sub_sat_ptr32
    #define cls_sub_sat_ind                  cls_sub_sat_ind_ptr32

    #define cls_sub_imm                      cls_sub_imm_ptr32
    #define cls_sub_imm_sat                  cls_sub_imm_sat_ptr32
    #define cls_sub64_imm                    cls_sub64_imm_ptr32

    #define cls_test_and_add64               cls_test_and_add64_ptr32
    #define cls_test_and_add_imm             cls_test_and_add_imm_ptr32
    #define cls_test_and_add64_imm           cls_test_and_add64_imm_ptr32
    #define cls_test_and_sub                 cls_test_and_sub_ptr32
    #define cls_test_and_sub64               cls_test_and_sub64_ptr32
    #define cls_test_and_sub_imm             cls_test_and_sub_imm_ptr32
    #define cls_test_and_sub64_imm           cls_test_and_sub64_imm_ptr32
    #define cls_test_and_clear_bits          cls_test_and_clear_bits_ptr32
    #define cls_test_and_clear_bits_ind      cls_test_and_clear_bits_ind_ptr32
    #define cls_test_and_clear_bits_imm      cls_test_and_clear_bits_imm_ptr32
    #define cls_test_and_set_bits            cls_test_and_set_bits_ptr32
    #define cls_test_and_set_bits_ind        cls_test_and_set_bits_ind_ptr32
    #define cls_test_and_set_bits_imm        cls_test_and_set_bits_imm_ptr32
    #define cls_test_and_add_sat             cls_test_and_add_sat_ptr32
    #define cls_test_and_add_sat_ind         cls_test_and_add_sat_ind_ptr32
    #define cls_test_and_add_imm_sat         cls_test_and_add_imm_sat_ptr32
    #define cls_test_and_sub_sat             cls_test_and_sub_sat_ptr32
    #define cls_test_and_sub_sat_ind         cls_test_and_sub_sat_ind_ptr32
    #define cls_test_and_sub_imm_sat         cls_test_and_sub_imm_sat_ptr32

    #define cls_incr                         cls_incr_ptr32
    #define cls_decr                         cls_decr_ptr32
    #define cls_incr64                       cls_incr64_ptr32
    #define cls_decr64                       cls_decr64_ptr32

/*
 * CLS Ring
 */
    #define cls_ring_init                    cls_ring_init_ptr32
    #define cls_ring_put                     cls_ring_put_ptr32
    #define cls_ring_journal                 cls_ring_journal_ptr32
    #define cls_ring_get                     cls_ring_get_ptr32
    #define cls_ring_pop                     cls_ring_pop_ptr32
    #define cls_ring_get_safe                cls_ring_get_safe_ptr32
    #define cls_ring_pop_safe                cls_ring_pop_safe_ptr32

    #define cls_ring_put_ind                 cls_ring_put_ind_ptr32
    #define cls_ring_journal_ind             cls_ring_journal_ind_ptr32
    #define cls_ring_get_ind                 cls_ring_get_ind_ptr32
    #define cls_ring_pop_ind                 cls_ring_pop_ind_ptr32
    #define cls_ring_get_safe_ind            cls_ring_get_safe_ind_ptr32
    #define cls_ring_pop_safe_ind            cls_ring_pop_safe_ind_ptr32

/*
 * CLS Statistic
 */
    #define cls_statistic                   cls_statistic_ptr32
    #define cls_statistic_imm               cls_statistic_imm_ptr32
    #define cls_meter                       cls_meter_ptr32

    #define cls_cmp_read_write              cls_cmp_read_write_ptr32
    #define cls_cmp_read_write_ind          cls_cmp_read_write_ind_ptr32

/*
 * CLS Queue
 */
    #define cls_queue_lock                  cls_queue_lock_ptr32
    #define cls_queue_lock_ind              cls_queue_lock_ind_ptr32
    #define cls_queue_unlock                cls_queue_unlock_ptr32

/*
 * CLS Hash
 */
    #define cls_hash_mask                   cls_hash_mask_ptr32
    #define cls_hash_mask_ind               cls_hash_mask_ind_ptr32
    #define cls_hash_mask_clear             cls_hash_mask_clear_ptr32

/*
 * CLS CAM
 */
    #define cls_cam_lookup                  cls_cam_lookup_ptr32
    #define cls_cam_lookup_ind              cls_cam_lookup_ind_ptr32
    #define cls_cam_lookup_add              cls_cam_lookup_add_ptr32
    #define cls_cam_lookup_add_ind          cls_cam_lookup_add_ind_ptr32
    #define cls_cam_lookup24                cls_cam_lookup24_ptr32
    #define cls_cam_lookup24_ind            cls_cam_lookup24_ind_ptr32
    #define cls_cam_lookup24_add            cls_cam_lookup24_add_ptr32
    #define cls_cam_lookup24_add_ind        cls_cam_lookup24_add_ind_ptr32
    #define cls_cam_lookup24_add_inc        cls_cam_lookup24_add_inc_ptr32
    #define cls_cam_lookup24_add_inc_ind    cls_cam_lookup24_add_inc_ind_ptr32
    #define cls_cam_lookup24_add_lock       cls_cam_lookup24_add_lock_ptr32
    #define cls_cam_lookup24_add_extend     cls_cam_lookup24_add_extend_ptr32
    #define cls_cam_lookup16                cls_cam_lookup16_ptr32
    #define cls_cam_lookup16_ind            cls_cam_lookup16_ind_ptr32
    #define cls_cam_lookup16_add            cls_cam_lookup16_add_ptr32
    #define cls_cam_lookup16_add_ind        cls_cam_lookup16_add_ind_ptr32
    #define cls_cam_lookup8                 cls_cam_lookup8_ptr32
    #define cls_cam_lookup8_ind             cls_cam_lookup8_ind_ptr32
    #define cls_cam_lookup8_add             cls_cam_lookup8_add_ptr32
    #define cls_cam_lookup8_add_ind         cls_cam_lookup8_add_ind_ptr32

/*
 * CLS TCAM
 */
    #define cls_tcam_lookup                 cls_tcam_lookup_ptr32
    #define cls_tcam_lookup_ind             cls_tcam_lookup_ind_ptr32
    #define cls_tcam_lookup24               cls_tcam_lookup24_ptr32
    #define cls_tcam_lookup24_ind           cls_tcam_lookup24_ind_ptr32
    #define cls_tcam_lookup16               cls_tcam_lookup16_ptr32
    #define cls_tcam_lookup16_ind           cls_tcam_lookup16_ind_ptr32
    #define cls_tcam_lookup8                cls_tcam_lookup8_ptr32
    #define cls_tcam_lookup8_ind            cls_tcam_lookup8_ind_ptr32

/*
 * MEM
 */
    #define mem_write64                     mem_write64_ptr32
    #define mem_write64_ind                 mem_write64_ind_ptr32
    #define mem_write64_be                  mem_write64_be_ptr32
    #define mem_write64_be_ind              mem_write64_be_ind_ptr32
    #define mem_write64_le                  mem_write64_le_ptr32
    #define mem_write64_le_ind              mem_write64_le_ind_ptr32
    #define mem_write64_swap                mem_write64_swap_ptr32
    #define mem_write64_swap_ind            mem_write64_swap_ind_ptr32
    #define mem_write64_swap_be             mem_write64_swap_be_ptr32
    #define mem_write64_swap_be_ind         mem_write64_swap_be_ind_ptr32
    #define mem_write64_swap_le             mem_write64_swap_le_ptr32
    #define mem_write64_swap_le_ind         mem_write64_swap_le_ind_ptr32

    #define mem_read64                      mem_read64_ptr32
    #define mem_read64_ind                  mem_read64_ind_ptr32
    #define mem_read64_swap                 mem_read64_swap_ptr32
    #define mem_read64_swap_ind             mem_read64_swap_ind_ptr32
    #define mem_read64_swap_be              mem_read64_swap_be_ptr32
    #define mem_read64_swap_be_ind          mem_read64_swap_be_ind_ptr32
    #define mem_read64_swap_le              mem_read64_swap_le_ptr32
    #define mem_read64_swap_le_ind          mem_read64_swap_le_ind_ptr32
    #define mem_read64_be                   mem_read64_be_ptr32
    #define mem_read64_be_ind               mem_read64_be_ind_ptr32
    #define mem_read64_le                   mem_read64_le_ptr32
    #define mem_read64_le_ind               mem_read64_le_ind_ptr32

    #define mem_write32                     mem_write32_ptr32
    #define mem_write32_ind                 mem_write32_ind_ptr32
    #define mem_write32_be                  mem_write32_be_ptr32
    #define mem_write32_be_ind              mem_write32_be_ind_ptr32
    #define mem_write32_le                  mem_write32_le_ptr32
    #define mem_write32_swap                mem_write32_swap_ptr32
    #define mem_write32_swap_ind            mem_write32_swap_ind_ptr32
    #define mem_write32_swap_be             mem_write32_swap_be_ptr32
    #define mem_write32_swap_be_ind         mem_write32_swap_be_ind_ptr32
    #define mem_write32_swap_le             mem_write32_swap_le_ptr32

    #define mem_read32                      mem_read32_ptr32
    #define mem_read32_ind                  mem_read32_ind_ptr32
    #define mem_read32_be                   mem_read32_be_ptr32
    #define mem_read32_be_ind               mem_read32_be_ind_ptr32
    #define mem_read32_le                   mem_read32_le_ptr32
    #define mem_read32_swap                 mem_read32_swap_ptr32
    #define mem_read32_swap_ind             mem_read32_swap_ind_ptr32
    #define mem_read32_swap_be              mem_read32_swap_be_ptr32
    #define mem_read32_swap_be_ind          mem_read32_swap_be_ind_ptr32
    #define mem_read32_swap_le              mem_read32_swap_le_ptr32

    #define mem_write8                      mem_write8_ptr32
    #define mem_write8_ind                  mem_write8_ind_ptr32
    #define mem_write8_be                   mem_write8_be_ptr32
    #define mem_write8_be_ind               mem_write8_be_ind_ptr32
    #define mem_write8_le                   mem_write8_le_ptr32
    #define mem_write8_le_ind               mem_write8_le_ind_ptr32
    #define mem_write8_swap                 mem_write8_swap_ptr32
    #define mem_write8_swap_ind             mem_write8_swap_ind_ptr32
    #define mem_write8_swap_be              mem_write8_swap_be_ptr32
    #define mem_write8_swap_be_ind          mem_write8_swap_be_ind_ptr32
    #define mem_write8_swap_le              mem_write8_swap_le_ptr32
    #define mem_write8_swap_le_ind          mem_write8_swap_le_ind_ptr32

    #define mem_read8                       mem_read8_ptr32
    #define mem_read8_ind                   mem_read8_ind_ptr32
    #define mem_read8_be                    mem_read8_be_ptr32
    #define mem_read8_be_ind                mem_read8_be_ind_ptr32

    #define mem_read_atomic                 mem_read_atomic_ptr32
    #define mem_read_atomic_ind             mem_read_atomic_ind_ptr32

    #define mem_compare_write               mem_compare_write_ptr32
    #define mem_compare_write_ind           mem_compare_write_ind_ptr32
    #define mem_test_and_compare_write      mem_test_and_compare_write_ptr32
    #define mem_test_and_compare_write_ind  mem_test_and_compare_write_ind_ptr32

    #define mem_write_atomic                mem_write_atomic_ptr32
    #define mem_write_atomic_ind            mem_write_atomic_ind_ptr32
    #define mem_swap                        mem_swap_ptr32
    #define mem_swap_ind                    mem_swap_ind_ptr32
    #define mem_write_atomic_imm            mem_write_atomic_imm_ptr32
    #define mem_swap_imm                    mem_swap_imm_ptr32
    #define mem_set                         mem_set_ptr32
    #define mem_set_ind                     mem_set_ind_ptr32
    #define mem_test_and_set                mem_test_and_set_ptr32
    #define mem_test_and_set_ind            mem_test_and_set_ind_ptr32
    #define mem_set_imm                     mem_set_imm_ptr32
    #define mem_test_and_set_imm            mem_test_and_set_imm_ptr32
    #define mem_clr                         mem_clr_ptr32
    #define mem_clr_ind                     mem_clr_ind_ptr32
    #define mem_test_and_clr                mem_test_and_clr_ptr32
    #define mem_test_and_clr_ind            mem_test_and_clr_ind_ptr32
    #define mem_clr_imm                     mem_clr_imm_ptr32
    #define mem_test_and_clr_imm            mem_test_and_clr_imm_ptr32
    #define mem_add32                       mem_add32_ptr32
    #define mem_add32_ind                   mem_add32_ind_ptr32
    #define mem_add64                       mem_add64_ptr32
    #define mem_add64_ind                   mem_add64_ind_ptr32
    #define mem_test_and_add32              mem_test_and_add32_ptr32
    #define mem_test_and_add32_ind          mem_test_and_add32_ind_ptr32
    #define mem_test_and_add64              mem_test_and_add64_ptr32
    #define mem_test_and_add64_ind          mem_test_and_add64_ind_ptr32
    #define mem_add32_imm                   mem_add32_imm_ptr32
    #define mem_incr32                      mem_incr32_ptr32
    #define mem_test_and_add32_imm          mem_test_and_add32_imm_ptr32
    #define mem_add64_imm                   mem_add64_imm_ptr32
    #define mem_incr64                      mem_incr64_ptr32
    #define mem_test_and_add64_imm          mem_test_and_add64_imm_ptr32
    #define mem_add32_sat                   mem_add32_sat_ptr32
    #define mem_add32_sat_ind               mem_add32_sat_ind_ptr32
    #define mem_add64_sat                   mem_add64_sat_ptr32
    #define mem_add64_sat_ind               mem_add64_sat_ind_ptr32
    #define mem_test_and_add32_sat          mem_test_and_add32_sat_ptr32
    #define mem_test_and_add32_sat_ind      mem_test_and_add32_sat_ind_ptr32
    #define mem_test_and_add64_sat          mem_test_and_add64_sat_ptr32
    #define mem_test_and_add64_sat_ind      mem_test_and_add64_sat_ind_ptr32
    #define mem_add32_imm_sat               mem_add32_imm_sat_ptr32
    #define mem_test_and_add32_imm_sat      mem_test_and_add32_imm_sat_ptr32
    #define mem_add64_imm_sat               mem_add64_imm_sat_ptr32
    #define mem_test_and_add64_imm_sat      mem_test_and_add64_imm_sat_ptr32
    #define mem_sub32                       mem_sub32_ptr32
    #define mem_sub32_ind                   mem_sub32_ind_ptr32
    #define mem_sub64                       mem_sub64_ptr32
    #define mem_sub64_ind                   mem_sub64_ind_ptr32
    #define mem_test_and_sub32              mem_test_and_sub32_ptr32
    #define mem_test_and_sub32_ind          mem_test_and_sub32_ind_ptr32
    #define mem_test_and_sub64              mem_test_and_sub64_ptr32
    #define mem_test_and_sub64_ind          mem_test_and_sub64_ind_ptr32
    #define mem_sub32_imm                   mem_sub32_imm_ptr32
    #define mem_decr32                      mem_decr32_ptr32
    #define mem_test_and_sub32_imm          mem_test_and_sub32_imm_ptr32
    #define mem_sub64_imm                   mem_sub64_imm_ptr32
    #define mem_decr64                      mem_decr64_ptr32
    #define mem_test_and_sub64_imm          mem_test_and_sub64_imm_ptr32
    #define mem_sub32_sat                   mem_sub32_sat_ptr32
    #define mem_sub32_sat_ind               mem_sub32_sat_ind_ptr32
    #define mem_sub64_sat                   mem_sub64_sat_ptr32
    #define mem_sub64_sat_ind               mem_sub64_sat_ind_ptr32
    #define mem_test_and_sub32_sat          mem_test_and_sub32_sat_ptr32
    #define mem_test_and_sub32_sat_ind      mem_test_and_sub32_sat_ind_ptr32
    #define mem_test_and_sub64_sat          mem_test_and_sub64_sat_ptr32
    #define mem_test_and_sub64_sat_ind      mem_test_and_sub64_sat_ind_ptr32
    #define mem_sub32_imm_sat               mem_sub32_imm_sat_ptr32
    #define mem_test_and_sub32_imm_sat      mem_test_and_sub32_imm_sat_ptr32
    #define mem_sub64_imm_sat               mem_sub64_imm_sat_ptr32
    #define mem_test_and_sub64_imm_sat      mem_test_and_sub64_imm_sat_ptr32
    #define mem_xor                         mem_xor_ptr32
    #define mem_xor_ind                     mem_xor_ind_ptr32
    #define mem_test_and_xor                mem_test_and_xor_ptr32
    #define mem_test_and_xor_ind            mem_test_and_xor_ind_ptr32
    #define mem_xor_imm                     mem_xor_imm_ptr32
    #define mem_test_and_xor_imm            mem_test_and_xor_imm_ptr32
    #define mem_mask_compare_write          mem_mask_compare_write_ptr32
    #define mem_test_mask_and_compare_write mem_test_mask_and_compare_write_ptr32

/*
 * MEM CAM
 */
    #define  mem_cam128_init                mem_cam128_init_ptr32
    #define  mem_cam256_init                mem_cam256_init_ptr32
    #define  mem_cam384_init                mem_cam384_init_ptr32
    #define  mem_cam512_init                mem_cam512_init_ptr32
    #define  mem_cam128_set8                mem_cam128_set8_ptr32
    #define  mem_cam256_set8                mem_cam256_set8_ptr32
    #define  mem_cam384_set8                mem_cam384_set8_ptr32
    #define  mem_cam512_set8                mem_cam512_set8_ptr32
    #define  mem_cam128_set16               mem_cam128_set16_ptr32
    #define  mem_cam256_set16               mem_cam256_set16_ptr32
    #define  mem_cam384_set16               mem_cam384_set16_ptr32
    #define  mem_cam512_set16               mem_cam512_set16_ptr32
    #define  mem_cam128_set24               mem_cam128_set24_ptr32
    #define  mem_cam256_set24               mem_cam256_set24_ptr32
    #define  mem_cam384_set24               mem_cam384_set24_ptr32
    #define  mem_cam512_set24               mem_cam512_set24_ptr32
    #define  mem_cam128_set3                mem_cam128_set32_ptr32
    #define  mem_cam256_set32               mem_cam256_set32_ptr32
    #define  mem_cam384_set32               mem_cam384_set32_ptr32
    #define  mem_cam512_set32               mem_cam512_set32_ptr32

    #define mem_cam128_lookup8              mem_cam128_lookup8_ptr32
    #define mem_cam256_lookup8              mem_cam256_lookup8_ptr32
    #define mem_cam384_lookup8              mem_cam384_lookup8_ptr32
    #define mem_cam512_lookup8              mem_cam512_lookup8_ptr32

    #define mem_cam128_lookup8_add          mem_cam128_lookup8_add_ptr32
    #define mem_cam256_lookup8_add          mem_cam256_lookup8_add_ptr32
    #define mem_cam384_lookup8_add          mem_cam384_lookup8_add_ptr32
    #define mem_cam512_lookup8_add          mem_cam512_lookup8_add_ptr32

    #define mem_cam128_lookup16             mem_cam128_lookup16_ptr32
    #define mem_cam256_lookup16             mem_cam256_lookup16_ptr32
    #define mem_cam384_lookup16             mem_cam384_lookup16_ptr32
    #define mem_cam512_lookup16             mem_cam512_lookup16_ptr32

    #define mem_cam128_lookup16_add         mem_cam128_lookup16_add_ptr32
    #define mem_cam256_lookup16_add         mem_cam256_lookup16_add_ptr32
    #define mem_cam384_lookup16_add         mem_cam384_lookup16_add_ptr32
    #define mem_cam512_lookup16_add         mem_cam512_lookup16_add_ptr32

    #define mem_cam128_lookup24             mem_cam128_lookup24_ptr32
    #define mem_cam256_lookup24             mem_cam256_lookup24_ptr32
    #define mem_cam384_lookup24             mem_cam384_lookup24_ptr32
    #define mem_cam512_lookup24             mem_cam512_lookup24_ptr32

    #define mem_cam128_lookup24_add         mem_cam128_lookup24_add_ptr32
    #define mem_cam256_lookup24_add         mem_cam256_lookup24_add_ptr32
    #define mem_cam384_lookup24_add         mem_cam384_lookup24_add_ptr32
    #define mem_cam512_lookup24_add         mem_cam512_lookup24_add_ptr32

    #define mem_cam128_lookup24_add_inc     mem_cam128_lookup24_add_inc_ptr32
    #define mem_cam256_lookup24_add_inc     mem_cam256_lookup24_add_inc_ptr32
    #define mem_cam384_lookup24_add_inc     mem_cam384_lookup24_add_inc_ptr32
    #define mem_cam512_lookup24_add_inc     mem_cam512_lookup24_add_inc_ptr32

    #define mem_cam128_lookup32             mem_cam128_lookup32_ptr32
    #define mem_cam256_lookup32             mem_cam256_lookup32_ptr32
    #define mem_cam384_lookup32             mem_cam384_lookup32_ptr32
    #define mem_cam512_lookup32             mem_cam512_lookup32_ptr32

    #define mem_cam128_lookup32_add         mem_cam128_lookup32_add_ptr32
    #define mem_cam256_lookup32_add         mem_cam256_lookup32_add_ptr32
    #define mem_cam384_lookup32_add         mem_cam384_lookup32_add_ptr32
    #define mem_cam512_lookup32_add         mem_cam512_lookup32_add_ptr32

/*
 * MEM TCAM
 */
    #define mem_tcam128_init                mem_tcam128_init_ptr32
    #define mem_tcam256_init                mem_tcam256_init_ptr32
    #define mem_tcam384_init                mem_tcam384_init_ptr32
    #define mem_tcam512_init                mem_tcam512_init_ptr32

    #define mem_tcam128_set8_word           mem_tcam128_set8_word_ptr32
    #define mem_tcam128_set8_entry_value    mem_tcam128_set8_entry_value_ptr32
    #define mem_tcam128_set8_entry_mask     mem_tcam128_set8_entry_mask_ptr32
    #define mem_tcam128_set8_entry          mem_tcam128_set8_entry_ptr32

    #define mem_tcam256_set8_word           mem_tcam256_set8_word_ptr32
    #define mem_tcam256_set8_entry_value    mem_tcam256_set8_entry_value_ptr32
    #define mem_tcam256_set8_entry_mask     mem_tcam256_set8_entry_mask_ptr32
    #define mem_tcam256_set8_entry          mem_tcam256_set8_entry_ptr32

    #define mem_tcam384_set8_word           mem_tcam384_set8_word_ptr32
    #define mem_tcam384_set8_entry_value    mem_tcam384_set8_entry_value_ptr32
    #define mem_tcam384_set8_entry_mask     mem_tcam384_set8_entry_mask_ptr32
    #define mem_tcam384_set8_entry          mem_tcam384_set8_entry_ptr32

    #define mem_tcam512_set8_word           mem_tcam512_set8_word_ptr32
    #define mem_tcam512_set8_entry_value    mem_tcam512_set8_entry_value_ptr32
    #define mem_tcam512_set8_entry_mask     mem_tcam512_set8_entry_mask_ptr32
    #define mem_tcam512_set8_entry          mem_tcam512_set8_entry_ptr32

    #define mem_tcam128_set16_word          mem_tcam128_set16_word_ptr32
    #define mem_tcam128_set16_entry_value   mem_tcam128_set16_entry_value_ptr32
    #define mem_tcam128_set16_entry_mask    mem_tcam128_set16_entry_mask_ptr32
    #define mem_tcam128_set16_entry         mem_tcam128_set16_entry_ptr32

    #define mem_tcam256_set16_word          mem_tcam256_set16_word_ptr32
    #define mem_tcam256_set16_entry_value   mem_tcam256_set16_entry_value_ptr32
    #define mem_tcam256_set16_entry_mask    mem_tcam256_set16_entry_mask_ptr32
    #define mem_tcam256_set16_entry         mem_tcam256_set16_entry_ptr32

    #define mem_tcam384_set16_word          mem_tcam384_set16_word_ptr32
    #define mem_tcam384_set16_entry_value   mem_tcam384_set16_entry_value_ptr32
    #define mem_tcam384_set16_entry_mask    mem_tcam384_set16_entry_mask_ptr32
    #define mem_tcam384_set16_entry         mem_tcam384_set16_entry_ptr32

    #define mem_tcam512_set16_word          mem_tcam512_set16_word_ptr32
    #define mem_tcam512_set16_entry_value   mem_tcam512_set16_entry_value_ptr32
    #define mem_tcam512_set16_entry_mask    mem_tcam512_set16_entry_mask_ptr32
    #define mem_tcam512_set16_entry         mem_tcam512_set16_entry_ptr32

    #define mem_tcam128_set24_word          mem_tcam128_set24_word_ptr32
    #define mem_tcam128_set24_entry_value   mem_tcam128_set24_entry_value_ptr32
    #define mem_tcam128_set24_entry_mask    mem_tcam128_set24_entry_mask_ptr32
    #define mem_tcam128_set24_entry          mem_tcam128_set24_entry_ptr32

    #define mem_tcam256_set24_word          mem_tcam256_set24_word_ptr32
    #define mem_tcam256_set24_entry_value   mem_tcam256_set24_entry_value_ptr32
    #define mem_tcam256_set24_entry_mask    mem_tcam256_set24_entry_mask_ptr32
    #define mem_tcam256_set24_entry         mem_tcam256_set24_entry_ptr32

    #define mem_tcam384_set24_word          mem_tcam384_set24_word_ptr32
    #define mem_tcam384_set24_entry_value   mem_tcam384_set24_entry_value_ptr32
    #define mem_tcam384_set24_entry_mask    mem_tcam384_set24_entry_mask_ptr32
    #define mem_tcam384_set24_entry         mem_tcam384_set24_entry_ptr32

    #define mem_tcam512_set24_word          mem_tcam512_set24_word_ptr32
    #define mem_tcam512_set24_entry_value   mem_tcam512_set24_entry_value_ptr32
    #define mem_tcam512_set24_entry_mask    mem_tcam512_set24_entry_mask_ptr32
    #define mem_tcam512_set24_entry         mem_tcam512_set24_entry_ptr32

    #define mem_tcam128_set32_word          mem_tcam128_set32_word_ptr32
    #define mem_tcam128_set32_entry_value   mem_tcam128_set32_entry_value_ptr32
    #define mem_tcam128_set32_entry_mask    mem_tcam128_set32_entry_mask_ptr32
    #define mem_tcam128_set32_entry         mem_tcam128_set32_entry_ptr32

    #define mem_tcam256_set32_word          mem_tcam256_set32_word_ptr32
    #define mem_tcam256_set32_entry_value   mem_tcam256_set32_entry_value_ptr32
    #define mem_tcam256_set32_entry_mask    mem_tcam256_set32_entry_mask_ptr32
    #define mem_tcam256_set32_entry         mem_tcam256_set32_entry_ptr32

    #define mem_tcam384_set32_word          mem_tcam384_set32_word_ptr32
    #define mem_tcam384_set32_entry_value   mem_tcam384_set32_entry_value_ptr32
    #define mem_tcam384_set32_entry_mask    mem_tcam384_set32_entry_mask_ptr32
    #define mem_tcam384_set32_entry         mem_tcam384_set32_entry_ptr32

    #define mem_tcam512_set32_word          mem_tcam512_set32_word_ptr32
    #define mem_tcam512_set32_entry_value   mem_tcam512_set32_entry_value_ptr32
    #define mem_tcam512_set32_entry_mask    mem_tcam512_set32_entry_mask_ptr32
    #define mem_tcam512_set32_entry         mem_tcam512_set32_entry_ptr32

    #define mem_tcam128_lookup8             mem_tcam128_lookup8_ptr32
    #define mem_tcam256_lookup8             mem_tcam256_lookup8_ptr32
    #define mem_tcam384_lookup8             mem_tcam384_lookup8_ptr32
    #define mem_tcam512_lookup8             mem_tcam512_lookup8_ptr32

    #define mem_tcam128_lookup16            mem_tcam128_lookup16_ptr32
    #define mem_tcam256_lookup16            mem_tcam256_lookup16_ptr32
    #define mem_tcam384_lookup16            mem_tcam384_lookup16_ptr32
    #define mem_tcam512_lookup16            mem_tcam512_lookup16_ptr32

    #define mem_tcam128_lookup24            mem_tcam128_lookup24_ptr32
    #define mem_tcam256_lookup24            mem_tcam256_lookup24_ptr32
    #define mem_tcam384_lookup24            mem_tcam384_lookup24_ptr32
    #define mem_tcam512_lookup24            mem_tcam512_lookup24_ptr32

    #define mem_tcam128_lookup32            mem_tcam128_lookup32_ptr32
    #define mem_tcam256_lookup32            mem_tcam256_lookup32_ptr32
    #define mem_tcam384_lookup32            mem_tcam384_lookup32_ptr32
    #define mem_tcam512_lookup32            mem_tcam512_lookup32_ptr32

/*
 * MEM ticket
 */
    #define mem_ticket_release              mem_ticket_release_ptr32
    #define mem_ticket_release_push         mem_ticket_release_push_ptr32
    #define mem_ticket_line_init            mem_ticket_line_init_ptr32
    #define mem_ticket_line_push_init       mem_ticket_line_push_init_ptr32

/*
 * MEM lock
 */
    #define mem_lock128_init                mem_lock128_init_ptr32
    #define mem_lock256_init                mem_lock256_init_ptr32
    #define mem_lock384_init                mem_lock384_init_ptr32
    #define mem_lock512_init                mem_lock512_init_ptr32
    #define mem_lock128                     mem_lock128_ptr32
    #define mem_lock256                     mem_lock256_ptr32
    #define mem_lock384                     mem_lock384_ptr32
    #define mem_lock512                     mem_lock512_ptr32
    #define mem_unlock128                   mem_unlock128_ptr32
    #define mem_unlock256                   mem_unlock256_ptr32
    #define mem_unlock384                   mem_unlock384_ptr32
    #define mem_unlock512                   mem_unlock512_ptr32

/*
 * MEM lockq
 */
    #define mem_lockq128_lock               mem_lockq128_lock_ptr32
    #define mem_lockq256_lock               mem_lockq256_lock_ptr32
    #define mem_lockq128_unlock             mem_lockq128_unlock_ptr32
    #define mem_lockq256_unlock             mem_lockq256_unlock_ptr32
    #define mem_lockq128_init               mem_lockq128_init_ptr32
    #define mem_lockq256_init               mem_lockq256_init_ptr32

/*
 * MEM microq
 */
    #define mem_microq128_put               mem_microq128_put_ptr32
    #define mem_microq256_put               mem_microq256_put_ptr32
    #define mem_microq128_get               mem_microq128_get_ptr32
    #define mem_microq256_get               mem_microq256_get_ptr32
    #define mem_microq128_pop               mem_microq128_pop_ptr32
    #define mem_microq256_pop               mem_microq256_pop_ptr32
    #define mem_microq128_init              mem_microq128_init_ptr32
    #define mem_microq256_init              mem_microq256_init_ptr32
#endif  /* __ADDRESSING_DEFAULT_32BIT */

#ifdef  __ADDRESSING_DEFAULT_40BIT


/*
 * PCIE
 */
    #define pcie_read                       pcie_read_ptr40
    #define pcie_write                      pcie_write_ptr40

    #define pcie_read_ind                   pcie_read_ind_ptr40     // TODO
    #define pcie_write_ind                  pcie_write_ind_ptr40    // TODO

    #define pcie_read_pci                   pcie_read_pci_ptr40
    #define pcie_write_pci                  pcie_write_pci_ptr40

    #define pcie_read_pci_ind               pcie_read_pci_ind_ptr40 // TODO
    #define pcie_write_pci_ind              pcie_write_pci_ind_ptr40// TODO

    #define pcie_read_rid                   pcie_read_rid_ptr40
    #define pcie_write_rid                  pcie_write_rid_ptr40

    #define pcie_read_rid_ind               pcie_read_rid_ind_ptr40 // TODO
    #define pcie_write_rid_ind              pcie_write_rid_ind_ptr40// TODO

/*
 * CLS
 */
    #define cls_read_be                     cls_read_be_ptr40
    #define cls_read_le                     cls_read_le_ptr40
    #define cls_read                        cls_read_ptr40
    #define cls_read_be_ind                 cls_read_be_ind_ptr40
    #define cls_read_le_ind                 cls_read_le_ind_ptr40
    #define cls_read_ind                    cls_read_ind_ptr40

    #define cls_write_be                    cls_write_be_ptr40
    #define cls_write_le                    cls_write_le_ptr40
    #define cls_write                       cls_write_ptr40
    #define cls_write_be_ind                cls_write_be_ind_ptr40
    #define cls_write_le_ind                cls_write_le_ind_ptr40
    #define cls_write_ind                   cls_write_ind_ptr40

    #define cls_write8_be                   cls_write8_be_ptr40
    #define cls_write8_le                   cls_write8_le_ptr40
    #define cls_write8                      cls_write8_ptr40

    #define cls_write8_le_ind               cls_write8_le_ind_ptr40
    #define cls_write8_be_ind               cls_write8_be_ind_ptr40
    #define cls_write8_ind                  cls_write8_ind_ptr40

    #define cls_clear_bits                  cls_clear_bits_ptr40
    #define cls_clear_bits_ind              cls_clear_bits_ind_ptr40
    #define cls_clear_bits_imm              cls_clear_bits_imm_ptr40

    #define cls_set_bits                    cls_set_bits_ptr40
    #define cls_set_bits_ind                cls_set_bits_ind_ptr40
    #define cls_set_bits_imm                cls_set_bits_imm_ptr40

    #define cls_xor_bits                    cls_xor_bits_ptr40
    #define cls_xor_bits_ind                cls_xor_bits_ind_ptr40

    #define cls_swap                        cls_swap_ptr40

    #define cls_add                         cls_add_ptr40
    #define cls_add_ind                     cls_add_ind_ptr40

    #define cls_test_and_add                cls_test_and_add_ptr40

    #define cls_add64                       cls_add64_ptr40
    #define cls_add64_ind                   cls_add64_ind_ptr40

    #define cls_add_sat                     cls_add_sat_ptr40
    #define cls_add_sat_ind                 cls_add_sat_ind_ptr40

    #define cls_add_imm                     cls_add_imm_ptr40
    #define cls_add_imm_sat                 cls_add_imm_sat_ptr40
    #define cls_add64_imm                   cls_add64_imm_ptr40

    #define cls_sub                          cls_sub_ptr40
    #define cls_sub_ind                      cls_sub_ind_ptr40
    #define cls_sub64                        cls_sub64_ptr40
    #define cls_sub64_ind                    cls_sub64_ind_ptr40
    #define cls_sub_sat                      cls_sub_sat_ptr40
    #define cls_sub_sat_ind                  cls_sub_sat_ind_ptr40

    #define cls_sub_imm                      cls_sub_imm_ptr40
    #define cls_sub_imm_sat                  cls_sub_imm_sat_ptr40
    #define cls_sub64_imm                    cls_sub64_imm_ptr40

    #define cls_test_and_add64               cls_test_and_add64_ptr40
    #define cls_test_and_add_imm             cls_test_and_add_imm_ptr40
    #define cls_test_and_add64_imm           cls_test_and_add64_imm_ptr40
    #define cls_test_and_sub                 cls_test_and_sub_ptr40
    #define cls_test_and_sub64               cls_test_and_sub64_ptr40
    #define cls_test_and_sub_imm             cls_test_and_sub_imm_ptr40
    #define cls_test_and_sub64_imm           cls_test_and_sub64_imm_ptr40
    #define cls_test_and_clear_bits          cls_test_and_clear_bits_ptr40
    #define cls_test_and_clear_bits_ind      cls_test_and_clear_bits_ind_ptr40
    #define cls_test_and_clear_bits_imm      cls_test_and_clear_bits_imm_ptr40
    #define cls_test_and_set_bits            cls_test_and_set_bits_ptr40
    #define cls_test_and_set_bits_ind        cls_test_and_set_bits_ind_ptr40
    #define cls_test_and_set_bits_imm        cls_test_and_set_bits_imm_ptr40
    #define cls_test_and_add_sat             cls_test_and_add_sat_ptr40
    #define cls_test_and_add_sat_ind         cls_test_and_add_sat_ind_ptr40
    #define cls_test_and_add_imm_sat         cls_test_and_add_imm_sat_ptr40
    #define cls_test_and_sub_sat             cls_test_and_sub_sat_ptr40
    #define cls_test_and_sub_sat_ind         cls_test_and_sub_sat_ind_ptr40
    #define cls_test_and_sub_imm_sat         cls_test_and_sub_imm_sat_ptr40

    #define cls_incr                         cls_incr_ptr40
    #define cls_decr                         cls_decr_ptr40
    #define cls_incr64                       cls_incr64_ptr40
    #define cls_decr64                       cls_decr64_ptr40

/*
 * CLS Ring
 */
    #define cls_ring_init                    cls_ring_init_ptr40
    #define cls_ring_put                     cls_ring_put_ptr40
    #define cls_ring_journal                 cls_ring_journal_ptr40
    #define cls_ring_get                     cls_ring_get_ptr40
    #define cls_ring_pop                     cls_ring_pop_ptr40
    #define cls_ring_get_safe                cls_ring_get_safe_ptr40
    #define cls_ring_pop_safe                cls_ring_pop_safe_ptr40

    #define cls_ring_put_ind                 cls_ring_put_ind_ptr40
    #define cls_ring_journal_ind             cls_ring_journal_ind_ptr40
    #define cls_ring_get_ind                 cls_ring_get_ind_ptr40
    #define cls_ring_pop_ind                 cls_ring_pop_ind_ptr40
    #define cls_ring_get_safe_ind            cls_ring_get_safe_ind_ptr40
    #define cls_ring_pop_safe_ind            cls_ring_pop_safe_ind_ptr40

/*
 * CLS Statistic
 */
    #define cls_statistic                   cls_statistic_ptr40
    #define cls_statistic_imm               cls_statistic_imm_ptr40
    #define cls_meter                       cls_meter_ptr40

    #define cls_cmp_read_write              cls_cmp_read_write_ptr40
    #define cls_cmp_read_write_ind          cls_cmp_read_write_ind_ptr40

/*
 * CLS Queue
 */
    #define cls_queue_lock                  cls_queue_lock_ptr40
    #define cls_queue_lock_ind              cls_queue_lock_ind_ptr40
    #define cls_queue_unlock                cls_queue_unlock_ptr40

/*
 * CLS Hash
 */
    #define cls_hash_mask                   cls_hash_mask_ptr40
    #define cls_hash_mask_ind               cls_hash_mask_ind_ptr40
    #define cls_hash_mask_clear             cls_hash_mask_clear_ptr40

/*
 * CLS CAM
 */
    #define cls_cam_lookup                  cls_cam_lookup_ptr40
    #define cls_cam_lookup_ind              cls_cam_lookup_ind_ptr40
    #define cls_cam_lookup_add              cls_cam_lookup_add_ptr40
    #define cls_cam_lookup_add_ind          cls_cam_lookup_add_ind_ptr40
    #define cls_cam_lookup24                cls_cam_lookup24_ptr40
    #define cls_cam_lookup24_ind            cls_cam_lookup24_ind_ptr40
    #define cls_cam_lookup24_add            cls_cam_lookup24_add_ptr40
    #define cls_cam_lookup24_add_ind        cls_cam_lookup24_add_ind_ptr40
    #define cls_cam_lookup24_add_inc        cls_cam_lookup24_add_inc_ptr40
    #define cls_cam_lookup24_add_inc_ind    cls_cam_lookup24_add_inc_ind_ptr40
    #define cls_cam_lookup24_add_lock       cls_cam_lookup24_add_lock_ptr40
    #define cls_cam_lookup24_add_extend     cls_cam_lookup24_add_extend_ptr40
    #define cls_cam_lookup16                cls_cam_lookup16_ptr40
    #define cls_cam_lookup16_ind            cls_cam_lookup16_ind_ptr40
    #define cls_cam_lookup16_add            cls_cam_lookup16_add_ptr40
    #define cls_cam_lookup16_add_ind        cls_cam_lookup16_add_ind_ptr40
    #define cls_cam_lookup8                 cls_cam_lookup8_ptr40
    #define cls_cam_lookup8_ind             cls_cam_lookup8_ind_ptr40
    #define cls_cam_lookup8_add             cls_cam_lookup8_add_ptr40
    #define cls_cam_lookup8_add_ind         cls_cam_lookup8_add_ind_ptr40

/*
 * CLS TCAM
 */
    #define cls_tcam_lookup                 cls_tcam_lookup_ptr40
    #define cls_tcam_lookup_ind             cls_tcam_lookup_ind_ptr40
    #define cls_tcam_lookup24               cls_tcam_lookup24_ptr40
    #define cls_tcam_lookup24_ind           cls_tcam_lookup24_ind_ptr40
    #define cls_tcam_lookup16               cls_tcam_lookup16_ptr40
    #define cls_tcam_lookup16_ind           cls_tcam_lookup16_ind_ptr40
    #define cls_tcam_lookup8                cls_tcam_lookup8_ptr40
    #define cls_tcam_lookup8_ind            cls_tcam_lookup8_ind_ptr40

/*
 * MEM
 */
    #define mem_write64                     mem_write64_ptr40
    #define mem_write64_ind                 mem_write64_ind_ptr40
    #define mem_write64_be                  mem_write64_be_ptr40
    #define mem_write64_be_ind              mem_write64_be_ind_ptr40
    #define mem_write64_le                  mem_write64_le_ptr40
    #define mem_write64_le_ind              mem_write64_le_ind_ptr40
    #define mem_write64_swap                mem_write64_swap_ptr40
    #define mem_write64_swap_ind            mem_write64_swap_ind_ptr40
    #define mem_write64_swap_be             mem_write64_swap_be_ptr40
    #define mem_write64_swap_be_ind         mem_write64_swap_be_ind_ptr40
    #define mem_write64_swap_le             mem_write64_swap_le_ptr40
    #define mem_write64_swap_le_ind         mem_write64_swap_le_ind_ptr40

    #define mem_read64                      mem_read64_ptr40
    #define mem_read64_ind                  mem_read64_ind_ptr40
    #define mem_read64_swap                 mem_read64_swap_ptr40
    #define mem_read64_swap_ind             mem_read64_swap_ind_ptr40
    #define mem_read64_swap_be              mem_read64_swap_be_ptr40
    #define mem_read64_swap_be_ind          mem_read64_swap_be_ind_ptr40
    #define mem_read64_swap_le              mem_read64_swap_le_ptr40
    #define mem_read64_swap_le_ind          mem_read64_swap_le_ind_ptr40
    #define mem_read64_be                   mem_read64_be_ptr40
    #define mem_read64_be_ind               mem_read64_be_ind_ptr40
    #define mem_read64_le                   mem_read64_le_ptr40
    #define mem_read64_le_ind               mem_read64_le_ind_ptr40

    #define mem_write32                     mem_write32_ptr40
    #define mem_write32_ind                 mem_write32_ind_ptr40
    #define mem_write32_be                  mem_write32_be_ptr40
    #define mem_write32_be_ind              mem_write32_be_ind_ptr40
    #define mem_write32_le                  mem_write32_le_ptr40
    #define mem_write32_swap                mem_write32_swap_ptr40
    #define mem_write32_swap_ind            mem_write32_swap_ind_ptr40
    #define mem_write32_swap_be             mem_write32_swap_be_ptr40
    #define mem_write32_swap_be_ind         mem_write32_swap_be_ind_ptr40
    #define mem_write32_swap_le             mem_write32_swap_le_ptr40

    #define mem_read32                      mem_read32_ptr40
    #define mem_read32_ind                  mem_read32_ind_ptr40
    #define mem_read32_be                   mem_read32_be_ptr40
    #define mem_read32_be_ind               mem_read32_be_ind_ptr40
    #define mem_read32_le                   mem_read32_le_ptr40
    #define mem_read32_swap                 mem_read32_swap_ptr40
    #define mem_read32_swap_ind             mem_read32_swap_ind_ptr40
    #define mem_read32_swap_be              mem_read32_swap_be_ptr40
    #define mem_read32_swap_be_ind          mem_read32_swap_be_ind_ptr40
    #define mem_read32_swap_le              mem_read32_swap_le_ptr40

    #define mem_write8                      mem_write8_ptr40
    #define mem_write8_ind                  mem_write8_ind_ptr40
    #define mem_write8_be                   mem_write8_be_ptr40
    #define mem_write8_be_ind               mem_write8_be_ind_ptr40
    #define mem_write8_le                   mem_write8_le_ptr40
    #define mem_write8_le_ind               mem_write8_le_ind_ptr40
    #define mem_write8_swap                 mem_write8_swap_ptr40
    #define mem_write8_swap_ind             mem_write8_swap_ind_ptr40
    #define mem_write8_swap_be              mem_write8_swap_be_ptr40
    #define mem_write8_swap_be_ind          mem_write8_swap_be_ind_ptr40
    #define mem_write8_swap_le              mem_write8_swap_le_ptr40
    #define mem_write8_swap_le_ind          mem_write8_swap_le_ind_ptr40

    #define mem_read8                       mem_read8_ptr40
    #define mem_read8_ind                   mem_read8_ind_ptr40
    #define mem_read8_be                    mem_read8_be_ptr40
    #define mem_read8_be_ind                mem_read8_be_ind_ptr40

    #define mem_read_atomic                 mem_read_atomic_ptr40
    #define mem_read_atomic_ind             mem_read_atomic_ind_ptr40

    #define mem_compare_write               mem_compare_write_ptr40
    #define mem_compare_write_ind           mem_compare_write_ind_ptr40
    #define mem_test_and_compare_write      mem_test_and_compare_write_ptr40
    #define mem_test_and_compare_write_ind  mem_test_and_compare_write_ind_ptr40

    #define mem_write_atomic                mem_write_atomic_ptr40
    #define mem_write_atomic_ind            mem_write_atomic_ind_ptr40
    #define mem_swap                        mem_swap_ptr40
    #define mem_swap_ind                    mem_swap_ind_ptr40
    #define mem_write_atomic_imm            mem_write_atomic_imm_ptr40
    #define mem_swap_imm                    mem_swap_imm_ptr40
    #define mem_set                         mem_set_ptr40
    #define mem_set_ind                     mem_set_ind_ptr40
    #define mem_test_and_set                mem_test_and_set_ptr40
    #define mem_test_and_set_ind            mem_test_and_set_ind_ptr40
    #define mem_set_imm                     mem_set_imm_ptr40
    #define mem_test_and_set_imm            mem_test_and_set_imm_ptr40
    #define mem_clr                         mem_clr_ptr40
    #define mem_clr_ind                     mem_clr_ind_ptr40
    #define mem_test_and_clr                mem_test_and_clr_ptr40
    #define mem_test_and_clr_ind            mem_test_and_clr_ind_ptr40
    #define mem_clr_imm                     mem_clr_imm_ptr40
    #define mem_test_and_clr_imm            mem_test_and_clr_imm_ptr40
    #define mem_add32                       mem_add32_ptr40
    #define mem_add32_ind                   mem_add32_ind_ptr40
    #define mem_add64                       mem_add64_ptr40
    #define mem_add64_ind                   mem_add64_ind_ptr40
    #define mem_test_and_add32              mem_test_and_add32_ptr40
    #define mem_test_and_add32_ind          mem_test_and_add32_ind_ptr40
    #define mem_test_and_add64              mem_test_and_add64_ptr40
    #define mem_test_and_add64_ind          mem_test_and_add64_ind_ptr40
    #define mem_add32_imm                   mem_add32_imm_ptr40
    #define mem_incr32                      mem_incr32_ptr40
    #define mem_test_and_add32_imm          mem_test_and_add32_imm_ptr40
    #define mem_add64_imm                   mem_add64_imm_ptr40
    #define mem_incr64                      mem_incr64_ptr40
    #define mem_test_and_add64_imm          mem_test_and_add64_imm_ptr40
    #define mem_add32_sat                   mem_add32_sat_ptr40
    #define mem_add32_sat_ind               mem_add32_sat_ind_ptr40
    #define mem_add64_sat                   mem_add64_sat_ptr40
    #define mem_add64_sat_ind               mem_add64_sat_ind_ptr40
    #define mem_test_and_add32_sat          mem_test_and_add32_sat_ptr40
    #define mem_test_and_add32_sat_ind      mem_test_and_add32_sat_ind_ptr40
    #define mem_test_and_add64_sat          mem_test_and_add64_sat_ptr40
    #define mem_test_and_add64_sat_ind      mem_test_and_add64_sat_ind_ptr40
    #define mem_add32_imm_sat               mem_add32_imm_sat_ptr40
    #define mem_test_and_add32_imm_sat      mem_test_and_add32_imm_sat_ptr40
    #define mem_add64_imm_sat               mem_add64_imm_sat_ptr40
    #define mem_test_and_add64_imm_sat      mem_test_and_add64_imm_sat_ptr40
    #define mem_sub32                       mem_sub32_ptr40
    #define mem_sub32_ind                   mem_sub32_ind_ptr40
    #define mem_sub64                       mem_sub64_ptr40
    #define mem_sub64_ind                   mem_sub64_ind_ptr40
    #define mem_test_and_sub32              mem_test_and_sub32_ptr40
    #define mem_test_and_sub32_ind          mem_test_and_sub32_ind_ptr40
    #define mem_test_and_sub64              mem_test_and_sub64_ptr40
    #define mem_test_and_sub64_ind          mem_test_and_sub64_ind_ptr40
    #define mem_sub32_imm                   mem_sub32_imm_ptr40
    #define mem_decr32                      mem_decr32_ptr40
    #define mem_test_and_sub32_imm          mem_test_and_sub32_imm_ptr40
    #define mem_sub64_imm                   mem_sub64_imm_ptr40
    #define mem_decr64                      mem_decr64_ptr40
    #define mem_test_and_sub64_imm          mem_test_and_sub64_imm_ptr40
    #define mem_sub32_sat                   mem_sub32_sat_ptr40
    #define mem_sub32_sat_ind               mem_sub32_sat_ind_ptr40
    #define mem_sub64_sat                   mem_sub64_sat_ptr40
    #define mem_sub64_sat_ind               mem_sub64_sat_ind_ptr40
    #define mem_test_and_sub32_sat          mem_test_and_sub32_sat_ptr40
    #define mem_test_and_sub32_sat_ind      mem_test_and_sub32_sat_ind_ptr40
    #define mem_test_and_sub64_sat          mem_test_and_sub64_sat_ptr40
    #define mem_test_and_sub64_sat_ind      mem_test_and_sub64_sat_ind_ptr40
    #define mem_sub32_imm_sat               mem_sub32_imm_sat_ptr40
    #define mem_test_and_sub32_imm_sat      mem_test_and_sub32_imm_sat_ptr40
    #define mem_sub64_imm_sat               mem_sub64_imm_sat_ptr40
    #define mem_test_and_sub64_imm_sat      mem_test_and_sub64_imm_sat_ptr40
    #define mem_xor                         mem_xor_ptr40
    #define mem_xor_ind                     mem_xor_ind_ptr40
    #define mem_test_and_xor                mem_test_and_xor_ptr40
    #define mem_test_and_xor_ind            mem_test_and_xor_ind_ptr40
    #define mem_xor_imm                     mem_xor_imm_ptr40
    #define mem_test_and_xor_imm            mem_test_and_xor_imm_ptr40
    #define mem_mask_compare_write          mem_mask_compare_write_ptr40
    #define mem_test_mask_and_compare_write mem_test_mask_and_compare_write_ptr40


/*
 * Mem CAM
 */
    #define  mem_cam128_init                mem_cam128_init_ptr40
    #define  mem_cam256_init                mem_cam256_init_ptr40
    #define  mem_cam384_init                mem_cam384_init_ptr40
    #define  mem_cam512_init                mem_cam512_init_ptr40
    #define  mem_cam128_set8                mem_cam128_set8_ptr40
    #define  mem_cam256_set8                mem_cam256_set8_ptr40
    #define  mem_cam384_set8                mem_cam384_set8_ptr40
    #define  mem_cam512_set8                mem_cam512_set8_ptr40
    #define  mem_cam128_set16               mem_cam128_set16_ptr40
    #define  mem_cam256_set16               mem_cam256_set16_ptr40
    #define  mem_cam384_set16               mem_cam384_set16_ptr40
    #define  mem_cam512_set16               mem_cam512_set16_ptr40
    #define  mem_cam128_set24               mem_cam128_set24_ptr40
    #define  mem_cam256_set24               mem_cam256_set24_ptr40
    #define  mem_cam384_set24               mem_cam384_set24_ptr40
    #define  mem_cam512_set24               mem_cam512_set24_ptr40
    #define  mem_cam128_set3                mem_cam128_set32_ptr40
    #define  mem_cam256_set32               mem_cam256_set32_ptr40
    #define  mem_cam384_set32               mem_cam384_set32_ptr40
    #define  mem_cam512_set32               mem_cam512_set32_ptr40

    #define mem_cam128_lookup8              mem_cam128_lookup8_ptr40
    #define mem_cam256_lookup8              mem_cam256_lookup8_ptr40
    #define mem_cam384_lookup8              mem_cam384_lookup8_ptr40
    #define mem_cam512_lookup8              mem_cam512_lookup8_ptr40

    #define mem_cam128_lookup8_add          mem_cam128_lookup8_add_ptr40
    #define mem_cam256_lookup8_add          mem_cam256_lookup8_add_ptr40
    #define mem_cam384_lookup8_add          mem_cam384_lookup8_add_ptr40
    #define mem_cam512_lookup8_add          mem_cam512_lookup8_add_ptr40

    #define mem_cam128_lookup16             mem_cam128_lookup16_ptr40
    #define mem_cam256_lookup16             mem_cam256_lookup16_ptr40
    #define mem_cam384_lookup16             mem_cam384_lookup16_ptr40
    #define mem_cam512_lookup16             mem_cam512_lookup16_ptr40

    #define mem_cam128_lookup16_add         mem_cam128_lookup16_add_ptr40
    #define mem_cam256_lookup16_add         mem_cam256_lookup16_add_ptr40
    #define mem_cam384_lookup16_add         mem_cam384_lookup16_add_ptr40
    #define mem_cam512_lookup16_add         mem_cam512_lookup16_add_ptr40

    #define mem_cam128_lookup24             mem_cam128_lookup24_ptr40
    #define mem_cam256_lookup24             mem_cam256_lookup24_ptr40
    #define mem_cam384_lookup24             mem_cam384_lookup24_ptr40
    #define mem_cam512_lookup24             mem_cam512_lookup24_ptr40

    #define mem_cam128_lookup24_add         mem_cam128_lookup24_add_ptr40
    #define mem_cam256_lookup24_add         mem_cam256_lookup24_add_ptr40
    #define mem_cam384_lookup24_add         mem_cam384_lookup24_add_ptr40
    #define mem_cam512_lookup24_add         mem_cam512_lookup24_add_ptr40

    #define mem_cam128_lookup24_add_inc     mem_cam128_lookup24_add_inc_ptr40
    #define mem_cam256_lookup24_add_inc     mem_cam256_lookup24_add_inc_ptr40
    #define mem_cam384_lookup24_add_inc     mem_cam384_lookup24_add_inc_ptr40
    #define mem_cam512_lookup24_add_inc     mem_cam512_lookup24_add_inc_ptr40

    #define mem_cam128_lookup32             mem_cam128_lookup32_ptr40
    #define mem_cam256_lookup32             mem_cam256_lookup32_ptr40
    #define mem_cam384_lookup32             mem_cam384_lookup32_ptr40
    #define mem_cam512_lookup32             mem_cam512_lookup32_ptr40

    #define mem_cam128_lookup32_add         mem_cam128_lookup32_add_ptr40
    #define mem_cam256_lookup32_add         mem_cam256_lookup32_add_ptr40
    #define mem_cam384_lookup32_add         mem_cam384_lookup32_add_ptr40
    #define mem_cam512_lookup32_add         mem_cam512_lookup32_add_ptr40

/*
 * MEM TCAM
 */
    #define mem_tcam128_init                mem_tcam128_init_ptr40
    #define mem_tcam256_init                mem_tcam256_init_ptr40
    #define mem_tcam384_init                mem_tcam384_init_ptr40
    #define mem_tcam512_init                mem_tcam512_init_ptr40

    #define mem_tcam128_set8_word           mem_tcam128_set8_word_ptr40
    #define mem_tcam128_set8_entry_value    mem_tcam128_set8_entry_value_ptr40
    #define mem_tcam128_set8_entry_mask     mem_tcam128_set8_entry_mask_ptr40
    #define mem_tcam128_set8_entry          mem_tcam128_set8_entry_ptr40

    #define mem_tcam256_set8_word           mem_tcam256_set8_word_ptr40
    #define mem_tcam256_set8_entry_value    mem_tcam256_set8_entry_value_ptr40
    #define mem_tcam256_set8_entry_mask     mem_tcam256_set8_entry_mask_ptr40
    #define mem_tcam256_set8_entry          mem_tcam256_set8_entry_ptr40

    #define mem_tcam384_set8_word           mem_tcam384_set8_word_ptr40
    #define mem_tcam384_set8_entry_value    mem_tcam384_set8_entry_value_ptr40
    #define mem_tcam384_set8_entry_mask     mem_tcam384_set8_entry_mask_ptr40
    #define mem_tcam384_set8_entry          mem_tcam384_set8_entry_ptr40

    #define mem_tcam512_set8_word           mem_tcam512_set8_word_ptr40
    #define mem_tcam512_set8_entry_value    mem_tcam512_set8_entry_value_ptr40
    #define mem_tcam512_set8_entry_mask     mem_tcam512_set8_entry_mask_ptr40
    #define mem_tcam512_set8_entry          mem_tcam512_set8_entry_ptr40

    #define mem_tcam128_set16_word          mem_tcam128_set16_word_ptr40
    #define mem_tcam128_set16_entry_value   mem_tcam128_set16_entry_value_ptr40
    #define mem_tcam128_set16_entry_mask    mem_tcam128_set16_entry_mask_ptr40
    #define mem_tcam128_set16_entry         mem_tcam128_set16_entry_ptr40

    #define mem_tcam256_set16_word          mem_tcam256_set16_word_ptr40
    #define mem_tcam256_set16_entry_value   mem_tcam256_set16_entry_value_ptr40
    #define mem_tcam256_set16_entry_mask    mem_tcam256_set16_entry_mask_ptr40
    #define mem_tcam256_set16_entry         mem_tcam256_set16_entry_ptr40

    #define mem_tcam384_set16_word          mem_tcam384_set16_word_ptr40
    #define mem_tcam384_set16_entry_value   mem_tcam384_set16_entry_value_ptr40
    #define mem_tcam384_set16_entry_mask    mem_tcam384_set16_entry_mask_ptr40
    #define mem_tcam384_set16_entry         mem_tcam384_set16_entry_ptr40

    #define mem_tcam512_set16_word          mem_tcam512_set16_word_ptr40
    #define mem_tcam512_set16_entry_value   mem_tcam512_set16_entry_value_ptr40
    #define mem_tcam512_set16_entry_mask    mem_tcam512_set16_entry_mask_ptr40
    #define mem_tcam512_set16_entry         mem_tcam512_set16_entry_ptr40

    #define mem_tcam128_set24_word          mem_tcam128_set24_word_ptr40
    #define mem_tcam128_set24_entry_value   mem_tcam128_set24_entry_value_ptr40
    #define mem_tcam128_set24_entry_mask    mem_tcam128_set24_entry_mask_ptr40
    #define mem_tcam128_set24_entry         mem_tcam128_set24_entry_ptr40

    #define mem_tcam256_set24_word          mem_tcam256_set24_word_ptr40
    #define mem_tcam256_set24_entry_value   mem_tcam256_set24_entry_value_ptr40
    #define mem_tcam256_set24_entry_mask    mem_tcam256_set24_entry_mask_ptr40
    #define mem_tcam256_set24_entry         mem_tcam256_set24_entry_ptr40

    #define mem_tcam384_set24_word          mem_tcam384_set24_word_ptr40
    #define mem_tcam384_set24_entry_value   mem_tcam384_set24_entry_value_ptr40
    #define mem_tcam384_set24_entry_mask    mem_tcam384_set24_entry_mask_ptr40
    #define mem_tcam384_set24_entry         mem_tcam384_set24_entry_ptr40

    #define mem_tcam512_set24_word          mem_tcam512_set24_word_ptr40
    #define mem_tcam512_set24_entry_value   mem_tcam512_set24_entry_value_ptr40
    #define mem_tcam512_set24_entry_mask    mem_tcam512_set24_entry_mask_ptr40
    #define mem_tcam512_set24_entry         mem_tcam512_set24_entry_ptr40

    #define mem_tcam128_set32_word          mem_tcam128_set32_word_ptr40
    #define mem_tcam128_set32_entry_value   mem_tcam128_set32_entry_value_ptr40
    #define mem_tcam128_set32_entry_mask    mem_tcam128_set32_entry_mask_ptr40
    #define mem_tcam128_set32_entry         mem_tcam128_set32_entry_ptr40

    #define mem_tcam256_set32_word          mem_tcam256_set32_word_ptr40
    #define mem_tcam256_set32_entry_value   mem_tcam256_set32_entry_value_ptr40
    #define mem_tcam256_set32_entry_mask    mem_tcam256_set32_entry_mask_ptr40
    #define mem_tcam256_set32_entry         mem_tcam256_set32_entry_ptr40

    #define mem_tcam384_set32_word          mem_tcam384_set32_word_ptr40
    #define mem_tcam384_set32_entry_value   mem_tcam384_set32_entry_value_ptr40
    #define mem_tcam384_set32_entry_mask    mem_tcam384_set32_entry_mask_ptr40
    #define mem_tcam384_set32_entry         mem_tcam384_set32_entry_ptr40

    #define mem_tcam512_set32_word          mem_tcam512_set32_word_ptr40
    #define mem_tcam512_set32_entry_value   mem_tcam512_set32_entry_value_ptr40
    #define mem_tcam512_set32_entry_mask    mem_tcam512_set32_entry_mask_ptr40
    #define mem_tcam512_set32_entry         mem_tcam512_set32_entry_ptr40

    #define mem_tcam128_lookup8             mem_tcam128_lookup8_ptr40
    #define mem_tcam256_lookup8             mem_tcam256_lookup8_ptr40
    #define mem_tcam384_lookup8             mem_tcam384_lookup8_ptr40
    #define mem_tcam512_lookup8             mem_tcam512_lookup8_ptr40

    #define mem_tcam128_lookup16            mem_tcam128_lookup16_ptr40
    #define mem_tcam256_lookup16            mem_tcam256_lookup16_ptr40
    #define mem_tcam384_lookup16            mem_tcam384_lookup16_ptr40
    #define mem_tcam512_lookup16            mem_tcam512_lookup16_ptr40

    #define mem_tcam128_lookup24            mem_tcam128_lookup24_ptr40
    #define mem_tcam256_lookup24            mem_tcam256_lookup24_ptr40
    #define mem_tcam384_lookup24            mem_tcam384_lookup24_ptr40
    #define mem_tcam512_lookup24            mem_tcam512_lookup24_ptr40

    #define mem_tcam128_lookup32            mem_tcam128_lookup32_ptr40
    #define mem_tcam256_lookup32            mem_tcam256_lookup32_ptr40
    #define mem_tcam384_lookup32            mem_tcam384_lookup32_ptr40
    #define mem_tcam512_lookup32            mem_tcam512_lookup32_ptr40

/*
 * MEM ticket
 */
    #define mem_ticket_release              mem_ticket_release_ptr40
    #define mem_ticket_release_push         mem_ticket_release_push_ptr40
    #define mem_ticket_line_init            mem_ticket_line_init_ptr40
    #define mem_ticket_line_push_init       mem_ticket_line_push_init_ptr40

/*
 * MEM lock
 */
    #define mem_lock128_init                mem_lock128_init_ptr40
    #define mem_lock256_init                mem_lock256_init_ptr40
    #define mem_lock384_init                mem_lock384_init_ptr40
    #define mem_lock512_init                mem_lock512_init_ptr40
    #define mem_lock128                     mem_lock128_ptr40
    #define mem_lock256                     mem_lock256_ptr40
    #define mem_lock384                     mem_lock384_ptr40
    #define mem_lock512                     mem_lock512_ptr40
    #define mem_unlock128                   mem_unlock128_ptr40
    #define mem_unlock256                   mem_unlock256_ptr40
    #define mem_unlock384                   mem_unlock384_ptr40
    #define mem_unlock512                   mem_unlock512_ptr40

/*
 * MEM lockq
 */
    #define mem_lockq128_lock               mem_lockq128_lock_ptr40
    #define mem_lockq256_lock               mem_lockq256_lock_ptr40
    #define mem_lockq128_unlock             mem_lockq128_unlock_ptr40
    #define mem_lockq256_unlock             mem_lockq256_unlock_ptr40
    #define mem_lockq128_init               mem_lockq128_init_ptr40
    #define mem_lockq256_init               mem_lockq256_init_ptr40

/*
 * MEM microq
 */
    #define mem_microq128_put               mem_microq128_put_ptr40
    #define mem_microq256_put               mem_microq256_put_ptr40
    #define mem_microq128_get               mem_microq128_get_ptr40
    #define mem_microq256_get               mem_microq256_get_ptr40
    #define mem_microq128_pop               mem_microq128_pop_ptr40
    #define mem_microq256_pop               mem_microq256_pop_ptr40
    #define mem_microq128_init              mem_microq128_init_ptr40
    #define mem_microq256_init              mem_microq256_init_ptr40
#endif /* __ADDRESSING_DEFAULT_40BIT */

#endif /* __NFP_COMPATIBILITY_H__ */


