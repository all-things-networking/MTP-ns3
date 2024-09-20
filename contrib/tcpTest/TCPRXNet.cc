#include"TCPRXNet.h"
#include"TCPHeaders.h"
#include"TCPEvents.h"
#include<vector>
#include<random>

using namespace std;
using namespace ns3;

int i = 0;

std::vector<ns3::MTEvent*> TCPRXNetParser::packet_parser(ns3::Ipv4Header iphdr, ns3::Ptr<ns3::Packet> pkt){
    vector <MTEvent*> events;
    TCPheader tcphdr;
    GetPointer(pkt)->PeekHeader(tcphdr);
        if(tcphdr.ack == 0) {
            if(/*rand()%100>97*/i%100 == 48){
                std::cout <<"RX Parser: Dropped a Packet. Seq_num = "<<tcphdr.seq<< std::endl;
                i++;
                return events;
            }
            i++;
            std::cout <<"RX Parser: Parsing Data Packet of Sequence "<<tcphdr.seq<< std::endl;
            DATA *data_ev = new DATA(10,0);
            data_ev->seq_num = tcphdr.seq;
            data_ev->data_len = GetPointer(pkt)->GetSize()-tcphdr.GetSerializedSize();
            events.push_back(data_ev);
        }

        if(tcphdr.ack == 1) {
            std::cout <<"RX Parser: Parsing Ack Packet of Sequence "<<tcphdr.ack_seq<< std::endl;
            ACK* ack_ev = new ACK(10,0);
            ack_ev->ack_seq = tcphdr.ack_seq;
            ack_ev->rwnd_size = tcphdr.window;
            events.push_back(ack_ev);
        }
        return events;
}