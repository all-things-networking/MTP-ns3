#include "mt-scheduler.h"

namespace ns3 {
  queue_set::queue_set() {
    queues = {&appQueue, &netQueue, &progQueue, &urgentQueue, &timerQueue, &memQueue};
  }

  MTScheduler::MTScheduler() {
    flowMap = flow_map<queue_set>();
    eventSelector = flow_map<unsigned int>(0);
    flowSelector = 0;
  }

  void MTScheduler::enqueue_event(flow_id id, event_t * event) {
    flowMap[id].enqueue_event(event);
  }

  flow_id MTScheduler::next_flow() {
    auto it = flowMap.begin();
    for (int i = 0; i < flowSelector; i++) {
      it = it->next();
    }
    return it->first;
  }

  event_t * MTScheduler::next_event(flow_id id) {
    queue_set & flowQueueSet = flowMap[id];
    unsigned int selector = eventSelector[id]++ % flowQueueSet.queues.size();
    return flowQueueSet.queues[selector]->pop();
  }

  event_t * get_next_event(MTScheduler * scheduler) {
    flow_id id = scheduler->next_flow();
    event_t * event = scheduler->next_event(id);
    return event;
  }

  void queue_set::enqueue_event(event_t * event) {
    switch (event->type) {
      case APP_EVENT:
        appQueue.push(event);
        break;
      case NET_EVENT:
        netQueue.push(event);
        break;
      case PROG_EVENT:
        progQueue.push(event);
        break;
      case URGENT_EVENT:
        urgentQueue.push(event);
        break;
      case TIMER_EVENT:
        timerQueue.push(event);
        break;
      case MEM_EVENT:
        memQueue.push(event);
        break;
    }
  }
}

