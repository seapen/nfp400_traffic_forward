/*
* @file          /wire/wire_main.c
* @brief         Wire with routing table :)
*
*/


#include <nfp.h>
#include <stdint.h>
#include <nfp/me.h>
#include <nfp/mem_bulk.h>
#include <nfp6000/nfp_me.h>
#include <pkt/pkt.h>

#include <com/channel.h>

#ifndef NBI
#define NBI 0
#endif

#define MAC_CHAN_PER_PORT   8
#define TMQ_PER_PORT        (MAC_CHAN_PER_PORT * 8)

#define MAC_TO_PORT(x)      (x / MAC_CHAN_PER_PORT)
#define PORT_TO_TMQ(x)      (x * TMQ_PER_PORT)

#ifndef PKT_NBI_OFFSET
#define PKT_NBI_OFFSET 64
#endif


struct f_counter {
    uint64_t arp_counter;
    uint64_t ip4_counter;
    uint64_t ip6_counter;
    uint64_t frame_counter;
};


//------------------------------------------------------------------------------
//To be read out of the list file. An address will be built using these
//------------------------------------------------------------------------------
__declspec(visible read_reg) volatile unsigned int eng_val0;
__declspec(visible)          SIGNAL eng_sig0;
__declspec(imem export scope(global)) struct f_counter f_counter;

//------------------------------------------------------------------------------
void process_sats(__xread uint32_t pkt_buf[16]) {
    if((pkt_buf[3] >> 16) == 0x0800) {
        f_counter.ip4_counter++;
    }
    else if((pkt_buf[3] >> 16) == 0x86dd) {
        f_counter.ip6_counter++;
    }
    else if((pkt_buf[3] >> 16) == 0x0806) {
        f_counter.arp_counter++;
    }
    f_counter.frame_counter ++;
    
}

//------------------------------------------------------------------------------

int main(void)
{
    
    

    __gpr volatile int in_port, out_port, pkt_offset, plen, frame_count = 0;
    __addr40 char *pbuf;
    __gpr volatile struct pkt_ms_info msi;

    __xwrite volatile unsigned int data_output[12];
    __xread volatile uint32_t pkt_buf[16];
    __xread volatile struct nbi_meta_catamaran nbi_meta;
    __xread volatile struct nbi_meta_pkt_info *pi = &nbi_meta.pkt_info;

    __assign_relative_register((void*)&eng_sig0, 15);
    __assign_relative_register((void*)&eng_val0, 31);
  

    f_counter.arp_counter   = 0;
    f_counter.ip4_counter   = 0;
    f_counter.ip6_counter   = 0;
    f_counter.frame_counter = 0;

    for (;;) {

        pkt_nbi_recv(&nbi_meta, sizeof(nbi_meta));
        in_port = MAC_TO_PORT(nbi_meta.port); 
        pbuf = pkt_ctm_ptr40(pi->isl, pi->pnum, 0);
        pkt_offset = PKT_NBI_OFFSET;

        
        mem_read64(pkt_buf, pbuf + pkt_offset, sizeof(pkt_buf));
        process_sats(pkt_buf);

        data_output[0]  = pkt_buf[0];
        data_output[1]  = pkt_buf[1];
        data_output[2]  = pkt_buf[2];
        data_output[3]  = pkt_buf[3];
        data_output[4]  = pkt_buf[4];
        data_output[5]  = pkt_buf[5];
        data_output[6]  = pkt_buf[6];
        data_output[7]  = pkt_buf[7];
        data_output[8]  = f_counter.frame_counter;
        data_output[9]  = f_counter.arp_counter;
        data_output[10] = f_counter.ip4_counter;
        data_output[11] = in_port;//f_counter.ip6_counter;
        channel_write((void*)data_output, 12, 0);


        pkt_offset += MAC_PREPEND_BYTES;
        pkt_mac_egress_cmd_write(pbuf, pkt_offset, 1, 1);
        pkt_offset -= 4;
        msi = pkt_msd_write(pbuf, pkt_offset);
        out_port = in_port;

        
        pkt_nbi_send_dont_free(pi->isl, pi->pnum, &msi, pi->len - MAC_PREPEND_BYTES + 4, NBI, PORT_TO_TMQ(0), nbi_meta.seqr, nbi_meta.seq, PKT_CTM_SIZE_256);
        pkt_nbi_send_dont_free(pi->isl, pi->pnum, &msi, pi->len - MAC_PREPEND_BYTES + 4, NBI, PORT_TO_TMQ(1), nbi_meta.seqr, nbi_meta.seq, PKT_CTM_SIZE_256);
        pkt_nbi_send_dont_free(pi->isl, pi->pnum, &msi, pi->len - MAC_PREPEND_BYTES + 4, NBI, PORT_TO_TMQ(2), nbi_meta.seqr, nbi_meta.seq, PKT_CTM_SIZE_256);
        pkt_nbi_send_dont_free(pi->isl, pi->pnum, &msi, pi->len - MAC_PREPEND_BYTES + 4, NBI, PORT_TO_TMQ(3), nbi_meta.seqr, nbi_meta.seq, PKT_CTM_SIZE_256);
        pkt_nbi_send_dont_free(pi->isl, pi->pnum, &msi, pi->len - MAC_PREPEND_BYTES + 4, NBI, PORT_TO_TMQ(4), nbi_meta.seqr, nbi_meta.seq, PKT_CTM_SIZE_256);
        pkt_nbi_send_dont_free(pi->isl, pi->pnum, &msi, pi->len - MAC_PREPEND_BYTES + 4, NBI, PORT_TO_TMQ(5), nbi_meta.seqr, nbi_meta.seq, PKT_CTM_SIZE_256);
        pkt_nbi_send_dont_free(pi->isl, pi->pnum, &msi, pi->len - MAC_PREPEND_BYTES + 4, NBI, PORT_TO_TMQ(6), nbi_meta.seqr, nbi_meta.seq, PKT_CTM_SIZE_256);
        pkt_nbi_send_dont_free(pi->isl, pi->pnum, &msi, pi->len - MAC_PREPEND_BYTES + 4, NBI, PORT_TO_TMQ(7), nbi_meta.seqr, nbi_meta.seq, PKT_CTM_SIZE_256);
        pkt_nbi_send_dont_free(pi->isl, pi->pnum, &msi, pi->len - MAC_PREPEND_BYTES + 4, NBI, PORT_TO_TMQ(8), nbi_meta.seqr, nbi_meta.seq, PKT_CTM_SIZE_256);
        pkt_nbi_send_dont_free(pi->isl, pi->pnum, &msi, pi->len - MAC_PREPEND_BYTES + 4, NBI, PORT_TO_TMQ(9), nbi_meta.seqr, nbi_meta.seq, PKT_CTM_SIZE_256);

        pkt_nbi_send(pi->isl, pi->pnum, &msi, pi->len - MAC_PREPEND_BYTES + 4, NBI, PORT_TO_TMQ(out_port), nbi_meta.seqr, nbi_meta.seq, PKT_CTM_SIZE_256);

        }
    return 0;
}
