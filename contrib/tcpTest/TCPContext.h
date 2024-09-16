using namespace std;
using namespace ns3;
#include <vector>
#include "TCPStructs.h"
class tcp_context :public MTContext
{
	public:
	int last_ack = 429496729;
	int duplicate_acks = 0;
	int flightsize_dupl = 0;
	int ssthresh = 99999999;
	int cwnd_size = 3 * 1440;
	int RTO = 1;
	int SRTT = 0;
	int RTTVAR = 0;
	bool first_rto = 1;
	int send_una = 0;
	int send_next = 0;
	int data_end = 0;
	int last_rwnd_size = 16959;
	int rwnd_size = 16959;
	int recv_next = 0;
	vector<sent_pkt_info> data_recv_info_array;
	int data_recv_array_head = 0;
	int data_recv_array_tail = 0;
	//timer_t ack_timeout;
	char read_from_addr;
	char write_to_addr;
};
