#include "mt-stream.h"

namespace ns3 {
  stream::stream(int size): size{size}, length{0} {
    data = new uint8_t[size];
  }

  stream::~stream() {
    delete [] data;
  }

  int stream::len() const {
    return length;;
  }

  addr_t stream::mem_append(addr_t address, int newDataLength) {
    if (size - length < newDataLength) {
      return nullptr;
    }

    std::copy(address, address + newDataLength, data + length);
    length += newDataLength;

    // bool allocated = false;
    // addr_t addrToReturn = nullptr;

    // // see if we can allocate the new data in an existing dataStream
    // for (int i = 0; i < dataStreams.size(); i++) {
    //   if (streamSizes[i] + length <= allocationSizes[i]) {
    //     addrToReturn = dataStreams[i] + streamSizes[i];
    //     streamSizes[i] += length;
    //     allocated = true;
    //     break;
    //   }
    // }

    // // allocate new memory if no existing dataStream could accomodate the new data
    // if (!allocated) {
    //   int bytesToAllocate = std::max(length, defaultAllocationSize);
    //   dataStreams.push_back(new uint8_t[bytesToAllocate]);
    //   streamSizes.push_back(length);
    //   allocationSizes.push_back(bytesToAllocate);
    //   addrToReturn = dataStreams.back();
    // }

    // // copy over the data where we decided to place it
    // std::copy(address, address + length, addrToReturn);
  }

  stream * stream::substream(int start, int end) const {
    stream * result = new stream();
    result->mem_append(data + start, end - start);
    return result;
  }

  addr_t stream::hold_data(stream target, flow_id flow, int length) {
    mem_append(target.data, length);
  }

  stream * release_data(stream data, addr_t addr, flow_id flow, int length) {
    stream * result = new stream();    
    result->mem_append(addr, length);
    return result;
  }

  addr_t stream::get_data() const {
    return data;
  }

}