#include "MTTCP.h"
#include "TCPRXApp.h"
#include "TCPDispatcher.h"
#include "TCPContext.h"
#include "TCPStructs.h"

using namespace ns3;

MTTCP::MTTCP()
{
    this->rxapp = new TCPRXAppParser();
    this->dispatcher = new TCPDispatcher();
    this->interm_output = new interm_out();
}

MTTCP::~MTTCP()
{
    
}

MTContext* MTTCP::InitContext(flow_id fid){
    MTContext* mtctx = new tcp_context();
    ctx_table[fid]= mtctx;
    return mtctx;
}