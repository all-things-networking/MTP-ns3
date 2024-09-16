#include"TCPDispatcher.h"
#include"TCPEvents.h"
#include"TCPEventProcs.h"

TCPDispatcher::TCPDispatcher(){}

std::vector<MTEventProcessor*> TCPDispatcher::dispatch(MTEvent* event){
	std::vector<MTEventProcessor*> ChosenProcessors;
	if (typeid(*event) == typeid(ACK))
	{
		ChosenProcessors.push_back( new rto_ep() );
		ChosenProcessors.push_back( new fast_retr_rec_ep() );
		ChosenProcessors.push_back( new slows_congc_ep() );
		ChosenProcessors.push_back( new ack_net_ep() );
	}
	if (typeid(*event) == typeid(MISS_ACK))
	{
		ChosenProcessors.push_back( new ack_timeout_ep() );
	}
	if (typeid(*event) == typeid(DATA))
	{
		ChosenProcessors.push_back( new data_net_ep() );
		ChosenProcessors.push_back( new send_ack() );
		ChosenProcessors.push_back( new app_feedback_ep() );
	}
	if (typeid(*event) == typeid(SEND))
	{
		ChosenProcessors.push_back( new send_ep() );
	}
	return ChosenProcessors;
}
