#ifndef MT_TX_NET_H
#define MT_TX_NET_H

#include "mt-scheduler.h"
#include "ns3/packet.h"

namespace ns3 {
  class MTTXNetScheduler {
    public:
      MTTXNetScheduler(){}

      // initialize queues here
      virtual Ptr<Packet> get_next_packet(MTEvent* event)=0;
  };
}

#endif