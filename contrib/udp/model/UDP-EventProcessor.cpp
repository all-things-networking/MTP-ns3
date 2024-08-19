#ifndef UDP_EVENT_PROCESSOR_H
#define UDP_EVENT_PROCESSOR_H

#include "ns3/mt-eventprocessor.h"
#include "UDP-Event.h"
#include "UDP-Context.h"

// ==========================================================================================
// QUESTIONS/TODOS:
//   - Do we need to define these as classes or can they be standalone functions?
//   - Do we need the intermediate output class here (as the third parameter to each processor definition 
//      below)? It doesn't seem like it, since UDP is so simple that there doesn't appear to be a need to 
//      chain multiple processors together. Perhaps we still include it to ensure compatibility with MTP?
//     - Could separate and then chain some processors together for modularity, e.g. a processor for verifying
//       checksum followed by a processor for deserializing data, but then...
//     - Which functionality belongs to opsBeforeSend in the Datagram definition vs. in the process_send definition here?
//       (for example, where would deserialization go?)
// ==========================================================================================

class SendIntermediateOutput : public MTIntermediateOutput {
  public:
    bool checksumComputed;
    bool dataSerialized;
}

class ReceiveIntermediateOutput : public MTIntermediateOutput {
  public:
    bool checksumSuccessful;
    bool dataDeserialized;
}

// this should probably do something similar to packet generation processor in QUIC_TEL example
// - how do we construct the packet? where do we draw the IP addresses to include in the header from?
std::vector<UDPEvent *> process_send(UDPEvent * ev, UDPContext *ctx) {

}

// should our receive logic be inside this processor or in a whole custom class like QUICReceiveLogic in QUIC_TEL?
std::vector<UDPEvent *> process_receive(UDPEvent * ev, UDPContext *ct) {

}

#endif