#include "UDP-Header.h"

namespace ns3{
int UDPHeader::GenPseudoHeader() {
    return 0;
}

int UDPHeader::ComputeCheckSum() {
    //To be implemented
    return 0;
}

void UDPHeader::OpsBeforeSend() {
    this->CheckSum = this->ComputeCheckSum();
    //Acknum should be set already, it's prcoesser's job

}

void UDPHeader::OpsAfterRecieved() { //Return A event to be added to Queue?
    int verifyChecksum = this->ComputeCheckSum();
    if (verifyChecksum != this->CheckSum) {
        //Check sum failed
    }//else continue
    //return a event
}

UDPHeader::UDPHeader(){

}

UDPHeader::~UDPHeader(){

}
}
