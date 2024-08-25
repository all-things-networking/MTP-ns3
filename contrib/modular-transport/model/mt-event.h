#ifndef MT_EVENT_H
#define MT_EVENT_H

#include <variant> // std::variant
#include <cstdint> // int32_t
#include "../helper/mtp-types.h" // addr_t
#include <stdexcept> // std::runtime_error
#include <string>

namespace ns3{

class MTHeader;

enum EventType {
    INCOMING, // event that transfers nothing to outer layers
    OUTGOING  // event that transfers packets or feedback to outer layers
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

// COMMENTS: ALTERNATIVE TYPE SYSTEM FOR SUBTYPES
// enum IncomingEventSubtype {
//     APP_EVENT,
//     NET_EVENT,
//     TIMER_EVENT,
//     PROG_EVENT,
//     URGENT_EVENT,
//     MEM_EVENT,
//     ERROR_EVENT
// };

// enum OutgoingEventSubtype {
//     APP_EVENT,
//     NET_EVENT
// };

class MTEvent {
public:
    EventType type;
    EventSubtype subtype;
    // union {
    //     IncomingEventSubtype incomingSubtype;
    //     OutgoingEventSubtype outgoingSubtype;
    // } subtype;
    long time;
    int flow_id;

    // used as key in event processor's eventMap
    std::string name;

    MTEvent(EventType type, 
            // std::variant<IncomingEventSubtype, OutgoingEventSubtype> && subtype, 
            EventSubtype subtype,
            long time, 
            int flow_id);
    virtual ~MTEvent();
};

class MemEvent : public MTEvent {
public:
    int32_t atomic_op;
    addr_t address;
    int length;

    MemEvent(// std::variant<IncomingEventSubtype, OutgoingEventSubtype> && subtype, 
             EventSubtype subtype,
             long time, 
             int flow_id, 
             int32_t atomic_op, 
             addr_t address, 
             int length);
    ~MemEvent() override;
};

// are these necessary?
int get_flow_id(event_t * event) {
    return event->flow_id;
}

void set_flow_id(event_t * event, int flow_id) {
    event->flow_id = flow_id;
}

} // namespace ns3
#endif
