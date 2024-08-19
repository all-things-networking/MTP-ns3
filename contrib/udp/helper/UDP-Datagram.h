#ifndef UDP_DATAGRAM_H
#define UDP_DATAGRAM_H

#include <string>

// ==========================================================================================
// QUESTIONS/TODOS:
//   - What operations do we need to perform before send and after received? 
//     - Serialization, deserialization most likely
//   - How to incorporate the MTHeader class into these class definitions?
//   - Determine checksum computation algorithm, implement if necessary (if it isn't implemented in MTP doc)
// ==========================================================================================

class Datagram {
  public:
    short sourcePort;
    short destinationPort;
    short length;
    short checksum;
    char * data;

    Datagram(short sourcePort, short destinationPort, short length, short checksum, char * data) {
      this->sourcePort = sourcePort;
      this->destinationPort = destinationPort;
      this->length = length;
      this->checksum = checksum;
      this->data = data;
    }

    int GenPseudoHeader();
    int ComputeCheckSum();
    void OpsBeforeSend(); // Compute Hash, call by processor before send?
    void OpsAfterReceived(); //Just produce event, leave verify hash to processor?
}

#endif