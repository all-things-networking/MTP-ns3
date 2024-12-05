#ifndef RX_NET_H
#define RX_NET_H

#include "ns3/mtp-types.h"
#include "ns3/ipv4-header.h"
#include "mt-scheduler.h"

namespace ns3 {

  // responsible for creating events based on packets received from network layer
  class MTRXNetParser {
    public:
      MTRXNetParser() {}
      virtual ~MTRXNetParser() {};

      virtual std::vector<event_t *> packet_parser(Ipv4Header iphdr, Ptr<ns3::Packet> pkt) = 0;
  };
}

#endif