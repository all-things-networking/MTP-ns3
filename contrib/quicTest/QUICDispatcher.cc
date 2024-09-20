#include"QUICDispatcher.h"
#include"QUICEvents.h"
#include"QUICEventProcs.h"

using namespace ns3;
using namespace std;

QUICDispatcher::QUICDispatcher(){}

std::vector<MTEventProcessor*> QUICDispatcher::dispatch(MTEvent* event){
	std::vector<MTEventProcessor*> ChosenProcessors;
	if (typeid(*event) == typeid(SEND))
	{
		ChosenProcessors.push_back( new selectDataProcessor() );
		ChosenProcessors.push_back( new sendProcessor() );
		//ChosenProcessors.push_back( new packetGenerationProcessor() );
	}
	if (typeid(*event) == typeid(ACK))
	{
		ChosenProcessors.push_back( new ackProcessor() );
		ChosenProcessors.push_back( new congestionProcessor() );
		ChosenProcessors.push_back( new updateRttProcessor() );
		ChosenProcessors.push_back( new lossDetectionProcessor() );
		ChosenProcessors.push_back( new congestionProcessor() );
		ChosenProcessors.push_back( new adjustWindowProcessor() );
		ChosenProcessors.push_back( new retransmitProcessor() );
		ChosenProcessors.push_back( new packetGenerationProcessor() );
	}
	if (typeid(*event) == typeid(DATA_ARRIVAL))
	{
		ChosenProcessors.push_back( new storeDataProcessor() );
		ChosenProcessors.push_back( new ackGenerationProcessor() );
		ChosenProcessors.push_back( new packetGenerationProcessor() );
	}
	if (typeid(*event) == typeid(ADD_DATA))
	{
		ChosenProcessors.push_back( new addStreamProcessor() );
	}
	if (typeid(*event) == typeid(TIMER))
	{
		ChosenProcessors.push_back( new lossDetectionProcessor() );
		ChosenProcessors.push_back( new congestionProcessor() );
		ChosenProcessors.push_back( new retransmitProcessor() );
		ChosenProcessors.push_back( new packetGenerationProcessor() );
	}
	return ChosenProcessors;
}
