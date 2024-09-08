#ifndef MT_PACKET_H
#define MT_PACKET_H

#include "mt-header.h"
#include "mtp-types.h"
#include "ns3/packet.h"

namespace ns3 {
  // should we even inherit from ns3 Packet?
  class pkt_t : public Packet {
    private:
      MTHeader header;
      stream data;
    public:
      pkt_t();
      ~pkt_t();
      int len();
      void add_data(stream newData);
      stream get_data();
      void add_hdr(MTHeader header);
      MTHeader extract_hdr(MTHeader header);
  };

  pkt_t new_pkt() { return pkt_t(); }

}

#endif