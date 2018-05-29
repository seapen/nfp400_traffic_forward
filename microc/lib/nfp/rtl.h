/*
 * Copyright (C) 2008-2015 Netronome Systems, Inc.  All rights reserved.
 */

/* NFP RTL definitions */

#ifndef __NFP_RTL_H__
#define __NFP_RTL_H__

#ifndef NFP_LIB_ANY_NFCC_VERSION
    #if (!defined(__NFP_TOOL_NFCC) ||                       \
        (__NFP_TOOL_NFCC < NFP_SW_VERSION(5, 0, 0, 0)) ||   \
        (__NFP_TOOL_NFCC > NFP_SW_VERSION(6, 0, 2, 255)))
        #error "This standard library is not supported for the version of the SDK currently in use."
    #endif
#endif


typedef struct
{
#ifdef __BIGENDIAN
    unsigned int hi;
    unsigned int lo;
#else
    unsigned int lo;
    unsigned int hi;
#endif
} lohi;

long long _mul_64(lohi x, lohi y);
unsigned int _div_mod_32(unsigned int x, unsigned int y, unsigned int mod);
int _mod_s32(int x, int y);
int _div_s32(int x, int y);
int _mod_u32(int x, int y);
int _div_u32(int x, int y);
unsigned long long _div_mod_64(unsigned long long x, unsigned long long y, unsigned int mod);
long long _mod_s64(long long x, long long y);
long long _div_s64(long long x, long long y);
long long _mod_u64(long long x, long long y);
long long _div_u64(long long x, long long y);
long long _shl_64(long long x, unsigned int y);
long long _shr_64(long long x, unsigned int y);
long long _ashr_64(long long x, unsigned int y);

void ua_set_8_lmem(__lmem void *q, unsigned int offset, unsigned int val);
void ua_set_16_lmem(__lmem void *q, unsigned int offset, unsigned int val);
void ua_set_32_lmem(__lmem void *q, unsigned int offset, unsigned int val);
void ua_set_8_cls(__cls void *q, unsigned int offset, unsigned int val);
void ua_set_16_cls(__cls void *q, unsigned int offset, unsigned int val);
void ua_set_32_cls(__cls void *q, unsigned int offset, unsigned int val);
void ua_set_64_cls(__cls void *q, unsigned int offset, unsigned long long val);
void ua_set_64_sram(__sram void *q, unsigned int offset, unsigned long long val);
void ua_set_64_lmem(__lmem void *q, unsigned int offset, unsigned long long val);
unsigned int ua_get_u8_lmem(__lmem void *q, unsigned int offset);
unsigned int ua_get_u16_lmem(__lmem void *q, unsigned int offset);
unsigned int ua_get_u16_sram(__sram void *q, unsigned int offset);
unsigned int ua_get_u16_cls(__cls void *q, unsigned int offset);
unsigned int ua_get_u32_lmem(__lmem void *q, unsigned int offset);
unsigned int ua_get_u32_sram(__sram void *q, unsigned int offset);
unsigned int ua_get_u32_cls(__cls void *q, unsigned int offset);
int ua_get_s8_lmem(__lmem void *q, unsigned int offset);
int ua_get_s8_sram(__sram void *q, unsigned int offset);
int ua_get_s8_cls(__cls void *q, unsigned int offset);
int ua_get_s16_lmem(__lmem void *q, unsigned int offset);
int ua_get_s16_sram(__sram void *q, unsigned int offset);
int ua_get_s16_cls(__cls void *q, unsigned int offset);
int ua_get_s32_lmem(__lmem void *q, unsigned int offset);
int ua_get_s32_sram(__sram void *q, unsigned int offset);
int ua_get_s32_cls(__cls void *q, unsigned int offset);
unsigned long long ua_get_64_sram(__sram void *q, unsigned int offset);
unsigned long long ua_get_64_cls(__cls void *q, unsigned int offset);
unsigned long long ua_get_64_lmem(__lmem void *q, unsigned int offset);
unsigned long long ua_get_u64_sram(__sram void *p, unsigned int offset);
unsigned long long ua_get_u64_cls(__cls void *p, unsigned int offset);
unsigned long long ua_get_u64_lmem(__lmem void *p, unsigned int offset);
long long ua_get_s64_sram(__sram void *p, unsigned int offset);
long long ua_get_s64_cls(__cls void *p, unsigned int offset);
long long ua_get_s64_lmem(__lmem void *p, unsigned int offset);
void ua_memcpy_sram_sram(__sram void *dst, unsigned int dst_off,
  __sram void *src, unsigned int src_off, unsigned int length);
void ua_memcpy_lmem_lmem(__lmem void *dst, unsigned int dst_off,
  __lmem void *src, unsigned int src_off, unsigned int length);
void ua_memcpy_lmem_sram(__lmem void *dst, unsigned int dst_off,
  __sram void *src, unsigned int src_off, unsigned int length);
