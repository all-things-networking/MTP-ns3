#include "MTUDP.h"
#include "UDPRXApp.h"
#include "UDPDispatcher.h"
#include "UDPContext.h"
#include "UDPStructs.h"

using namespace ns3;

MTUDP::MTUDP()
{
    this->rxapp = new UDPRXAppParser();
    this->dispatcher = new UDPDispatcher();
    this->interm_output = new interm_out();
}

MTUDP::~MTUDP()
{
    
}

MTContext* MTUDP::InitContext(flow_id fid){
    MTContext* mtctx = new myContext();
    ctx_table[fid]= mtctx;
    return mtctx;
}