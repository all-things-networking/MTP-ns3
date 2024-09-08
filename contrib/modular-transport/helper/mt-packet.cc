#include "mt-packet.h"
 
namespace ns3 {
  int pkt_t::len() { return header.GetSerializedSize() + data.len(); }

  void pkt_t::add_data(stream newData) {
    data.mem_append((addr_t) &newData, newData.len());
  }

  stream pkt_t::get_data() { return data; }

  void pkt_t::add_hdr(MTHeader header) {
    this->header = header;
  }

  MTHeader pkt_t::extract_hdr(MTHeader header) {
    MTHeader retval = header;
    header = MTHeader();
    return retval;
  }
}

