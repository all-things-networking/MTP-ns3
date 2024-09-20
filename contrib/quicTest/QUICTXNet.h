#ifndef QUIC_TX_NET_H
#define QUIC_TX_NET_H

#include "ns3/mt-txnet.h"
#include "ns3/mt-event.h"

class QUICTXNet : public ns3::MTTXNetScheduler {
    public:
      QUICTXNet(){}
      ns3::Ptr<ns3::Packet> get_next_packet(ns3::MTEvent* event)override;
};

#endif