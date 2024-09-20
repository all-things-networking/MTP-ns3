using namespace std;
using namespace ns3;
#include <vector>
#include "QUICStructs.h"
#include "ns3/mt-timer.h"
class MyContext : public MTContext
{
	public:
	char data_addr = 0;
	int number_streams=0;
	vector<QuicStream> streams;
	int streams_size = 0;
	vector<PacketInfo> sent_packets;
	int sent_packets_size = 0;
	int num_sent_packets;
	int curr_idx;
	int size_limit=2000000;
	int MAX_STREAMS;
	int id_counter = 0;
	int server_stream_counter = 0;
	int client_stream_counter = 0;
	int largest_acked_time = 0;
	int packet_size_limit;
	int kPacketThresh = 3;
	int kTimeThreshold;
	int time_of_last_ack_eliciting_packet = 0;
	int largest_acked_packet = -1;
	int kGranularity;
	int pto_count = 0;
	int latest_rtt = 0;
	int smoothed_rtt;
	int rttvar;
	int min_rtt = 0;
	int adjusted_rtt;
	int first_rtt_sample = 0;
	int loss_time;
	bool update_rtt = false;
	int initialWindow = 14720;
	int minimumWindow;
	float lossReductionFactor = 0.500000;
	int persistentCongestionThreshold = 3;
	int max_datagram_size;
	int bytes_in_flight = 0;
	int congestion_window = 14720;
	int congestion_recovery_start_time = 0;
	int ssthresh = -1;
	int ecn_ce_counters = 0;
	int ack_delay;
	vector<bool> recieved_packets = vector<bool>(500);
	int r_largest_acked;
	vector<QuicStreamBuffer> qsbs = vector<QuicStreamBuffer>(500);
	int qsbs_size = 0;
	int move_to_memory_size_thresh = 100;
	int max_stream_per_pkt = 6;
	int max_ack_delay;
	MTTimer timer;
};
