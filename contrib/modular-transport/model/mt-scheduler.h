#ifndef MT_SCHEDULER_H
#define MT_SCHEDULER_H

#include <vector>
#include "../helper/mtp-types.h"
#include "mt-event.h"

namespace ns3 {
  class queue_set {
    public:
      // queue set
      queue_t<event_t *>    appQueue;
      queue_t<event_t *>    netQueue;
      queue_t<event_t *>   progQueue;
      queue_t<event_t *> urgentQueue;
      queue_t<event_t *>  timerQueue;
      queue_t<event_t *>    memQueue;

      // used when selecting for round-robin scheduling
      std::vector<queue_t<event_t *> *> queues;

      void enqueue_event(event_t * event);

      queue_set();
      ~queue_set();
  };

  class MTScheduler {
    // need to initialize queues (with lower limit, upper limit and drop policy) when pushing
    flow_map<queue_set> flowMap;

    // for choosing next event/flow
    flow_map<unsigned int> eventSelector;
    unsigned int flowSelector;

    public:
      MTScheduler();
      ~MTScheduler();

      // used to store data from packets belonging to this flow while they are being processed
      flow_map<stream> transitoryMemory;

      void enqueue_event(flow_id id, event_t * event);
      virtual void initialize();
      flow_id next_flow();
      event_t * next_event(flow_id id);
 
      friend event_t * get_next_event(MTScheduler * scheduler);
      friend void enqueue_event(flow_map<queue_set> flowMap, flow_id id, event_t * event);
  };
}

#endif