#include "UDP-Datagram.h"

namespace ns3 {

int Datagram::GenPseudoHeader() {
  return 0;
}

int Datagram::ComputeCheckSum() {
  //To be implemented
  return 0;
}

void Datagram::OpsBeforeSend() {
    
}

void Datagram::OpsAfterReceived() { //Return A event to be added to Queue?
    int verifyChecksum = this->ComputeCheckSum();
    if (verifyChecksum != this->checksum) {
        //Check sum failed
    }//else continue
    //return a event
}

} // namespace ns3