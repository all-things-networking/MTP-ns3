#ifndef UDP_EVENT_H
#define UDP_EVENT_H
#include "ns3/mt-event.h"
#include "ns3/ipv4-l3-protocol.h"
#include "ns3/node.h"
#include "ns3/packet.h"
#include "../helper/UDP-Datagram.h"

namespace ns3 {

// ==========================================================================================
// QUESTIONS/TODOS:
//   - How to incorporate the MTHeader class into these class definitions?
//   - How to incorporate Packet class into these class definitions? I'm seeing pointers to Packets
//     but not much of a rhyme or reason as to how they are used
// ==========================================================================================

// this will choose the event processor (from dispatcher)
enum EventType {
    SEND,
    RECV,
    ERROR
};

class MTHeader;
class MTEvent;

// This is the base event for UDP. It uses an EventType for further filtering in the dispatcher
class UDPEvent: public MTEvent{
    public:
    UDPEvent();
    UDPEvent(long time, int flow_id, EventType type = EventType::EMPTY);
    EventType type;
};

// OUTGOING_EVENT & APP_EVENT from MTP spec?
class SendEvent: public UDPEvent{
    public:
    Datagram * datagram;
    SendEvent(Datagram * datagram) : type(EventType::SEND), datagram(datagram) {};
};

// OUTGOING_EVENT & NET_EVENT from MTP spec?
class ReceiveEvent : public UDPEvent {
    public:
    Packet * packet;
    ReceiveEvent(Packet * packet) : type(EventType::RECV), packet{packet} {};
};

} // namespace ns3

#endif