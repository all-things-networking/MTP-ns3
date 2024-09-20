#include"QUICRXNet.h"
#include"QUICHeaders.h"
#include"QUICEvents.h"
#include<vector>
#include<random>

using namespace std;
using namespace ns3;

int i = 0;

std::vector<ns3::MTEvent*> QUICRXNetParser::packet_parser(ns3::Ipv4Header iphdr, ns3::Ptr<ns3::Packet> pkt){
    vector <MTEvent*> events;
    QuicHeader QUIChdr;
    GetPointer(pkt)->PeekHeader(QUIChdr);
    
    //     if(QUIChdr.ack == 0) {
    //         if(/*rand()%100>97*/i%100 == 99){
    //             std::cout <<"RX Parser: Dropped a Packet. Seq_num = "<<QUIChdr.seq<< std::endl;
    //             i++;
    //             return events;
    //         }
    //         i++;
    //         std::cout <<"RX Parser: Parsing Data Packet of Sequence "<<QUIChdr.seq<< std::endl;
    //         DATA *data_ev = new DATA(10,0);
    //         data_ev->seq_num = QUIChdr.seq;
    //         data_ev->data_len = GetPointer(pkt)->GetSize()-QUIChdr.GetSerializedSize();
    //         events.push_back(data_ev);
    //     }

    //     if(QUIChdr.ack == 1) {
    //         std::cout <<"RX Parser: Parsing Ack Packet of Sequence "<<QUIChdr.ack_seq<< std::endl;
    //         ACK* ack_ev = new ACK(10,0);
    //         ack_ev->ack_seq = QUIChdr.ack_seq;
    //         ack_ev->rwnd_size = QUIChdr.window;
    //         events.push_back(ack_ev);
    //     }
        return events;
}