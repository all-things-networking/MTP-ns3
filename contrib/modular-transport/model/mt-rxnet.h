#ifndef RX_NET_H
#define RX_NET_H

#include "../helper/mtp-types.h"
#include "ns3/ipv4-header.h"
#include "mt-scheduler.h"
#include "ns3/packet.h"

namespace ns3 {
  class MTRXNetParser {
    public:
      MTRXNetParser(){}

      virtual std::vector<MTEvent*> packet_parser(Ipv4Header iphdr, Ptr<ns3::Packet> pkt)=0;
  };
}

#endif