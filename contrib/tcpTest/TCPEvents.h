#ifndef EVENTS_H
#define EVENTS_H

#include"ns3/mt-event.h"


class SEND : public ns3::MTEvent
{
public: 
	int data_size;
	SEND(long time, int flow_id)
	:ns3::MTEvent(ns3::EventType::INCOMING, ns3::EventSubtype::APP_EVENT, time,flow_id)
	{}
	void getType()override{}
};
class ACK : public ns3::MTEvent
{
public: 
	int ack_seq;
	int rwnd_size;
	ACK(long time, int flow_id)
	:ns3::MTEvent(ns3::EventType::INCOMING, ns3::EventSubtype::NET_EVENT, time,flow_id)
	{}
	void getType()override{}
};
class DATA : public ns3::MTEvent
{
public: 
	int data_len;
	int seq_num;
	DATA(long time, int flow_id)
	:ns3::MTEvent(ns3::EventType::INCOMING, ns3::EventSubtype::NET_EVENT, time,flow_id)
	{}
	void getType()override{}
};
class MISS_ACK : public ns3::MTEvent
{
public: 
	int seq_num;
	MISS_ACK(long time, int flow_id)
	:ns3::MTEvent(ns3::EventType::NONE, ns3::EventSubtype::TIMER_EVENT, time,flow_id)
	{}
	void getType()override{}
};
class FB_EVENT : public ns3::MTEvent
{
public: 
	int seq_num;
	int data_len;
	FB_EVENT(long time, int flow_id)
	:ns3::MTEvent(ns3::EventType::OUTGOING, ns3::EventSubtype::APP_EVENT, time,flow_id)
	{}
	void getType()override{}
};
class PKT_EVENT : public ns3::MTEvent
{
public: 
	int seq_num;
	int data_len;
	bool ack_flag;
	int ack_num;
	int wnd_size;
	PKT_EVENT(long time, int flow_id)
	:ns3::MTEvent(ns3::EventType::OUTGOING, ns3::EventSubtype::NET_EVENT, time,flow_id)
	{}
	void getType()override{}
};

#endif