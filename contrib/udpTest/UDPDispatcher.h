#include <vector>
#include "ns3/mt-event.h"
#include "ns3/mt-eventprocessor.h"
#include "ns3/mt-dispatcher.h"

class UDPDispatcher:public ns3::MTDispatcher{
	public:
	UDPDispatcher();
	~UDPDispatcher(){}
	std::vector<ns3::MTEventProcessor*> dispatch(ns3::MTEvent*);
};

