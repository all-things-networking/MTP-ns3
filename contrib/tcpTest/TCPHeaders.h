#include "ns3/mt-header.h"

class TCPheader : public ns3::MTHeader
{
	public:
	int src_port;
	int dest_port;
	int seq;
	int ack_seq;
	int ack;
	int window;
};