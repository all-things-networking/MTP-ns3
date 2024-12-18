#ifndef MTUDP_H
#define MTUDP_H

#include "ns3/modular-transport.h"
#include "ns3/mt-context.h"
#include "ns3/mtp-types.h"
#include "ns3/mt-flow-id.h"
#include "ns3/udp-rxapp.h"
#include "ns3/udp-txnet.h"
#include "ns3/udp-rxnet.h"
#include "ns3/udp-txapp.h"
#include "ns3/udp-dispatcher.h"

namespace ns3 { 
  class MTUDP: public ModularTransport
  {
    private:
      /* data */
    public:
      MTUDP();
      ~MTUDP();
      MTContext* InitContext(flow_id fid);
  };
}

#endif