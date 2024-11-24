#ifndef MT_TX_NET_H
#define MT_TX_NET_H

#include "ns3/mt-scheduler.h"
#include "ns3/mt-flow-map.h"
#include "ns3/mt-event.h"

namespace ns3 {
  class MTTXNetScheduler {
    protected:
      flow_map<queue_t<event_t *>> txQueues;

      // for choosing next event/flow
      flow_map<unsigned int> eventSelector;
      unsigned int flowSelector;

    public:
      MTTXNetScheduler() {
        txQueues = flow_map<queue_t<event_t *>>();
        eventSelector = flow_map<unsigned int>(0);
        flowSelector = 0;
      }
      virtual ~MTTXNetScheduler() {}

      // initialize queues here
      virtual void initialize();
      virtual pkt_t get_next_packet(MTEvent * e, flow_id id) = 0;
  };
}

#endif