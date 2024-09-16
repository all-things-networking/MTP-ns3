#include "TCPTXNet.h"
#include "TCPEvents.h"
#include "ns3/mt-header.h"
#include "ns3/ptr.h"

using namespace ns3;

class TCPheader : public MTHeader
{
	public:
	int src_port;
	int dest_port;
	int seq;
	int ack_seq;
	int ack;
	int window;
};

Ptr<Packet> TCPTXNet::get_next_packet(MTEvent* event){
  PKT_EVENT* pkt_ev = (PKT_EVENT*)event;
  TCPheader hdr;
  hdr.src_port = 1;
  hdr.dest_port =2;
  hdr.seq = pkt_ev->seq_num;
  hdr.ack = 0;
  hdr.ack_seq = 0;
  hdr.window = pkt_ev->wnd_size;
  Packet* pkt = new Packet;
  pkt->AddHeader(hdr);
  return Ptr<Packet>(pkt);
}