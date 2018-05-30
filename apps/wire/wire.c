#include <nfp.h>
#include <stdint.h>
#include <nfp/me.h>
#include <nfp/mem_bulk.h>
#include <nfp6000/nfp_me.h>
#include <pkt/pkt.h>

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
    
    

    __gpr  int in_port, out_port, pkt_offset;
    __addr40 char *pbuf;
    __gpr  struct pkt_ms_info msi;

    __xread  uint32_t pkt_buf[16];
    __xread  struct nbi_meta_catamaran nbi_meta;
    __xread  struct nbi_meta_pkt_info *pi = &nbi_meta.pkt_info;
  

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

        pkt_offset += MAC_PREPEND_BYTES;
        pkt_mac_egress_cmd_write(pbuf, pkt_offset, 1, 1);
        pkt_offset -= 4;
        msi = pkt_msd_write(pbuf, pkt_offset);
        
        out_port = in_port == 0 ? 4:0;

        pkt_nbi_send(pi->isl, pi->pnum, &msi, pi->len - MAC_PREPEND_BYTES + 4, 
          NBI, PORT_TO_TMQ(out_port), nbi_meta.seqr, nbi_meta.seq, 
          PKT_CTM_SIZE_256);


        }
    return 0;
}
