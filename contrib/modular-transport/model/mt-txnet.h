#ifndef MT_TX_NET_H
#define MT_TX_NET_H

#include "ns3/mt-scheduler.h"
#include "ns3/mt-flow-map.h"
#include "ns3/mt-event.h"

namespace ns3 {
  // sends packets to net layer as soon as it receives the NetEvent
  class MTTXNetScheduler {
    protected:
      flow_map<queue_t<event_t *>> txQueues;
      
      // for choosing next event/flow
      flow_map<unsigned int> eventSelector;
      unsigned int flowSelector;

    public:
      MTTXNetScheduler();
      virtual ~MTTXNetScheduler();

      // initialize queues here
      virtual void initialize();

      // returns next packet to send to net layer
      virtual Ptr<Packet> get_next_packet(MTEvent * e) = 0;
  };
}

#endif