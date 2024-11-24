#ifndef RX_NET_H
#define RX_NET_H

#include "../helper/mtp-types.h"
#include "ns3/ipv4-header.h"
#include "mt-scheduler.h"

namespace ns3 {

  // responsible for creating events based on packets received from network layer
  class MTRXNetParser {
    MTScheduler * sched;

    public:
      MTRXNetParser() {}
      virtual ~MTRXNetParser() = 0;

      virtual std::vector<event_t *> packet_parser(Ipv4Header iphdr, pkt_t * pkt);
  };
}

#endif