#ifndef UDPSTRUCTS_H
#define UDPSTRUCTS_H

using namespace std;
using namespace ns3;
#include "TCPEvents.h"

class sent_pkt_info
{
	public:
	
	int seq_num;
	int data_len;
};

class interm_out: public MTIntermediateOutput
{
	public:
	bool change_cwnd;
	bool skip_ack_eps;
	interm_out(){}
};

#endif