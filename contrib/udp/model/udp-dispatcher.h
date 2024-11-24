#ifndef UDP_DISPATCHER_H
#define UDP_DISPATCHER_H

#include "ns3/mt-dispatcher.h"
#include "ns3/udp-eventprocessor.h"

namespace ns3 {
  class UDPDispatcher : public MTDispatcher {
    protected:
      UDPSendProcessor * sendProcessor;
      UDPRecvProcessor * recvProcessor;
      UDPPktProcessor  * pktProcessor;
      UDPFbProcessor   * fbProcessor;
      std::unordered_map<std::string, std::vector<MTEventProcessor*>> eventMap;

    public:
      UDPDispatcher();
      ~UDPDispatcher();
      std::vector<MTEventProcessor*> dispatch(MTEvent* event);
  };
}

#endif