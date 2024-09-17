#include "TCPTXNet.h"
#include "TCPEvents.h"
#include "TCPHeaders.h"
#include "ns3/ptr.h"

using namespace ns3;



Ptr<Packet> TCPTXNet::get_next_packet(MTEvent* event){
  PKT_EVENT* pkt_ev = (PKT_EVENT*)event;
  TCPheader hdr;
  hdr.src_port = 1;
  hdr.dest_port =2;
  hdr.seq = pkt_ev->seq_num;
  hdr.ack = pkt_ev->ack_flag;
  std::cout <<"Creating Packet With seq num = "<<((pkt_ev->ack_flag)?pkt_ev->ack_num:pkt_ev->seq_num)<< std::endl;

  hdr.ack_seq = pkt_ev->ack_num;
  hdr.window = pkt_ev->wnd_size;
  Packet* pkt = new Packet;
  pkt->AddHeader(hdr);
  pkt->AddPaddingAtEnd(pkt_ev->data_len);
  return Ptr<Packet>(pkt);
}