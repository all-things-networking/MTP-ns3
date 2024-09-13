#ifndef UDPEVENTPROCS_H
#define UDPEVENTPROCS_H

#include "ns3/mt-eventprocessor.h"
#include "ns3/mt-event.h"
#include "ns3/mt-context.h"
#include "ns3/mtp-types.h"
#include "UDPContext.h"
#include "UDPEvents.h"



class SendProcessor: public ns3::MTEventProcessor
{ 
 public:
	SendProcessor();
	~SendProcessor();
	EventProcessorOutput* process (ns3::MTEvent* e, EventProcessorOutput* epOut)override;
	bool isValidEvent(ns3::MTEvent* e)override;
	vector<MTEvent*> own_Process (SEND_EVENT& ev , myContext& ctx , interm_out& out);
};
// class RecvProcessor: public MTEventProcessor
// { 
//  public:
// 	RecvProcessor();
// 	~RecvProcessor();
// 	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
// 	bool IsValidEvent(MTEvent* e);
// 	EventProcessorOutput* own_Process (RECV_EVENT ev , myContext ctx , interm_out out);
// };

#endif