#ifndef MT_PACKET_H
#define MT_PACKET_H

#include "mt-header.h"
#include "mtp-types.h"
#include "ns3/packet.h"
#include "ns3/buffer.h"

const int UDP_DATA_BIT_SIZE = 524056; // 65507 bytes
namespace ns3 {
  // should we even inherit from ns3 Packet?
  class pkt_t : public Packet {
    private:
      // header is MTHeader type 
      // data is Buffer type - included in ns3's Packet class in a field called m_buffer
    public:
      pkt_t();
      ~pkt_t();
      int len();
      void add_data(Buffer newData);
      void get_data(uint8_t * outputBuffer, int bytesToCopy);
      void add_hdr(MTHeader header);
      MTHeader extract_hdr();
  };

  pkt_t new_pkt() { return pkt_t(); }

}

#endif