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

class MTHeader;

enum EventType {
    INCOMING,  // event that transfers nothing to app or net layers (i.e. because it originated in one of them)
    OUTGOING,  // event that transfers packets or feedback to app or net layers
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
        bool deleted;
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

// hold feedback from memory reads/writes to be used in the transport layer
//  e.g. to generate ACKs
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

// needs to be processed ASAP
class UrgentEvent : public MTEvent {
    public:
        UrgentEvent(long time, 
                    flow_id flowId);
        virtual ~UrgentEvent() override;
};

// events created during the execution of the transport-layer program
//  itself (as opposed to other events that represent external things coming in)
class ProgEvent : public MTEvent {
    public:
        ProgEvent(long time, 
                  flow_id flowId);
        virtual ~ProgEvent() override;
};

// represents events that can be executed only after a timer is triggered
class TimerEvent : public MTEvent {
    public:
        TimerEvent(long time, flow_id flowId);
        virtual ~TimerEvent() override;
};

// represents packets arriving from/outgoing to the network layer
class NetEvent : public MTEvent {
    public:
        NetEvent(EventType type,
                long time, 
                flow_id flowId);
        virtual ~NetEvent() override;
};

// represents requests arriving from/outgoing to the app layer
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
