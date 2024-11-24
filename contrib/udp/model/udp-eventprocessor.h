#ifndef UDP_EVENTPROCESSOR_H
#define UDP_EVENTPROCESSOR_H

#include "ns3/mt-eventprocessor.h"
#include "ns3/udp-header.h"
#include "ns3/udp-event.h"
#include "ns3/udp-context.h"
namespace ns3 {
  class UDPSendProcessor: public MTEventProcessor {
    public:
      UDPSendProcessor() {}
      virtual ~UDPSendProcessor() {}
      EventProcessorOutput* process(MTEvent * e, EventProcessorOutput* epOut) override;
      bool isValidEvent(MTEvent* e) override;
  };

  class UDPRecvProcessor : public MTEventProcessor {
    public:
      UDPRecvProcessor() {}
      virtual ~UDPRecvProcessor() {}
      EventProcessorOutput* process(MTEvent* e, EventProcessorOutput* epOut) override;
      bool isValidEvent(MTEvent* e) override;
  };

  class UDPPktProcessor : public MTEventProcessor {
    public:
      UDPPktProcessor() {}
      virtual ~UDPPktProcessor() {}
      EventProcessorOutput* process(MTEvent* e, EventProcessorOutput* epOut) override;
      bool isValidEvent(MTEvent* e) override;
  };

  class UDPFbProcessor : public MTEventProcessor {
    public:
      UDPFbProcessor() {}
      virtual ~UDPFbProcessor() {}
      EventProcessorOutput* process(MTEvent* e, EventProcessorOutput* epOut) override;
      bool isValidEvent(MTEvent* e) override;
  };
}

#endif