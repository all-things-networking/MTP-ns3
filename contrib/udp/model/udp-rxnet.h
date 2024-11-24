#ifndef UDP_RXNET_H
#define UDP_RXNET_H

#include "ns3/mt-rxnet.h"

namespace ns3 {
  class UDPRXNetParser : public MTRXNetParser {
    MTScheduler * sched;

    public:
      UDPRXNetParser(MTScheduler * sched) : sched(sched) {};
      virtual ~UDPRXNetParser() {}

      // question: when we receive a packet, how do we know which flow it belongs to?
      std::vector<event_t *> packet_parser(Ipv4Header iphdr, pkt_t * pkt) override {
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