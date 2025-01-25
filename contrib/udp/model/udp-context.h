#ifndef UDP_CONTEXT_H
#define UDP_CONTEXT_H

using namespace std;

#include "ns3/mt-context.h"

namespace ns3 {
  class UDPContext: public MTContext {
    public:
      int src_port;
      int dst_port;
      int sent_count;
      int recv_count;
      int MTU = 3;
  };
}

#endif