#include "MTTCP.h"
#include "TCPRXApp.h"
#include "TCPTXNet.h"
#include "TCPRXNet.h"
#include "TCPDispatcher.h"
#include "TCPContext.h"
#include "TCPStructs.h"

#include <fstream>

using namespace ns3;

MTTCP::MTTCP()
{
    this->rxapp = new TCPRXAppParser();
    this->txnet = new TCPTXNet();
    this->rxnet = new TCPRXNetParser();
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

void MTTCP::print_debugging_info(flow_id fid){
    ofstream cwndFile("data.csv",std::ios_base::app);
    tcp_context* ctx = (tcp_context*)ctx_table[fid];
    //if(ctx->send_next!=0)
    cwndFile <<Simulator::Now().GetMilliSeconds()<<","<< ctx->cwnd_size <<","<<ctx->ssthresh<<","<<ctx->duplicate_acks<<endl;

}