void ua_memcpy_lmem_cls(__lmem void *dst, unsigned int dst_off,
  __cls void *src, unsigned int src_off, unsigned int length);
void ua_memcpy_sram_lmem(__sram void *dst, unsigned int dst_off,
  __lmem void *src, unsigned int src_off, unsigned int length);
void ua_memcpy_cls_lmem(__cls void *dst, unsigned int dst_off,
  __lmem void *src, unsigned int src_off, unsigned int length);
void ua_memcpy_lmem0_7_xfer_w_clr(__lmem void *dst,
  unsigned int dst_off, unsigned int ctx, unsigned int xfer_reg_number,
  unsigned int src_off, unsigned int length);

void ua_set_8_sram(__sram void *q, unsigned int offset, unsigned int val);
void ua_set_16_sram(__sram void *q, unsigned int offset, unsigned int val);
void ua_set_32_sram(__sram void *q, unsigned int offset, unsigned int val);

void ua_set_8_mem(__mem void *q, unsigned int offset, unsigned int val);
void ua_set_16_mem(__mem void *q, unsigned int offset, unsigned int val);
void ua_set_32_mem(__mem void *q, unsigned int offset, unsigned int val);
void ua_set_64_mem(__mem void *q, unsigned int offset, unsigned long long val);

unsigned int ua_get_u8_mem(__mem void *q, unsigned int offset);
unsigned int ua_get_u16_mem(__mem void *q, unsigned int offset);
unsigned int ua_get_u32_mem(__mem void *q, unsigned int offset);

int ua_get_s8_mem(__mem void *q, unsigned int offset);
int ua_get_s16_mem(__mem void *q, unsigned int offset);
int ua_get_s32_mem(__mem void *q, unsigned int offset);

unsigned long long ua_get_64_mem(__mem void *q, unsigned int offset);
unsigned long long ua_get_u64_mem(__mem void *p, unsigned int offset);
long long ua_get_s64_mem(__mem void *p, unsigned int offset);

void ua_set_ptr40_8_mem(__mem void *hi_q, __mem void *q, unsigned int offset, unsigned int val);
void ua_set_ptr40_16_mem(__mem void *hi_q, __mem void *q, unsigned int offset, unsigned int val);
void ua_set_ptr40_32_mem(__mem void *hi_q, __mem void *q, unsigned int offset, unsigned int val);
void ua_set_ptr40_64_mem(__mem void *hi_q, __mem void *q, unsigned int offset, unsigned long long val);

unsigned long long ua_get_ptr40_64_mem(__mem void *hi_q, __mem void *q, unsigned int offset);
unsigned int ua_get_ptr40_32_mem(__mem void *hi_q, __mem void *q, unsigned int offset);
unsigned short ua_get_ptr40_16_mem(__mem void *hi_q, __mem void *q, unsigned int offset);
unsigned char ua_get_ptr40_8_mem(__mem void *hi_q, __mem void *q, unsigned int offset);

void ua_set_8_mem40(__mem __addr40 void *ptr, unsigned off, unsigned val);
void ua_set_16_mem40(__mem __addr40 void *ptr, unsigned off, unsigned val);
void ua_set_32_mem40(__mem __addr40 void *ptr, unsigned off, unsigned val);
void ua_set_64_mem40(__mem __addr40 void *ptr, unsigned off, unsigned long long val);

void ua_memcpy_mem_mem(__mem void *dst, unsigned int dst_off, __mem void *src, unsigned int src_off, unsigned int length);
void ua_memcpy_mem_sram(__mem void *dst, unsigned int dst_off, __sram void *src, unsigned int src_off, unsigned int length);
void ua_memcpy_mem_cls(__mem void *dst, unsigned int dst_off, __cls void *src, unsigned int src_off, unsigned int length);
void ua_memcpy_sram_mem(__sram void *dst, unsigned int dst_off, __mem void *src, unsigned int src_off, unsigned int length);
void ua_memcpy_cls_mem(__cls void *dst, unsigned int dst_off, __mem void *src, unsigned int src_off, unsigned int length);
void ua_memcpy_sram_cls(__sram void *dst, unsigned int dst_off, __cls void *src, unsigned int src_off, unsigned int length);
void ua_memcpy_cls_sram(__cls void *dst, unsigned int dst_off, __sram void *src, unsigned int src_off, unsigned int length);
void ua_memcpy_cls_cls(__cls void *dst, unsigned int dst_off, __cls void *src, unsigned int src_off, unsigned int length);
void ua_memcpy_lmem_mem(__lmem void *dst, unsigned int dst_off, __mem void *src, unsigned int src_off, unsigned int length);
void ua_memcpy_mem_lmem(__mem void *dst, unsigned int dst_off, __lmem void *src, unsigned int src_off, unsigned int length);

__noinline void exit(int status);
void exit_thread(int status);


#endif /* __NFP_RTL_H__ */

