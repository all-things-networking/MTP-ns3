#ifndef MT_EVENT_H
#define MT_EVENT_H

#include <variant> // std::variant
#include <cstdint> // int32_t
#include <stdexcept> // std::runtime_error
#include <string>
#include "ns3/mtp-types.h"
// #include "ns3/mt-flow-id.h"
// #include "ns3/mt-addr.h"

namespace ns3 {

// TODO: Do we need to implement a TX_EVENT type (from page 27 of the Overleaf doc) ?

class MTHeader;

enum EventType {
    INCOMING, // event that transfers nothing to outer layers
    OUTGOING,  // event that transfers packets or feedback to outer layers
    NONE
};

enum EventSubtype {
    APP_EVENT,
    NET_EVENT,
    TIMER_EVENT,
    PROG_EVENT,
    URGENT_EVENT,
    MEM_EVENT,
    ERROR_EVENT
};

class MTEvent {
    public:
        EventType type;
        EventSubtype subtype;
        long time;
        flow_id flowId;
        const std::string typeString;
        uint8_t * data;
        virtual EventType getType() { return type; }

        // used as key in event processor's eventMap
        std::string name;

        MTEvent(EventType type, 
                EventSubtype subtype,
                long time, 
                flow_id flowId,
                std::string typeString = "");
        virtual ~MTEvent();
};

// event_t
typedef MTEvent event_t;
class MemEvent : public MTEvent {
    public:
        int32_t atomic_op;
        addr_t address;
        int length;

        MemEvent(long time, 
                flow_id flowId, 
                int32_t atomic_op, 
                addr_t address, 
                int length);
        virtual ~MemEvent() override;
};

class UrgentEvent : public MTEvent {
    public:
        UrgentEvent(long time, 
                    flow_id flowId);
        virtual ~UrgentEvent() override;
};

class ProgEvent : public MTEvent {
    public:
        ProgEvent(long time, 
                flow_id flowId);
        virtual ~ProgEvent() override;
};

class TimerEvent : public MTEvent {
    public:
        TimerEvent(long time, flow_id flowId);
        virtual ~TimerEvent() override;
};

class NetEvent : public MTEvent {
    public:
        NetEvent(EventType type,
                long time, 
                flow_id flowId);
        virtual ~NetEvent() override;
};

class AppEvent : public MTEvent {
    public:
        AppEvent(EventType type,
                long time, 
                flow_id flowId);
        virtual ~AppEvent() override;
};

// are these necessary?
inline flow_id get_flow_id(event_t * event) {
    return event->flowId;
}

} // namespace ns3
#endif
