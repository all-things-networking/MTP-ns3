#ifndef UDP_RXNET_H
#define UDP_RXNET_H

#include "ns3/mt-rxnet.h"

namespace ns3 {
  class UDPRXNetParser : public MTRXNetParser {

    public:
      UDPRXNetParser() {}
      virtual ~UDPRXNetParser() {}

      std::vector<event_t *> packet_parser(Ipv4Header iphdr, Ptr<Packet> pkt) override {
        flow_id fid = 0; // ??
        std::vector<event_t *> events;
        auto now = std::chrono::system_clock::now();
        long timestamp = std::chrono::system_clock::to_time_t(now);
        events.push_back((MTEvent *) new RecvEvent(timestamp, fid));
        return events;
      }
      
  };
}

#endif 