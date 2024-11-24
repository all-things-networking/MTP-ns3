#include "ns3/mt-dispatcher.h"

namespace ns3 {
  std::unordered_map<std::string, std::vector<MTEventProcessor*>> MTDispatcher::getEventMap() {
    return eventMap;
  }

  std::vector<MTEventProcessor*> MTDispatcher::dispatch(MTEvent* e) {
    std::string key = e->typeString;
    return eventMap[key];
  }
} // namespace ns3