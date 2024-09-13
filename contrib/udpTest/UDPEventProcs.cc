#include "UDPEventProcs.h"
#include "UDPHeaders.h"

SendProcessor::SendProcessor(){}
SendProcessor::~SendProcessor(){}
EventProcessorOutput* SendProcessor::process (MTEvent* e, EventProcessorOutput* epOut) {
	SEND_EVENT ev = *(SEND_EVENT*)e;
	myContext ctx = *(myContext*)epOut->ctx;
	interm_out out = *(interm_out*)e;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	epOutput->events = own_Process(ev, ctx, out);
	epOutput->ctx = new myContext(ctx);
	return epOutput;
}
bool SendProcessor::isValidEvent(MTEvent* e) {return true;};
vector<MTEvent*> SendProcessor::own_Process(SEND_EVENT& ev, myContext& ctx, interm_out& out)
{
	vector<MTEvent*> events;
	cout<<ctx.MTU<<endl;
	for ( int index = 0 ; index < ev.length ; index = index + ctx.MTU )
	{
		PKT_EVENT* pkt_ev= new PKT_EVENT(ev.flowId,10);
		pkt_ev->addr = ev.addr + index;
		int data_len = ctx.MTU;
		if( index + ctx.MTU > ev.length )
		{
			data_len = ev.length - index;
		}
		pkt_ev->length = data_len;
		UDPHeader udp;
		udp.src_port = ctx.src_port;
		udp.dst_port = ctx.dst_port;
		udp.length = sizeof(udp) + data_len;
		pkt_ev->udp = udp;
		events.emplace_back( pkt_ev );
	}
	ctx.sent_count = ctx.sent_count + 1;
	return events;
}
RecvProcessor::RecvProcessor(){}
RecvProcessor::~RecvProcessor(){}
EventProcessorOutput* RecvProcessor::process (MTEvent* e, EventProcessorOutput* epOut) {
	RECV_EVENT ev = *(RECV_EVENT*)e;
	myContext ctx = *(myContext*)epOut->ctx;
	interm_out out = *(interm_out*)e;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	epOutput->events = own_Process(ev, ctx, out);
	epOutput->ctx = new myContext(ctx);
	return epOutput;
}
bool RecvProcessor::IsValidEvent(MTEvent* e) {return true;};
vector<MTEvent*> RecvProcessor::own_Process(RECV_EVENT& ev, myContext& ctx, interm_out& out)
{
	vector<MTEvent*> events;
	FB_EVENT* fb_ev = new FB_EVENT(ev.flowId,10);
	fb_ev->transit_addr = ev.transit_addr;
	fb_ev->transit_length = ev.transit_length;
	events.emplace_back( fb_ev );
	ctx.recv_count = ctx.recv_count + 1;
	return events;
}
