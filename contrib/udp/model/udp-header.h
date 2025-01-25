#ifndef UDP_HEADER_H
#define UDP_HEADER_H 

#include "ns3/mt-header.h"

namespace ns3 {
  class UDPHeader : public MTHeader {
    public:
      // in a UDP header, each field is 16 bytes
      UDPHeader(uint16_t src_port, 
                uint16_t dst_port, 
                uint16_t length, 
                uint16_t checksum):
                src_port(src_port),
                dst_port(dst_port),
                length(length)
                {}
      
      uint16_t src_port;
      uint16_t dst_port;
      uint16_t length;
      uint16_t checksum;
      UDPHeader() {}
      virtual ~UDPHeader() override {}
  };

}

#endif 