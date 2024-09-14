#include"UDPDispatcher.h"
#include"UDPEvents.h"
#include"UDPEventProcs.h"

using namespace std;
using namespace ns3;

UDPDispatcher::UDPDispatcher(){}
std::vector<MTEventProcessor*> UDPDispatcher::dispatch(MTEvent* event){
	std::vector<MTEventProcessor*> ChosenProcessors;
	if (typeid(*event) == typeid(RECV_EVENT))
	{
		ChosenProcessors.push_back( new RecvProcessor() );
	}
	if (typeid(*event) == typeid(SEND_EVENT))
	{
		//cout<<"it is a send event"<<endl;
		ChosenProcessors.push_back( new SendProcessor() );
	}
	return ChosenProcessors;
}
