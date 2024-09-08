#include "mt-event.h"

namespace ns3 {

  template<typename ... T>
  MTEvent<T...>::MTEvent(EventType type, EventSubtype subtype, long time, flow_id<T...> flowId):
    type{type},
    subtype{std::move(subtype)},
    time{time},
    flowId{flowId}
    {
      if (type == EventType::INCOMING && (subtype != EventSubtype::APP_EVENT || subtype != EventSubtype::NET_EVENT)) {
        throw std::runtime_error("Invalid subtype for incoming event");
      }
    }

  template<typename ... T>
  MemEvent<T...>::MemEvent(long time, flow_id<T...> flowId, int32_t atomic_op, addr_t address, int length): 
    MTEvent{EventType::INCOMING, EventSubtype::MEM_EVENT, time, flowId},
    atomic_op{atomic_op},
    address{address},
    length{length}
    {}
  
  template<typename ... T>
  UrgentEvent<T...>::UrgentEvent(long time, flow_id<T...> flowId):
    MTEvent{EventType::INCOMING, EventSubtype::URGENT_EVENT, time, flowId}
  {}

  template<typename ... T>
  ProgEvent<T...>::ProgEvent(long time, flow_id<T...> flowId):
    MTEvent{EventType::INCOMING, EventSubtype::PROG_EVENT, time, flowId}
  {}

  template<typename ... T>
  TimerEvent<T...>::TimerEvent(long time, flow_id<T...> flowId):
    MTEvent{EventType::INCOMING, EventSubtype::TIMER_EVENT, time, flowId}
  {}

  template<typename ... T>
  NetEvent<T...>::NetEvent(EventType type, long time, flow_id<T...> flowId):
    MTEvent{type, EventSubtype::NET_EVENT, time, flowId}
  {}

  template<typename ... T>
  AppEvent<T...>::AppEvent(EventType type, long time, flow_id<T...> flowId):
    MTEvent{type, EventSubtype::APP_EVENT, time, flowId}
  {}

} // namespace ns3