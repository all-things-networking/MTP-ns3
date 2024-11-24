#include "ns3/udp-dispatcher.h"

namespace ns3 {
  UDPDispatcher::UDPDispatcher() {
    sendProcessor = new UDPSendProcessor();
    recvProcessor = new UDPRecvProcessor();
    pktProcessor  = new UDPPktProcessor();
    fbProcessor   = new UDPFbProcessor();
    
    eventMap =
      {
        {"SEND", {sendProcessor}},
        {"RECV", {recvProcessor}},
        {"PKT", {pktProcessor}},
        {"FB", {fbProcessor}}
      };
  }

  UDPDispatcher::~UDPDispatcher() {
    delete sendProcessor;
    delete recvProcessor;
    delete pktProcessor;
    delete fbProcessor;
  }

  std::vector<MTEventProcessor*> UDPDispatcher::dispatch(MTEvent* event) {
    return eventMap[event->typeString];
  }
}