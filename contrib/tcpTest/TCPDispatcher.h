#include "ns3/mt-event.h"
#include "ns3/mt-eventprocessor.h"
#include "ns3/mt-dispatcher.h"

#include <vector>

using namespace ns3;
using namespace std;

class TCPDispatcher: public MTDispatcher
{
	public:
		TCPDispatcher();
		~TCPDispatcher(){}
		std::vector<MTEventProcessor*> dispatch(MTEvent*);
};
