#include "ns3/mt-txapp.h"

namespace ns3 {
  MTTXAppScheduler::MTTXAppScheduler() : flowMap(queue_set()) {
    eventSelector = flow_map<unsigned int>(0);
    flowSelector = 0;
  }

  MTTXAppScheduler::~MTTXAppScheduler() {}

  void MTTXAppScheduler::initialize() {}

  void MTTXAppScheduler::send_app_event(event_t * e) {}
}