#include "TCPEventProcs.h"

/*
Compiler Fixes: 
 - add header.cc and all its contents.
 - fix header.h
 - change the epOutput->events = own_Process(ev, ctx, int_out); to append instead.

*/

send_ep::send_ep(){}
send_ep::~send_ep(){}
EventProcessorOutput* send_ep::process (MTEvent* e, EventProcessorOutput* epOut) {
	SEND ev = *(SEND*)e;
	tcp_context ctx = *(tcp_context*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new tcp_context(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool send_ep::isValidEvent(MTEvent* e) {return true;}
vector<MTEvent*> send_ep::own_Process(SEND& ev, tcp_context& ctx, interm_out& int_out)
{
	vector<MTEvent*> events;
	int SMSS = 1440;
	ctx.data_end = ctx.data_end + ev.data_size;
	int data_rest = ctx.data_end - ctx.send_next;
	int effective_window = ctx.cwnd_size;
	if( effective_window > ctx.last_rwnd_size )
	{
		effective_window = ctx.last_rwnd_size;
	}
	int bytes_to_send = 0;
	if( ctx.send_una + effective_window < ctx.send_next )
	{
		return events;
	}
	else
	{
		int window_avail = ctx.send_una + effective_window - ctx.send_next;
		if( data_rest < window_avail )
		{
			bytes_to_send = data_rest;
		}
		else
		{
			bytes_to_send = window_avail;
		}
	}
	int num_loops = bytes_to_send / SMSS;
	if( bytes_to_send % SMSS != 0 )
	{
		num_loops = num_loops + 1;
	}
	for ( int i = 0 ; i < num_loops ; i = i + 1 )
	{
		int pkt_data_len;
		if( bytes_to_send <= SMSS )
		{
			pkt_data_len = bytes_to_send;
			bytes_to_send = 0;
		}
		else
		{
			pkt_data_len = SMSS;
			bytes_to_send = bytes_to_send - SMSS;
		}
		PKT_EVENT* pkt_ev = new PKT_EVENT(ev.flowId,10);
		pkt_ev->seq_num = ctx.send_next;
		pkt_ev->data_len = pkt_data_len;
		pkt_ev->ack_flag = 0;
		pkt_ev->ack_num = ctx.recv_next;
		pkt_ev->wnd_size = ctx.rwnd_size;
		events.emplace_back( pkt_ev );
		ctx.send_next = ctx.send_next + pkt_data_len;
	}
	MISS_ACK* time_ev = new MISS_ACK(ev.flowId,10);
	time_ev->seq_num = ctx.send_una;
	ctx.ack_timeout.set_duration( ctx.RTO );
	ctx.ack_timeout.start( time_ev );
	return events;
}
rto_ep::rto_ep(){}
rto_ep::~rto_ep(){}
EventProcessorOutput* rto_ep::process (MTEvent* e, EventProcessorOutput* epOut) {
	ACK ev = *(ACK*)e;
	tcp_context ctx = *(tcp_context*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new tcp_context(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool rto_ep::isValidEvent(MTEvent* e) {return true;}
vector<MTEvent*> rto_ep::own_Process(ACK& ev, tcp_context& ctx, interm_out& int_out)
{
	int_out.skip_ack_eps = 0;
	if( ev.ack_seq < ctx.send_una || ctx.send_next < ev.ack_seq )
	{
		int_out.skip_ack_eps = 1;
		return vector<MTEvent*>();
	}
	int granularity_g = 1;
	if( ctx.first_rto )
	{
		ctx.SRTT = 100;
		ctx.RTTVAR = 100 / 2;
		if( granularity_g >= 4 * ctx.RTTVAR )
		{
			ctx.RTO = ctx.SRTT + granularity_g;
		}
		else
		{
			ctx.RTO = ctx.SRTT + 4 * ctx.RTTVAR;
		}
		ctx.first_rto = false;
	}
	else
	{
		ctx.RTTVAR = ( 1 - 1 / 4 ) * ctx.RTTVAR + 1 / 4 * abs( ctx.SRTT - 100 );
		ctx.SRTT = ( 1 - 1 / 8 ) * ctx.SRTT + 1 / 8 * 100;
		if( granularity_g >= 4 * ctx.RTTVAR )
		{
			ctx.RTO = ctx.SRTT + granularity_g;
		}
		else
		{
			ctx.RTO = ctx.SRTT + 4 * ctx.RTTVAR;
		}
	}
	return vector<MTEvent*>();
}
fast_retr_rec_ep::fast_retr_rec_ep(){}
fast_retr_rec_ep::~fast_retr_rec_ep(){}
EventProcessorOutput* fast_retr_rec_ep::process (MTEvent* e, EventProcessorOutput* epOut) {
	ACK ev = *(ACK*)e;
	tcp_context ctx = *(tcp_context*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new tcp_context(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool fast_retr_rec_ep::isValidEvent(MTEvent* e) {return true;}
vector<MTEvent*> fast_retr_rec_ep::own_Process(ACK& ev, tcp_context& ctx, interm_out& int_out)
{
	if( int_out.skip_ack_eps )
	{
		return vector<MTEvent*>();
	}
	int SMSS = 1440;
	int_out.change_cwnd = 1;
	if( ev.ack_seq == ctx.last_ack )
	{
		ctx.duplicate_acks = ctx.duplicate_acks + 1;
		int_out.change_cwnd = 0;
		if( ctx.duplicate_acks == 1 )
		{
			ctx.flightsize_dupl = ctx.send_next - ctx.send_una;
		}
		if( ctx.duplicate_acks == 3 )
		{
			int opt1 = ctx.flightsize_dupl / 2;
			int opt2 = 2 * SMSS;
			if( opt1 >= opt2 )
			{
				ctx.ssthresh = opt1;
			}
			else
			{
				ctx.ssthresh = opt2;
			}
			ctx.cwnd_size = ctx.ssthresh + 3 * SMSS;
		}
		if( ctx.duplicate_acks != 3 )
		{
			ctx.cwnd_size = ctx.cwnd_size * SMSS;
		}
	}
	else
	{
		if( ctx.duplicate_acks > 0 )
		{
			ctx.cwnd_size = ctx.ssthresh;
		}
		ctx.duplicate_acks = 0;
		ctx.last_ack = ev.ack_seq;
	}
	return vector<MTEvent*>();
}
slows_congc_ep::slows_congc_ep(){}
slows_congc_ep::~slows_congc_ep(){}
EventProcessorOutput* slows_congc_ep::process (MTEvent* e, EventProcessorOutput* epOut) {
	ACK ev = *(ACK*)e;
	tcp_context ctx = *(tcp_context*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new tcp_context(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool slows_congc_ep::isValidEvent(MTEvent* e) {return true;}
vector<MTEvent*> slows_congc_ep::own_Process(ACK& ev, tcp_context& ctx, interm_out& int_out)
{
	if( int_out.skip_ack_eps )
	{
		return vector<MTEvent*>();
	}
	int SMSS = 1440;
	if( int_out.change_cwnd )
	{
		if( ctx.cwnd_size < ctx.ssthresh )
		{
			ctx.cwnd_size = ctx.cwnd_size + SMSS;
		}
		else
		{
			int add_cwnd = SMSS * SMSS / ctx.cwnd_size;
			if( add_cwnd == 0 )
			{
				add_cwnd = 1;
			}
			ctx.cwnd_size = ctx.cwnd_size + add_cwnd;
		}
	}
	return vector<MTEvent*>();
}
ack_net_ep::ack_net_ep(){}
ack_net_ep::~ack_net_ep(){}
EventProcessorOutput* ack_net_ep::process (MTEvent* e, EventProcessorOutput* epOut) {
	ACK ev = *(ACK*)e;
	tcp_context ctx = *(tcp_context*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new tcp_context(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool ack_net_ep::isValidEvent(MTEvent* e) {return true;}
vector<MTEvent*> ack_net_ep::own_Process(ACK& ev, tcp_context& ctx, interm_out& int_out)
{
	vector<MTEvent*> events;
	int SMSS = 1440;
	if( int_out.skip_ack_eps )
	{
		return events;
	}
	ctx.last_rwnd_size = ev.rwnd_size;
	ctx.send_una = ev.ack_seq;
	int data_rest = ctx.data_end - ctx.send_next;
	if( data_rest == 0 && ev.ack_seq == ctx.send_next )
	{
		ctx.ack_timeout.stop(  );
		return events;
	}
	int effective_window = ctx.cwnd_size;
	if( effective_window > ctx.last_rwnd_size )
	{
		effective_window = ctx.last_rwnd_size;
	}
	int bytes_to_send = 0;
	if( ctx.duplicate_acks == 3 )
	{
		bytes_to_send = SMSS;
		if( bytes_to_send > effective_window )
		{
			bytes_to_send = effective_window;
		}
		PKT_EVENT* pkt_ev = new PKT_EVENT (ev.flowId,10);
		pkt_ev->seq_num = ctx.send_una;
		pkt_ev->data_len = bytes_to_send;
		pkt_ev->ack_flag = 0;
		pkt_ev->ack_num = ctx.recv_next;
		pkt_ev->wnd_size = ctx.rwnd_size;
		events.emplace_back( pkt_ev );
		return events;
	}
	int window_avail = ctx.send_una + effective_window - ctx.send_next;
	if( window_avail < 0 )
	{
		bytes_to_send = 0;
	}
	else
	{
		if( data_rest < window_avail )
		{
			bytes_to_send = data_rest;
		}
		else
		{
			bytes_to_send = window_avail;
		}
	}
	int num_loops = bytes_to_send / SMSS;
	if( bytes_to_send % SMSS != 0 )
	{
		num_loops = num_loops + 1;
	}
	for ( int i = 0 ; i < num_loops ; i = i + 1 )
	{
		int pkt_data_len;
		if( bytes_to_send <= SMSS )
		{
			pkt_data_len = bytes_to_send;
			bytes_to_send = 0;
		}
		else
		{
			pkt_data_len = SMSS;
			bytes_to_send = bytes_to_send - SMSS;
		}
		PKT_EVENT* pkt_ev = new PKT_EVENT(ev.flowId,10);
		pkt_ev->seq_num = ctx.send_next;
		pkt_ev->data_len = pkt_data_len;
		pkt_ev->ack_flag = 0;
		pkt_ev->ack_num = ctx.recv_next;
		pkt_ev->wnd_size = ctx.rwnd_size;
		events.emplace_back( pkt_ev );
		ctx.send_next = ctx.send_next + pkt_data_len;
	}
	ctx.ack_timeout.stop(  );
	MISS_ACK* time_ev = new MISS_ACK(ev.flowId,10);
	time_ev->seq_num = ctx.send_una;
	ctx.ack_timeout.set_duration( ctx.RTO);
	ctx.ack_timeout.start( time_ev );
	return events;
}
data_net_ep::data_net_ep(){}
data_net_ep::~data_net_ep(){}
EventProcessorOutput* data_net_ep::process (MTEvent* e, EventProcessorOutput* epOut) {
	DATA ev = *(DATA*)e;
	tcp_context ctx = *(tcp_context*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new tcp_context(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool data_net_ep::isValidEvent(MTEvent* e) {return true;}
vector<MTEvent*> data_net_ep::own_Process(DATA& ev, tcp_context& ctx, interm_out& int_out)
{
	if( ( ctx.rwnd_size == 0 && ev.data_len > 0 ) || ( ev.seq_num > ctx.recv_next + ctx.rwnd_size ) || ( ev.seq_num + ev.data_len - 1 < ctx.recv_next ) )
	{
		return vector<MTEvent*>();
	}
	int MAX_NUM_CTX_PKT_INFO = 500;
	if( ev.seq_num <= ctx.recv_next && ev.seq_num + ev.data_len - 1 >= ctx.recv_next )
	{
		if( ev.seq_num + ev.data_len < ctx.recv_next + ctx.rwnd_size )
		{
			ctx.recv_next = ev.seq_num + ev.data_len;
		}
		else
		{
			ctx.recv_next = ctx.recv_next + ctx.rwnd_size;
		}
		if( ctx.data_recv_array_head != ctx.data_recv_array_tail )
		{
			int curr_index;
			if( ctx.data_recv_array_tail == 0 )
			{
				curr_index = MAX_NUM_CTX_PKT_INFO - 1;
			}
			else
			{
				curr_index = ctx.data_recv_array_tail - 1;
			}
			for ( int i = 0 ; i < MAX_NUM_CTX_PKT_INFO ; i = i + 1 )
			{
				if( ctx.data_recv_info_array[ curr_index ].seq_num <= ctx.recv_next )
				{
					int elem_recv_next = ctx.data_recv_info_array[ curr_index ].seq_num + ctx.data_recv_info_array[ curr_index ].data_len;
					if( elem_recv_next > ctx.recv_next )
					{
						ctx.recv_next = elem_recv_next;
					}
					if( ctx.data_recv_array_tail == 0 )
					{
						ctx.data_recv_array_tail = MAX_NUM_CTX_PKT_INFO - 1;
					}
					else
					{
						ctx.data_recv_array_tail = ctx.data_recv_array_tail - 1;
					}
				}
				else
				{
					break;
				}
				if( ctx.data_recv_array_head == ctx.data_recv_array_tail )
				{
					break;
				}
				if( curr_index == 0 )
				{
					curr_index = MAX_NUM_CTX_PKT_INFO - 1;
				}
				else
				{
					curr_index = curr_index - 1;
				}
			}
		}
	}
	else
	{
		if( ( ctx.data_recv_array_tail == MAX_NUM_CTX_PKT_INFO - 1 && ctx.data_recv_array_head == 0 ) || ( ctx.data_recv_array_head == ctx.data_recv_array_tail + 1 ) )
		{
			return vector<MTEvent*>();
		}
		int curr_index = ctx.data_recv_array_head;
		sent_pkt_info new_elem;
		new_elem.seq_num = ev.seq_num;
		new_elem.data_len = ev.data_len;
		bool found = false;
		for ( int i = 0 ; i < MAX_NUM_CTX_PKT_INFO ; i = i + 1 )
		{
			if( found )
			{
				sent_pkt_info temp = ctx.data_recv_info_array[ curr_index ];
				ctx.data_recv_info_array[ curr_index ] = new_elem;
				new_elem = temp;
			}
			if( ctx.data_recv_info_array[ curr_index ].seq_num == new_elem.seq_num && ctx.data_recv_info_array[ curr_index ].data_len == new_elem.data_len && found == false )
			{
				break;
			}
			if( ctx.data_recv_info_array[ curr_index ].seq_num <= new_elem.seq_num && found == false )
			{
				sent_pkt_info temp = ctx.data_recv_info_array[ curr_index ];
				ctx.data_recv_info_array[ curr_index ] = new_elem;
				new_elem = temp;
				found = true;
				ctx.data_recv_array_tail = ( ctx.data_recv_array_tail + 1 ) % MAX_NUM_CTX_PKT_INFO;
			}
			if( curr_index == ctx.data_recv_array_tail )
			{
				break;
			}
			curr_index = ( curr_index + 1 ) % MAX_NUM_CTX_PKT_INFO;
		}
	}
	return vector<MTEvent*>();
}
send_ack::send_ack(){}
send_ack::~send_ack(){}
EventProcessorOutput* send_ack::process (MTEvent* e, EventProcessorOutput* epOut) {
	DATA ev = *(DATA*)e;
	tcp_context ctx = *(tcp_context*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new tcp_context(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool send_ack::isValidEvent(MTEvent* e) {return true;}
vector<MTEvent*> send_ack::own_Process(DATA& ev, tcp_context& ctx, interm_out& int_out)
{
	vector<MTEvent*> events;
	int SMSS = 1440;
	int data_rest = ctx.data_end - ctx.send_next;
	int effective_window = ctx.cwnd_size;
	if( effective_window > ctx.last_rwnd_size )
	{
		effective_window = ctx.last_rwnd_size;
	}
	int window_avail = ctx.send_una + effective_window - ctx.send_next;
	int bytes_to_send = 0;
	if( window_avail < 0 )
	{
		bytes_to_send = 0;
	}
	else
	{
		if( data_rest < window_avail )
		{
			bytes_to_send = data_rest;
		}
		else
		{
			bytes_to_send = window_avail;
		}
		if( bytes_to_send > SMSS )
		{
			bytes_to_send = SMSS;
		}
	}
	PKT_EVENT* pkt_ev = new PKT_EVENT(ev.flowId,10);
	pkt_ev->seq_num = ctx.send_next;
	pkt_ev->data_len = bytes_to_send;
	pkt_ev->ack_flag = 1;
	pkt_ev->ack_num = ctx.recv_next;
	pkt_ev->wnd_size = ctx.rwnd_size;
	events.emplace_back( pkt_ev );
	return events;
}
app_feedback_ep::app_feedback_ep(){}
app_feedback_ep::~app_feedback_ep(){}
EventProcessorOutput* app_feedback_ep::process (MTEvent* e, EventProcessorOutput* epOut) {
	DATA ev = *(DATA*)e;
	tcp_context ctx = *(tcp_context*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new tcp_context(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool app_feedback_ep::isValidEvent(MTEvent* e) {return true;}
vector<MTEvent*> app_feedback_ep::own_Process(DATA& ev, tcp_context& ctx, interm_out& int_out)
{
	vector<MTEvent*> events;
	FB_EVENT* fb_ev = new FB_EVENT(ev.flowId,10);
	fb_ev->seq_num = ev.seq_num;
	fb_ev->data_len = ev.data_len;
	events.emplace_back( fb_ev );
	return events;
}
ack_timeout_ep::ack_timeout_ep(){}
ack_timeout_ep::~ack_timeout_ep(){}
EventProcessorOutput* ack_timeout_ep::process (MTEvent* e, EventProcessorOutput* epOut) {
	MISS_ACK ev = *(MISS_ACK*)e;
	tcp_context ctx = *(tcp_context*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new tcp_context(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool ack_timeout_ep::isValidEvent(MTEvent* e) {return true;}
vector<MTEvent*> ack_timeout_ep::own_Process(MISS_ACK& ev, tcp_context& ctx, interm_out& int_out)
{
	vector<MTEvent*> events;
	int SMSS = 1440;
	ctx.cwnd_size = SMSS * 3;
	int opt1 = ( ctx.send_next - ctx.send_una ) / 2;
	int opt2 = 2 * SMSS;
	if( opt1 > opt2 )
	{
		ctx.ssthresh = opt1;
	}
	else
	{
		ctx.ssthresh = opt2;
	}
	int data_rest = ctx.data_end - ctx.send_una;
	int effective_window = ctx.cwnd_size;
	if( effective_window > ctx.last_rwnd_size )
	{
		effective_window = ctx.last_rwnd_size;
	}
	int bytes_to_send = 0;
	if( ctx.send_una + effective_window < ctx.send_next )
	{
		if( data_rest < effective_window )
		{
			bytes_to_send = data_rest;
		}
		else
		{
			bytes_to_send = effective_window;
		}
	}
	else
	{
		int window_avail = ctx.send_una + effective_window - ctx.send_next;
		if( data_rest < window_avail )
		{
			bytes_to_send = data_rest;
		}
		else
		{
			bytes_to_send = window_avail;
		}
	}
	if( bytes_to_send > SMSS )
	{
		bytes_to_send = SMSS;
	}
	PKT_EVENT* pkt_ev = new PKT_EVENT(ev.flowId,10);
	pkt_ev->seq_num = ctx.send_una;
	pkt_ev->data_len = bytes_to_send;
	pkt_ev->ack_flag = 0;
	pkt_ev->ack_num = ctx.recv_next;
	pkt_ev->wnd_size = ctx.rwnd_size;
	events.emplace_back( pkt_ev );
	ctx.ack_timeout.restart( ctx.RTO );
	return events;
}
