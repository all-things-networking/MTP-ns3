#include "ns3/mt-eventprocessor.h"
#include "ns3/mt-event.h"
#include "ns3/mt-context.h"
#include "ns3/mtp-types.h"
#include "TCPContext.h"
#include "TCPEvents.h"

using namespace ns3;
using namespace std;

class send_ep: public MTEventProcessor
{ 
 public:
	send_ep();
	~send_ep();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (SEND& ev , tcp_context& ctx , interm_out& int_out);
};
class rto_ep: public MTEventProcessor
{ 
 public:
	rto_ep();
	~rto_ep();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (ACK& ev , tcp_context& ctx , interm_out& int_out);
};
class fast_retr_rec_ep: public MTEventProcessor
{ 
 public:
	fast_retr_rec_ep();
	~fast_retr_rec_ep();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (ACK& ev , tcp_context& ctx , interm_out& int_out);
};
class slows_congc_ep: public MTEventProcessor
{ 
 public:
	slows_congc_ep();
	~slows_congc_ep();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (ACK& ev , tcp_context& ctx , interm_out& int_out);
};
class ack_net_ep: public MTEventProcessor
{ 
 public:
	ack_net_ep();
	~ack_net_ep();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (ACK& ev , tcp_context& ctx , interm_out& int_out);
};
class data_net_ep: public MTEventProcessor
{ 
 public:
	data_net_ep();
	~data_net_ep();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (DATA& ev , tcp_context& ctx , interm_out& int_out);
};
class send_ack: public MTEventProcessor
{ 
 public:
	send_ack();
	~send_ack();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (DATA& ev , tcp_context& ctx , interm_out& int_out);
};
class app_feedback_ep: public MTEventProcessor
{ 
 public:
	app_feedback_ep();
	~app_feedback_ep();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (DATA& ev , tcp_context& ctx , interm_out& int_out);
};
class ack_timeout_ep: public MTEventProcessor
{ 
 public:
	ack_timeout_ep();
	~ack_timeout_ep();
	EventProcessorOutput* process (MTEvent* e, EventProcessorOutput* epOut);
	bool isValidEvent(MTEvent* e);
	vector<MTEvent*> own_Process (MISS_ACK& ev , tcp_context& ctx , interm_out& int_out);
};
