#include "ns3/mt-eventprocessor.h"
#include "ns3/mt-event.h"
#include "ns3/mt-context.h"
#include "ns3/mtp-types.h"
#include "QUICContext.h"
#include "QUICEvents.h"
#include "QUICStructs.h"

using namespace ns3;
using namespace std;

class selectDataProcessor: public MTEventProcessor
{ 
 public:
	selectDataProcessor();
	~selectDataProcessor();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (SEND& ev , MyContext& ctx , interm_out& out);
};
class sendProcessor: public MTEventProcessor
{ 
 public:
	sendProcessor();
	~sendProcessor();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (SEND& ev , MyContext& ctx , interm_out& out);
};
class ackProcessor: public MTEventProcessor
{ 
 public:
	ackProcessor();
	~ackProcessor();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (ACK& ev , MyContext& ctx , interm_out& out);
};
class updateRttProcessor: public MTEventProcessor
{ 
 public:
	updateRttProcessor();
	~updateRttProcessor();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (ACK& ev , MyContext& ctx , interm_out& out);
};
class adjustWindowProcessor: public MTEventProcessor
{ 
 public:
	adjustWindowProcessor();
	~adjustWindowProcessor();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (ACK& ev , MyContext& ctx , interm_out& out);
};
class congestionProcessor: public MTEventProcessor
{ 
 public:
	congestionProcessor();
	~congestionProcessor();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (TIMER& ev , MyContext& ctx , interm_out& out);
};
class lossDetectionProcessor: public MTEventProcessor
{ 
 public:
	lossDetectionProcessor();
	~lossDetectionProcessor();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (ACK& ev , MyContext& ctx , interm_out& out);//ALSO TIMER
};
class retransmitProcessor: public MTEventProcessor
{ 
 public:
	retransmitProcessor();
	~retransmitProcessor();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (ACK& ev , MyContext& ctx , interm_out& out);//ALSO TIMER
};
class addStreamProcessor: public MTEventProcessor
{ 
 public:
	addStreamProcessor();
	~addStreamProcessor();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (ADD_DATA& ev , MyContext& ctx , interm_out& out);
};
class storeDataProcessor: public MTEventProcessor
{ 
 public:
	storeDataProcessor();
	~storeDataProcessor();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (DATA_ARRIVAL& ev , MyContext& ctx , interm_out& out);
};
class ackGenerationProcessor: public MTEventProcessor
{ 
 public:
	ackGenerationProcessor();
	~ackGenerationProcessor();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (DATA_ARRIVAL& ev , MyContext& ctx , interm_out& out);
};
class packetGenerationProcessor: public MTEventProcessor
{ 
 public:
	packetGenerationProcessor();
	~packetGenerationProcessor();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (SEND& ev , MyContext& ctx , interm_out& out);
};
