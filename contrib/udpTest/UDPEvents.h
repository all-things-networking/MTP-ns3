#ifndef EVENTS_H
#define EVENTS_H

#include"ns3/mt-event.h"
#include"UDPHeaders.h"

class SEND_EVENT : public ns3::MTEvent
{
public: 
	char addr;
	int length;
	SEND_EVENT(long time, int flow_id)
	:MTEvent(ns3::EventType::INCOMING, ns3::EventSubtype::APP_EVENT, time,flow_id)
	{}
	void getType()override{}
};
class RECV_EVENT : public ns3::MTEvent
{
public: 
	char transit_addr;
	int transit_length;
	RECV_EVENT(long time, int flow_id)
	:MTEvent(ns3::EventType::INCOMING, ns3::EventSubtype::NET_EVENT, time,flow_id)
	{}
	void getType()override{}
};
class PKT_EVENT : public ns3::MTEvent
{
public: 
	UDPHeader udp;
	char addr;
	int length;
	PKT_EVENT(long time, int flow_id)
	:MTEvent(ns3::EventType::OUTGOING, ns3::EventSubtype::NET_EVENT, time,flow_id)
	{}
	void getType()override{}
};
class FB_EVENT : public ns3::MTEvent
{
public: 
	char transit_addr;
	int transit_length;
	FB_EVENT(long time, int flow_id)
	:MTEvent(ns3::EventType::OUTGOING, ns3::EventSubtype::APP_EVENT, time,flow_id)
	{}
	void getType()override{}
};

#endif