#ifndef QUICSTRUCTS_H
#define QUICSTRUCTS_H

using namespace std;
using namespace ns3;


class QuicStream
{
	public:
	
	char address;
	int id;
	int frame_size_limit = 1440;
	int last_sent = 0;
	int length = 0;
	vector<bool> acked_frames;
};
class QuicStreamBuffer
{
	public:
	
	int id;
	int offset;
	vector < char > data;
	vector<bool> received;
	char address;
};
class PacketInfo
{
	public:
	
	int packet_id;
	int time_sent;
	bool in_flight;
	bool ack_eliciting;
	int size;
	vector<int> stream_id;
	vector<int> frame_size;
	vector<int> start_point;
	int list_size = 0;
};
class Frame
{
	public:
	
	int data_length;
	int stream_id;
	int offset;
	char address;
};
class AckRange
{
	public:
	
	int gap;
	int ack_range_length;
};
class ackFrame :public Frame
{
	public:
	
	int frameType;
	int largest_acked;
	float ack_delay;
	int range_count;
	int first_ack_range;
	vector<AckRange> ack_ranges;
	int ack_ranges_size = 0;
	int ecn_count;
};

class interm_out: public MTIntermediateOutput
{
	public:
	PacketInfo info;
	vector<PacketInfo> lost_packets;
	vector<Frame> frames;
	int frames_size;
	bool in_congestion;
	int start_time;
	vector<PacketInfo> acked_packets;
	int acked_packets_size = 0;
	interm_out(){}
};

#endif