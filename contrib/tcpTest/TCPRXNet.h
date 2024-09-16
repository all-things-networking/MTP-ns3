#ifndef TCP_RX_NET_H
#define TCP_RX_NET_H

#include"ns3/mt-rxnet.h"

#include<vector>

class TCPRXNetParser: public ns3::MTRXNetParser {
  public:
    TCPRXNetParser(){}

    std::vector<ns3::MTEvent*> packet_parser(ns3::Ipv4Header iphdr, ns3::Ptr<ns3::Packet> pkt);
};

#endif