#ifndef MT_SCHEDULER_H
#define MT_SCHEDULER_H

#include <vector>
#include <queue>
#include "../helper/mtp-types.h"
#include "mt-event.h"

namespace ns3 {
  class queue_set {
    public:
      // queue set
      std::queue<MTEvent *>    appQueue;
      std::queue<MTEvent *>    netQueue;
      std::queue<MTEvent *>   progQueue;
      std::queue<MTEvent *> urgentQueue;
      std::queue<MTEvent *>  timerQueue;
      std::queue<MTEvent *>    memQueue;
      int total_queues;

      // used when selecting for round-robin scheduling

      void enqueue_event(MTEvent * event);
      std::queue<MTEvent *> get_queue(int selector);
      void pop_queue(int selector);
      bool is_empty();

      queue_set();
  };

  class MTScheduler {
    // need to initialize queues (with lower limit, upper limit and drop policy) when pushing
    flow_map<queue_set> flowMap;

    // for choosing next event/flow
    flow_map<unsigned int> eventSelector;
    unsigned int flowSelector;

    public:
      MTScheduler();
      ~MTScheduler(){}

      // used to store data from packets belonging to this flow while they are being processed
      //flow_map<stream> transitoryMemory;

      void enqueue_event(flow_id id, MTEvent * event);
      void initialize();
      flow_id next_flow();
      MTEvent * next_event(flow_id id);

      bool is_empty();
 
      MTEvent * get_next_event();
  };
}

#endif