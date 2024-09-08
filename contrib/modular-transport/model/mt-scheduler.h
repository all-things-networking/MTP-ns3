#ifndef MT_SCHEDULER_H
#define MT_SCHEDULER_H

#include <vector>
#include "../helper/mtp-types.h"
#include "mt-event.h"

namespace ns3 {
  class queue_set {
    public:
      // queue set
      queue_t<AppEvent *>    appQueue;
      queue_t<NetEvent *>    netQueue;
      queue_t<ProgEvent *>   progQueue;
      queue_t<UrgentEvent *> urgentQueue;
      queue_t<TimerEvent *>  timerQueue;
      queue_t<MemEvent *>    memQueue;
  };

  class MTScheduler {
    // need to initialize queues (with lower limit, upper limit and drop policy) when pushing
    flow_map<queue_set> flowMap;

    public:
      MTScheduler();
      ~MTScheduler();

      // used to store data from packets belonging to this flow while they are being processed
      flow_map<stream> transitoryMemory;

      virtual void initialize();
      
      virtual flow_id next_flow();
      virtual event_t next_event(flow_id id);
  };
}

#endif