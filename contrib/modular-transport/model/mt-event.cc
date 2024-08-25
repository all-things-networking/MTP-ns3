#include "mt-event.h"

namespace ns3 {

MTEvent::MTEvent(EventType type, EventSubtype subtype,  long time, int flow_id):
  type{type},
  subtype{std::move(subtype)},
  time{time},
  flow_id{flow_id}
  {
    if (type == EventType::INCOMING && (subtype != EventSubtype::APP_EVENT || subtype != EventSubtype::NET_EVENT)) {
      throw std::runtime_error("Invalid subtype for incoming event");
    }
  }

MemEvent::MemEvent(EventSubtype subtype, 
                   long time, 
                   int flow_id, 
                   int32_t atomic_op, 
                   addr_t address, 
                   int length): 
  MTEvent{EventType::INCOMING, subtype, time, flow_id},
  atomic_op{atomic_op},
  address{address},
  length{length}
  {}

} // namespace ns3