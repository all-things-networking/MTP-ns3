#ifndef MT_PACKET_H
#define MT_PACKET_H

/*
 === DEPRECATED IN FAVOUR OF ns3::Packet CLASS ===
*/

// #include "ns3/mt-header.h"
#include "ns3/packet.h"
#include "ns3/buffer.h"

const int UDP_DATA_BIT_SIZE = 524056; // 65507 bytes
namespace ns3 {
  // deprecated - use ns3::Packet instead
  class pkt_t : public Packet {
    private:
      // header is MTHeader type 
      // data is Buffer type - included in ns3's Packet class in a field called m_buffer
    public:
      pkt_t()  {}
      ~pkt_t() {}
      pkt_t(Packet pkt);
      
      // length in bytes
      int len();

      void add_data(Buffer newData);
      void add_data(uint8_t * newData, int size);

      // copies bytesToCopy bytes (ideally pkt_t::len()) from the packet's 
      // buffer to outputBuffer, which should be preallocated
      void get_data(uint8_t * outputBuffer, int bytesToCopy);

      void add_hdr(MTHeader header);
      MTHeader extract_hdr();
  };

  inline pkt_t new_pkt() { return pkt_t(); }

}

#endif