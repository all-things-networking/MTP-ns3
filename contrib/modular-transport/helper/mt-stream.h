#ifndef STREAM_H
#define STREAM_H

#include <vector>
#include <cstdint> // uint8_t
#include <numeric>

#include "mtp-types.h"

namespace ns3 {
  class stream {
    uint8_t * data;
    // size of the heap allocation
    int size;
    // how many bytes are actually stored within data
    int length;

    // Scaffolding for alternative implementation
    // std::vector<uint8_t *> dataStreams;
    // std::vector<int> streamSizes;
    // std::vector<int> allocationSizes;

    public:
      stream(int size = 80000);
      ~stream();
      int len() const;
      stream * substream(int start, int end) const;
      
      // assume lengths are in bytes
      addr_t stream::mem_append(addr_t address, int length);
      addr_t hold_data(stream data, flow_id flow, int length);
      stream * release_data(stream data, addr_t addr, flow_id flow, int length);
      addr_t get_data() const;
  };

  void mem_write(addr_t address, stream & data, int offset, int length) {
    std::copy(data.get_data(), data.get_data() + length, address + offset);
  }

}

#endif // STREAM_H