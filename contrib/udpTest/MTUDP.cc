#include "MTUDP.h"
#include "UDPRXApp.h"

using namespace ns3;

MTUDP::MTUDP()
{
    this->rxapp = new UDPRXAppParser();
    
}

MTUDP::~MTUDP()
{
    
}