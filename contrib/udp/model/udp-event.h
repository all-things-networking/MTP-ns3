#ifndef UDP_EVENTS_H
#define UDP_EVENTS_H

#include "ns3/mt-event.h"
#include "ns3/udp-header.h"

namespace ns3 {
  // receive data from app 
  //  (note: event processors should not create incoming events therefore an event processor
  //   should never generate a SendEvent)
  class SendEvent : public MTEvent {
    public:
      int length;
      uint8_t * data;
      SendEvent(long time, int flow_id) : MTEvent(EventType::INCOMING, EventSubtype::APP_EVENT, time, flow_id, "SEND") {}
  };

  // receive packets from network layer
  //  (note: event processors should not create incoming events therefore an event processor
  //   should never generate a RecvEvent)
  class RecvEvent : public MTEvent {
    public:
      Ipv4Address transit_addr;
      int transit_length;
      RecvEvent(long time, int flow_id) : MTEvent(EventType::INCOMING, EventSubtype::NET_EVENT, time, flow_id, "RECV") {}
  };

  // transmit packets to network layer
  class PktEvent : public MTEvent {
    public:
      UDPHeader header;
      uint8_t * payload;
      Ipv4Address dest_addr;
      Ipv4Address src_addr;
      int length;
      PktEvent(long time, flow_id flowId, UDPHeader header, uint8_t * payload, Ipv4Address src_addr, Ipv4Address dest_addr) 
        : MTEvent(EventType::OUTGOING, EventSubtype::NET_EVENT, time, flowId, "PKT"),
          header{header}, payload{payload}, dest_addr{dest_addr}, src_addr{src_addr} {}
  };

  // write data back to app - comes after RecvEvent
  class FbEvent : public MTEvent {
    public:
      Ipv4Address transit_addr;
      int transit_length;
      FbEvent(long time, int flow_id) : MTEvent(EventType::OUTGOING, EventSubtype::APP_EVENT, time, flow_id, "FB") {}
  };
}

#endif
