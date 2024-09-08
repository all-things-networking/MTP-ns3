#ifndef MT_TX_NET_H
#define MT_TX_NET_H

#include "mt-scheduler.h"

namespace ns3 {
  class MTTXNetScheduler {
    MTScheduler * sched;

    flow_map<queue_t<MTEvent *>> txQueues;

    public:
      MTTXNetScheduler(MTScheduler * sched);
      virtual ~MTTXNetScheduler();

      // initialize queues here
      virtual void initialize();
      virtual pkt_t next_packet();
  };
}

#endif