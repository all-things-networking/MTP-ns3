#include "mt-stream.h"

namespace ns3 {
  int stream::len() const {
    return data.size();
  }

  stream stream::substream(int start, int end) const {
    stream result;
    if (end <= data.size() && start < end) {
      result.data.insert(result.data.end(), data.begin() + start, data.begin() + end);
    }
    return result;
  }

  void stream::mem_append(addr_t address, int length) {
    uint8_t* target = reinterpret_cast<uint8_t*>(address);
    data.insert(data.end(), target, target + length);
  }

  std::vector<uint8_t> get_data() const {
    return data;
  }

}