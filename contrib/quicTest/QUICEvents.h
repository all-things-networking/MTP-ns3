#ifndef EVENTS_H
#define EVENTS_H

#include"ns3/mt-event.h"
#include<vector>
#include"QUICStructs.h"
#include"QUICHeaders.h"


class SEND : public ns3::MTEvent
{
public: 
	int flow_id;
	SEND(long time, int flow_id)
	:ns3::MTEvent(ns3::EventType::NONE, ns3::EventSubtype::PROG_EVENT, time,flow_id)
	{}
};
class TIMER : public ns3::MTEvent
{
public: 
	TIMER(long time, int flow_id)
	:ns3::MTEvent(ns3::EventType::NONE, ns3::EventSubtype::TIMER_EVENT, time,flow_id)
	{}
};
class ACK : public ns3::MTEvent
{
public: 
	int flow_id;
	std::vector<int> pkt_nums;
	int pkt_nums_counter;
	int largest;
	int largest_acked;
	int ECT0_Count;
	int ECT1_Count;
	int ECN_CE_Count;
	ACK(long time, int flow_id)
	:ns3::MTEvent(ns3::EventType::INCOMING, ns3::EventSubtype::NET_EVENT, time,flow_id)
	{}
};
class ADD_DATA : public ns3::MTEvent
{
public: 
	bool server_side;
	bool direction;
	int data_length;
	char address;
	ADD_DATA(long time, int flow_id)
	:ns3::MTEvent(ns3::EventType::INCOMING, ns3::EventSubtype::APP_EVENT, time,flow_id)
	{}
};
class DATA_ARRIVAL : public ns3::MTEvent
{
public: 
	int packet_id;
	std::vector<Frame> frames;
	DATA_ARRIVAL(long time, int flow_id)
	:ns3::MTEvent(ns3::EventType::INCOMING, ns3::EventSubtype::NET_EVENT, time,flow_id)
	{}
};
class PKT_EVENT : public ns3::MTEvent
{
public: 
	int hdr_combination;
	QuicHeader qheader;
	bool read_from_mem;
	std::vector<Frame> frame;
	int frame_size = 0;
	char address;
	int length;
	PKT_EVENT(long time, int flow_id)
	:ns3::MTEvent(ns3::EventType::OUTGOING, ns3::EventSubtype::NET_EVENT, time,flow_id)
	{}
};

#endif