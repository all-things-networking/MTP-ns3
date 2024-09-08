#ifndef STREAM_H
#define STREAM_H

#include <vector>
#include <cstdint> // uint8_t

#include "mtp-types.h"

namespace ns3 {
  class stream {
    std::vector<uint8_t> data;

    public:
      stream();
      ~stream();
      int len() const;
      stream substream(int start, int end) const;
      void stream::mem_append(addr_t address, int length);
      addr_t hold_data(stream data, flow_id flow, int length);
      std::vector<uint8_t> get_data() const;

      // todo: implement hold_data and release_data after clarification from Kimiya

  };

  void mem_write(addr_t address, stream & data, int offset, int length) {
    std::copy(data.get_data().begin() + offset, data.get_data().begin() + offset + length, reinterpret_cast<uint8_t*>(address));
  }

}

#endif // STREAM_H