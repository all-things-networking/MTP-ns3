#include "QUICEventProcs.h"
#include "ns3/simulator.h"

selectDataProcessor::selectDataProcessor(){}
selectDataProcessor::~selectDataProcessor(){}
EventProcessorOutput* selectDataProcessor::process (MTEvent* e, EventProcessorOutput* epOut) {
	SEND ev = *(SEND*)e;
	MyContext ctx = *(MyContext*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new MyContext(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool selectDataProcessor::isValidEvent(MTEvent* e) {return true;};
vector<MTEvent*> selectDataProcessor::own_Process(SEND& ev, MyContext& ctx, interm_out& out)
{
	vector<MTEvent*> events;
	int events_size = 0;
	int sent_size = 0;
	int i = 0;
	PKT_EVENT* pkt_ev = new PKT_EVENT(10,ev.flowId);
	int bytes_allowed = ctx.congestion_window - ctx.bytes_in_flight;
	int bytes_in_packet = 24;
	pkt_ev->address = ctx.data_addr;
	int frame_size_limit;
	if( bytes_allowed / ctx.number_streams > bytes_allowed / ctx.max_stream_per_pkt )
	{
		frame_size_limit = bytes_allowed / ctx.number_streams;
	}
	else
	{
		frame_size_limit = bytes_allowed / ctx.max_stream_per_pkt;
	}
	PacketInfo pkt_info;
	while( bytes_allowed > 0 )
	{
		i=0;
		QuicStream qs;
		//cout<<sent_size <<" , "<< ctx.size_limit <<" , "<< i <<" , "<< ctx.streams.size() <<" , "<< bytes_allowed <<" , "<< 0<<endl;
		while( sent_size < ctx.size_limit && i < ctx.streams.size() && bytes_allowed > 0 )
		{
			qs = ctx.streams[ i ];
			Frame frame;
			pkt_info.stream_id.push_back(i);
			int data_len = qs.frame_size_limit;
			//cout<<data_len<<endl;
			if( data_len > bytes_allowed )
			{
				data_len = bytes_allowed;
			}
			//cout<<data_len<<endl;
			if( data_len > frame_size_limit )
			{
				data_len = frame_size_limit;
			}
			//cout<<data_len<<endl;
			if( data_len > qs.length - qs.last_sent )
			{
				data_len = qs.length - qs.last_sent;
			}
			//cout<<data_len<<endl;
			frame.data_length = data_len;
			pkt_info.frame_size.push_back(data_len);
			pkt_info.start_point.push_back(qs.last_sent);
			pkt_info.list_size = pkt_info.list_size + 1;
			frame.offset = qs.last_sent;
			qs.last_sent = qs.last_sent + frame.data_length;
			pkt_ev->frame.push_back(frame);
			pkt_ev->frame_size = pkt_ev->frame_size + 1;
			out.frames.push_back(frame);
			out.frames_size = out.frames_size + 1;
			ctx.bytes_in_flight = ctx.bytes_in_flight + frame.data_length;
			bytes_allowed = bytes_allowed - frame.data_length;
			i = i + 1;
		}
		pkt_info.time_sent = ns3::Simulator::Now().GetSeconds();
		QuicHeader qheader;
		qheader.pkt_id = ctx.id_counter + 1;
		ctx.id_counter = ctx.id_counter + 1;
		pkt_info.packet_id = qheader.pkt_id;
		pkt_ev->qheader = qheader;
		ctx.sent_packets.push_back(pkt_info);
		ctx.sent_packets_size = ctx.sent_packets_size + 1;
		events.push_back(pkt_ev);
	}
	return events;
}
sendProcessor::sendProcessor(){}
sendProcessor::~sendProcessor(){}
EventProcessorOutput* sendProcessor::process (MTEvent* e, EventProcessorOutput* epOut) {
	SEND  ev = *(SEND *)e;
	MyContext ctx = *(MyContext*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new MyContext(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool sendProcessor::isValidEvent(MTEvent* e) {return true;};
vector<MTEvent*> sendProcessor::own_Process(SEND & ev, MyContext& ctx, interm_out& out)
{
	vector<MTEvent*> events;
	TIMER* timer_event = new TIMER(10,ev.flowId);
	PacketInfo info;
	if( info.in_flight )
	{
		if( info.ack_eliciting )
		{
			ctx.time_of_last_ack_eliciting_packet = ns3::Simulator::Now().GetSeconds();
		}
		ctx.timer.stop(  );
		ctx.timer.set_duration( ctx.kTimeThreshold );
		ctx.timer.start( timer_event );
	}
	return events;
}
ackProcessor::ackProcessor(){}
ackProcessor::~ackProcessor(){}
EventProcessorOutput* ackProcessor::process (MTEvent* e, EventProcessorOutput* epOut) {
	ACK ev = *(ACK*)e;
	MyContext ctx = *(MyContext*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new MyContext(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool ackProcessor::isValidEvent(MTEvent* e) {return true;};
vector<MTEvent*> ackProcessor::own_Process(ACK& ev, MyContext& ctx, interm_out& out)
{
	vector<MTEvent*> events;
	if( ctx.largest_acked_packet == -1 )
	{
		ctx.largest_acked_packet = ev.largest_acked;
	}
	else
	{
		int largest_ack_pkt = ctx.largest_acked_packet;
		if( largest_ack_pkt < ev.largest_acked )
		{
			largest_ack_pkt = ev.largest_acked;
		}
		ctx.largest_acked_packet = largest_ack_pkt;
	}
	bool new_packet_acked = false;
	int acked_bytes;
	for ( int i = 0 ; i < ev.pkt_nums_counter ; i = i + 1 )
	{
		for ( int j = 0 ; j < ctx.sent_packets.size(  ) ; j = j + 1 )
		{
			if( i == ctx.sent_packets[ j ].packet_id )
			{
				if( i == ctx.largest_acked_packet )
				{
					ctx.largest_acked_time = ctx.sent_packets[ j ].time_sent;
				}
				out.acked_packets[ out.acked_packets_size ] = ctx.sent_packets[ j ];
				out.acked_packets_size = out.acked_packets_size + 1;
				acked_bytes = acked_bytes + ctx.sent_packets[ j ].size;
				for ( int k = j ; k < ctx.sent_packets_size ; k = k + 1 )
				{
					ctx.sent_packets[ k ] = ctx.sent_packets[ k + 1 ];
				}
				ctx.sent_packets_size = ctx.sent_packets_size - 1;
				new_packet_acked = true;
				break;
			}
		}
	}
	ctx.bytes_in_flight = ctx.bytes_in_flight - acked_bytes;
	if( !new_packet_acked )
	{
		return events;
	}
	ctx.latest_rtt = ns3::Simulator::Now().GetSeconds() - ctx.largest_acked_time;
	ctx.update_rtt = true;
	if( ev.ECN_CE_Count > ctx.ecn_ce_counters )
	{
		ctx.ecn_ce_counters = ev.ECN_CE_Count;
		out.in_congestion = true;
		out.start_time = ctx.largest_acked_packet;
	}
	return events;
}
updateRttProcessor::updateRttProcessor(){}
updateRttProcessor::~updateRttProcessor(){}
EventProcessorOutput* updateRttProcessor::process (MTEvent* e, EventProcessorOutput* epOut) {
	ACK ev = *(ACK*)e;
	MyContext ctx = *(MyContext*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new MyContext(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool updateRttProcessor::isValidEvent(MTEvent* e) {return true;};
vector<MTEvent*> updateRttProcessor::own_Process(ACK& ev, MyContext& ctx, interm_out& out)
{
	vector<MTEvent*> events;
	if( !ctx.update_rtt )
	{
		return events;
	}
	ctx.update_rtt = false;
	if( ctx.first_rtt_sample == 0 )
	{
		ctx.min_rtt = ctx.latest_rtt;
		ctx.smoothed_rtt = ctx.latest_rtt;
		ctx.rttvar = ctx.latest_rtt / 2;
		ctx.first_rtt_sample = ns3::Simulator::Now().GetSeconds();
		return events;
	}
	int rtt = ctx.min_rtt;
	if( rtt > ctx.latest_rtt )
	{
		rtt = ctx.latest_rtt;
	}
	ctx.min_rtt = rtt;
	int delay = ctx.ack_delay;
	if( delay > ctx.max_ack_delay )
	{
		delay = ctx.max_ack_delay;
	}
	ctx.ack_delay = delay;
	ctx.adjusted_rtt = ctx.latest_rtt;
	if( ctx.latest_rtt >= ctx.min_rtt + ctx.ack_delay )
	{
		ctx.adjusted_rtt = ctx.latest_rtt - ctx.ack_delay;
	}
	ctx.rttvar = 3 / 4 * ctx.rttvar + 1 / 4 * abs( ctx.smoothed_rtt - ctx.adjusted_rtt );
	ctx.smoothed_rtt = 7 / 8 * ctx.smoothed_rtt + 1 / 8 * ctx.adjusted_rtt;
	return events;
}
adjustWindowProcessor::adjustWindowProcessor(){}
adjustWindowProcessor::~adjustWindowProcessor(){}
EventProcessorOutput* adjustWindowProcessor::process (MTEvent* e, EventProcessorOutput* epOut) {
	ACK  ev = *(ACK *)e;
	MyContext ctx = *(MyContext*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new MyContext(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool adjustWindowProcessor::isValidEvent(MTEvent* e) {return true;};
vector<MTEvent*> adjustWindowProcessor::own_Process(ACK & ev, MyContext& ctx, interm_out& out)
{
	vector<MTEvent*> events;
	for ( int i = 0 ; i < out.acked_packets.size(  ) ; i = i + 1 )
	{
		if( out.acked_packets[ i ].time_sent <= ctx.congestion_recovery_start_time )
		{
			continue;
		}
		if( ctx.congestion_window < ctx.ssthresh )
		{
			ctx.congestion_window = ctx.congestion_window + out.acked_packets[ i ].size;
		}
		else
		{
			ctx.congestion_window = ctx.congestion_window + ctx.max_datagram_size * out.acked_packets[ i ].size / ctx.congestion_window;
		}
	}
	if( ctx.congestion_window - ctx.bytes_in_flight > ctx.ssthresh )
	{
		SEND* newEv = new SEND(10,ev.flowId);
		events.push_back(newEv);
	}
	return events;
}
congestionProcessor::congestionProcessor(){}
congestionProcessor::~congestionProcessor(){}
EventProcessorOutput* congestionProcessor::process (MTEvent* e, EventProcessorOutput* epOut) {
	TIMER ev = *(TIMER*)e;
	MyContext ctx = *(MyContext*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new MyContext(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool congestionProcessor::isValidEvent(MTEvent* e) {return true;};
vector<MTEvent*> congestionProcessor::own_Process(TIMER& ev, MyContext& ctx, interm_out& out)
{
	vector<MTEvent*> events;
	if( out.start_time <= ctx.congestion_recovery_start_time || !out.in_congestion )
	{
		return events;
	}
	ctx.congestion_recovery_start_time = ns3::Simulator::Now().GetSeconds();
	ctx.ssthresh = ctx.congestion_window * ctx.lossReductionFactor;
	int cwnd = ctx.ssthresh;
	if( cwnd < ctx.minimumWindow )
	{
		cwnd = ctx.minimumWindow;
	}
	ctx.congestion_window = cwnd;
	return events;
}
lossDetectionProcessor::lossDetectionProcessor(){}
lossDetectionProcessor::~lossDetectionProcessor(){}
EventProcessorOutput* lossDetectionProcessor::process (MTEvent* e, EventProcessorOutput* epOut) {
	ACK  ev = *(ACK *)e;
	MyContext ctx = *(MyContext*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new MyContext(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool lossDetectionProcessor::isValidEvent(MTEvent* e) {return true;};
vector<MTEvent*> lossDetectionProcessor::own_Process(ACK & ev, MyContext& ctx, interm_out& out)
{
	vector<MTEvent*> events;
	vector<PacketInfo> lost_packets;
	int lost_packets_size = 0;
	int loss_delay = ctx.kTimeThreshold;
	int loss_threshold = ns3::Simulator::Now().GetSeconds() - loss_delay;
	int last_loss = 0;
	for ( int i = 0 ; i < ctx.sent_packets.size(  ) ; i = i + 1 )
	{
		if( ctx.sent_packets[ i ].packet_id > ctx.largest_acked_packet )
		{
			continue;
		}
		if( ctx.sent_packets[ i ].time_sent > loss_threshold || ctx.largest_acked_packet >= ctx.sent_packets[ i ].packet_id + ctx.kPacketThresh )
		{
			lost_packets[ lost_packets_size ] = ctx.sent_packets[ i ];
			lost_packets_size = lost_packets_size + 1;
			if( last_loss < ctx.sent_packets[ i ].time_sent )
			{
				last_loss = ctx.sent_packets[ i ].time_sent;
			}
			for ( int j = i ; j < ctx.sent_packets.size(  ) - 1 ; j = j + 1 )
			{
				ctx.sent_packets[ j ] = ctx.sent_packets[ j + 1 ];
			}
			ctx.sent_packets_size = ctx.sent_packets_size - 1;
		}
	}
	out.lost_packets = lost_packets;
	if( lost_packets.size(  ) > 0 )
	{
		out.in_congestion = true;
		out.start_time = last_loss;
	}
	return events;
}
retransmitProcessor::retransmitProcessor(){}
retransmitProcessor::~retransmitProcessor(){}
EventProcessorOutput* retransmitProcessor::process (MTEvent* e, EventProcessorOutput* epOut) {
	ACK  ev = *(ACK *)e;
	MyContext ctx = *(MyContext*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new MyContext(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool retransmitProcessor::isValidEvent(MTEvent* e) {return true;};
vector<MTEvent*> retransmitProcessor::own_Process(ACK & ev, MyContext& ctx, interm_out& out)
{
	vector<MTEvent*> events;
	int events_size = 0;
	if( out.lost_packets.size(  ) == 0 )
	{
		return events;
	}
	for ( int j = 0 ; j < out.lost_packets.size(  ) ; j = j + 1 )
	{
		PacketInfo lost_packet = out.lost_packets[ j ];
		PKT_EVENT* pkt_ev = new PKT_EVENT(10,ev.flowId);
		pkt_ev->address = ctx.data_addr;
		QuicStream qs;
		PacketInfo pkt_info = lost_packet;
		for ( int i = 0 ; i < lost_packet.stream_id.size(  ) ; i = i + 1 )
		{
			QuicStream qs = ctx.streams[ lost_packet.stream_id[ i ] ];
			Frame frame;
			frame.data_length = lost_packet.frame_size[ i ];
			frame.address = qs.address;
			pkt_ev->frame[ pkt_ev->frame_size ] = frame;
			pkt_ev->frame_size = pkt_ev->frame_size + 1;
		}
		QuicHeader qheader;
		qheader.pkt_id = ctx.sent_packets.size(  );
		pkt_info.packet_id = qheader.pkt_id;
		pkt_ev->qheader = qheader;
		ctx.sent_packets[ ctx.sent_packets_size ] = pkt_info;
		ctx.sent_packets_size = ctx.sent_packets_size + 1;
		events[ events_size ] = pkt_ev;
		events_size = events_size + 1;
	}
	return events;
}
addStreamProcessor::addStreamProcessor(){}
addStreamProcessor::~addStreamProcessor(){}
EventProcessorOutput* addStreamProcessor::process (MTEvent* e, EventProcessorOutput* epOut) {
	ADD_DATA ev = *(ADD_DATA*)e;
	MyContext ctx = *(MyContext*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new MyContext(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool addStreamProcessor::isValidEvent(MTEvent* e) {return true;};
vector<MTEvent*> addStreamProcessor::own_Process(ADD_DATA& ev, MyContext& ctx, interm_out& out)
{
	vector<MTEvent*> events;
	QuicStream qs;
	qs.length = ev.data_length;
	if( ev.server_side == true )
	{
		ctx.server_stream_counter = ctx.server_stream_counter + 2;
		qs.id = ctx.server_stream_counter;
	}
	else
	{
		ctx.client_stream_counter = ctx.client_stream_counter + 2;
		qs.id = ctx.client_stream_counter;
	}
	qs.address = ev.address;
	ctx.streams.push_back(qs);
	ctx.number_streams+=1;//TBA
	ctx.streams_size = ctx.streams_size + 1;
	SEND* e = new SEND(10,ev.flowId);
	events.push_back(e);
	return events;
}
storeDataProcessor::storeDataProcessor(){}
storeDataProcessor::~storeDataProcessor(){}
EventProcessorOutput* storeDataProcessor::process (MTEvent* e, EventProcessorOutput* epOut) {
	DATA_ARRIVAL ev = *(DATA_ARRIVAL*)e;
	MyContext ctx = *(MyContext*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new MyContext(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool storeDataProcessor::isValidEvent(MTEvent* e) {return true;};
vector<MTEvent*> storeDataProcessor::own_Process(DATA_ARRIVAL& ev, MyContext& ctx, interm_out& out)
{
	vector<MTEvent*> events;
	ctx.recieved_packets[ ev.packet_id ] = true;
	if( ev.packet_id > ctx.r_largest_acked )
	{
		ctx.r_largest_acked = ev.packet_id;
	}
	for ( int k = 0 ; k < ev.frames.size(  ) ; k = k + 1 )
	{
		int curr_id = -1;
		for ( int j = 0 ; j < ctx.qsbs.size(  ) ; j = j + 1 )
		{
			if( ctx.qsbs[ j ].id == ev.frames[ k ].stream_id )
			{
				curr_id = j;
				break;
			}
		}
		if( curr_id == -1 )
		{
			QuicStreamBuffer qsb;
			qsb.offset = 0;
			qsb.id = ev.frames[ k ].stream_id;
			curr_id = ev.frames[ k ].stream_id;
			ctx.qsbs[ ctx.qsbs_size ] = qsb;
			ctx.qsbs_size = ctx.qsbs_size + 1;
		}
		for ( int i = 0 ; i < ev.frames[ k ].data_length ; i = i + 1 )
		{
			int buffer_idx = i + ev.frames[ k ].offset - ctx.qsbs[ curr_id ].offset;
			ctx.qsbs[ curr_id ].received[ buffer_idx ] = true;
		}
	}
	return events;
}
ackGenerationProcessor::ackGenerationProcessor(){}
ackGenerationProcessor::~ackGenerationProcessor(){}
EventProcessorOutput* ackGenerationProcessor::process (MTEvent* e, EventProcessorOutput* epOut) {
	DATA_ARRIVAL ev = *(DATA_ARRIVAL*)e;
	MyContext ctx = *(MyContext*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new MyContext(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool ackGenerationProcessor::isValidEvent(MTEvent* e) {return true;};
vector<MTEvent*> ackGenerationProcessor::own_Process(DATA_ARRIVAL& ev, MyContext& ctx, interm_out& out)
{
	vector<MTEvent*> events;
	ackFrame frame;
	frame.frameType = 2;
	// if( !frame.ack_eliciting )
	// {
	// 	return events;
	// }
	frame.largest_acked = ctx.largest_acked_packet;
	int i = ctx.largest_acked_packet - 1;
	int count = 0;
	while( ctx.recieved_packets[ i ] && i >= 0 )
	{
		count = count + 1;
	}
	frame.first_ack_range = count;
	bool count_gap = true;
	AckRange range;
	count = 0;
	for ( int j = i ; j >= 0 ; j = j - 1 )
	{
		if( count_gap && ctx.recieved_packets[ j ] == true )
		{
			range.gap = count;
			count = 1;
			count_gap = false;
		}
		else
		{
			if( !count_gap && ctx.recieved_packets[ j ] == false )
			{
				range.ack_range_length = count;
				frame.ack_ranges[ frame.ack_ranges_size ] = range;
				frame.ack_ranges_size = frame.ack_ranges_size + 1;
				count = 1;
				count_gap = true;
			}
			else
			{
				count = count + 1;
			}
		}
	}
	if( count_gap )
	{
		range.gap = count;
	}
	else
	{
		range.ack_range_length = count;
	}
	frame.ack_ranges[ frame.ack_ranges_size ] = range;
	frame.ack_ranges_size = frame.ack_ranges_size + 1;
	out.frames[ out.frames_size ] = frame;
	out.frames_size = out.frames_size + 1;
	return events;
}
packetGenerationProcessor::packetGenerationProcessor(){}
packetGenerationProcessor::~packetGenerationProcessor(){}
EventProcessorOutput* packetGenerationProcessor::process (MTEvent* e, EventProcessorOutput* epOut) {
	SEND ev = *(SEND*)e;
	MyContext ctx = *(MyContext*)epOut->ctx;
	interm_out int_out = *(interm_out*)epOut->intermOutput;
	EventProcessorOutput* epOutput = new EventProcessorOutput();
	vector<MTEvent*> newEvents = own_Process(ev, ctx, int_out);
	epOutput->events = epOut->events;
	cout<<"Adding new events of size: "<<newEvents.size()<<endl;
	epOutput->events.insert(epOutput->events.end(),newEvents.begin(),newEvents.end());
	cout<<"Current Events size: "<<epOutput->events.size()<<endl;
	epOutput->ctx = new MyContext(ctx);
	epOutput->intermOutput = new interm_out(int_out);
	return epOutput;
}
bool packetGenerationProcessor::isValidEvent(MTEvent* e) {return true;};
vector<MTEvent*> packetGenerationProcessor::own_Process(SEND& ev, MyContext& ctx, interm_out& out)
{
	vector<MTEvent*> events;
	PKT_EVENT* pkt_ev = new PKT_EVENT(10,ev.flowId);
	pkt_ev->address = ctx.data_addr;
	for ( int i = 0 ; i < out.frames.size(  ) ; i = i + 1 )
	{
		pkt_ev->frame.push_back( out.frames[ i ]);
		pkt_ev->frame_size = pkt_ev->frame_size + 1;
	}
	PacketInfo pkt_info;
	pkt_info.time_sent = ns3::Simulator::Now().GetSeconds();
	QuicHeader qheader;
	ctx.id_counter = ctx.id_counter + 1;
	qheader.pkt_id = ctx.id_counter;
	pkt_info.packet_id = qheader.pkt_id;
	pkt_ev->qheader = qheader;
	ctx.sent_packets[ ctx.sent_packets_size ] = pkt_info;
	ctx.sent_packets_size = ctx.sent_packets_size + 1;
	events.push_back(pkt_ev);
	return events;
}
