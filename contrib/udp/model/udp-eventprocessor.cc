#include "ns3/udp-eventprocessor.h"

namespace ns3 {
  EventProcessorOutput* create_event_processor_output(EventProcessorOutput * epOut) {
    EventProcessorOutput * newOutput = new EventProcessorOutput();
    // newOutput->packets = epOut->packets;
    newOutput->ctx = epOut->ctx;
    newOutput->events = epOut->events;
    if (epOut->intermOutput) {
      newOutput->intermOutput = epOut->intermOutput;
    } else {
      newOutput->intermOutput = new UDPIntermediateOutput();
    }
    return newOutput;
  }

  EventProcessorOutput* UDPSendProcessor::process(MTEvent * e, EventProcessorOutput* epOut) {
    EventProcessorOutput * newOutput = create_event_processor_output(epOut);
    // construct PktEvent to be added to scheduler
    UDPHeader hdr = UDPHeader();
    hdr.SetSourcePort(epOut->ctx->src_port);
    hdr.SetDestinationPort(epOut->ctx->dst_port);


    PktEvent * pktEvent = new PktEvent(e->time, e->flowId, hdr, e->data);
    newOutput->events = {pktEvent};

    // delete SendEvent; we are finished with it 
    delete e;

    return newOutput;
  }

  EventProcessorOutput* UDPRecvProcessor::process(MTEvent* e, EventProcessorOutput* epOut) {
    return create_event_processor_output(epOut);
  }

  EventProcessorOutput* UDPPktProcessor::process(MTEvent* e, EventProcessorOutput* epOut) {
    return create_event_processor_output(epOut);
  }

  EventProcessorOutput* UDPFbProcessor::process(MTEvent* e, EventProcessorOutput* epOut) {
    return create_event_processor_output(epOut);
  }
  
}





