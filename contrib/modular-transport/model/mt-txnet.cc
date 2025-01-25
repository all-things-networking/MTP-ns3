#include "ns3/mt-txnet.h"

namespace ns3 {
  MTTXNetScheduler::MTTXNetScheduler() {
    txQueues = flow_map<queue_t<event_t *>>();
    eventSelector = flow_map<unsigned int>(0);
    flowSelector = 0;
  }

  MTTXNetScheduler::~MTTXNetScheduler() {}

  void MTTXNetScheduler::initialize() {
    // initialize queues here
  }
}