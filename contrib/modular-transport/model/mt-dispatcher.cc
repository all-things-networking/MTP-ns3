#include "mt-dispatcher.h"

namespace ns3 {

  std::unordered_map<std::string, std::vector<MTEventProcessor*>> MTDispatcher::getEventMap() {
    return eventMap;
  }

} // namespace ns3