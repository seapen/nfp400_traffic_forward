/*
 * Copyright (C) 2008-2015 Netronome Systems, Inc.  All rights reserved.
 */


#ifndef __NFP_INTERNAL_H__
#define __NFP_INTERNAL_H__

#ifndef NFP_LIB_ANY_NFCC_VERSION
    #if (!defined(__NFP_TOOL_NFCC) ||                       \
        (__NFP_TOOL_NFCC < NFP_SW_VERSION(5, 0, 0, 0)) ||   \
        (__NFP_TOOL_NFCC > NFP_SW_VERSION(6, 0, 2, 255)))
        #error "This standard library is not supported for the version of the SDK currently in use."
    #endif
#endif

#ifndef __BIGENDIAN
#error Only __BIGENDIAN mode is supported
#endif

#ifndef NFCC_OMIT_PTR40_INTRINSICS
#define __PTR40
#endif

#ifdef __NFP_INDIRECT_REF_FORMAT_NFP3200

#define _INTRINSIC_OVERRIDE_LENGTH_AND_BYTEMASK_IN_ALU(ov_ind, length, bytemask) \
{ \
    ov_ind.value = 0; \
    ov_ind.cnt_mask_ind.encoding = 3; \
    ov_ind.cnt_mask_ind.ref_count = length; \
    ov_ind.cnt_mask_ind.byte_mask = bytemask; \
}

#endif

#ifdef __NFP_INDIRECT_REF_FORMAT_NFP6000

#define _INTRINSIC_OVERRIDE_BYTEMASK_AS_DATA_FIELD(ov_alu, ov_data) \
{ \
    ov_alu = ov_alu | (((ov_data) & 0xff) << 16) | ovr_data_byte_mask_bit; \
}

#define _INTRINSIC_OVERRIDE_LENGTH_FIELD(ov_alu, ov_len) \
{ \
    ov_alu = ov_alu | (((ov_len) & 0x1f) << 8) | ovr_length_bit; \
}

#define _INTRINSIC_OVERRIDE_LENGTH_AND_BYTEMASK_IN_ALU(ov_ind, length, bytemask) \
{ \
    ov_ind.alu_ind.value = 0x00; \
    _INTRINSIC_OVERRIDE_BYTEMASK_AS_DATA_FIELD(ov_ind.alu_ind.value, bytemask); \
    _INTRINSIC_OVERRIDE_LENGTH_FIELD(ov_ind.alu_ind.value, length); \
}

#endif


/* an area for communication with the host */
typedef struct
{
    unsigned int data;
    unsigned int thread;
    unsigned int command;
    unsigned int reserved;
} host_comm_struct;

/* buffer is at address 0 in the DRAM */
extern volatile __mem __addr40 host_comm_struct *host_comm;

#endif /* __NFP_INTERNAL_H__ */

