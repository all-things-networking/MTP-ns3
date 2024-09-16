#include"TCPRXNet.h"
#include"TCPHeaders.h"
#include"TCPEvents.h"
#include<vector>

using namespace std;
using namespace ns3;

std::vector<ns3::MTEvent*> TCPRXNetParser::packet_parser(ns3::Ipv4Header iphdr, ns3::Ptr<ns3::Packet> pkt){
    vector <MTEvent*> events;

    TCPheader tcphdr;
    GetPointer(pkt)->PeekHeader(tcphdr);
    std::cout <<"Parsing TCP "<<tcphdr.ack<< std::endl;
        if(tcphdr.ack == 0) {
            DATA *data_ev = new DATA(10,0);
            data_ev->seq_num = tcphdr.seq;
            data_ev->data_len = GetPointer(pkt)->GetSize();
            events.push_back(data_ev);
        }

        if(tcphdr.ack == 1) {
            ACK* ack_ev = new ACK(10,0);
            ack_ev->ack_seq = tcphdr.ack_seq;
            ack_ev->rwnd_size = tcphdr.window;
            events.push_back(ack_ev);
        }
        return events;
}