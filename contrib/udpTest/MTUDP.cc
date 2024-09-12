#include "MTUDP.h"
#include "UDPRXApp.h"
#include "UDPDispatcher.h"

using namespace ns3;

MTUDP::MTUDP()
{
    this->rxapp = new UDPRXAppParser();
    this->dispatcher = new UDPDispatcher();
    
}

MTUDP::~MTUDP()
{
    
}