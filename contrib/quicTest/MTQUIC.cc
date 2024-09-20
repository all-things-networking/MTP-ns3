#include "MTQUIC.h"
#include "QUICRXApp.h"
#include "QUICTXNet.h"
#include "QUICRXNet.h"
#include "QUICDispatcher.h"
#include "QUICContext.h"
#include "QUICStructs.h"

#include <fstream>

using namespace ns3;

MTQUIC::MTQUIC()
{
    this->rxapp = new QUICRXAppParser();
    this->txnet = new QUICTXNet();
    this->rxnet = new QUICRXNetParser();
    this->dispatcher = new QUICDispatcher();
    this->interm_output = new interm_out();
}

MTQUIC::~MTQUIC()
{
    
}

MTContext* MTQUIC::InitContext(flow_id fid){
    MTContext* mtctx = new MyContext();
    ctx_table[fid]= mtctx;
    return mtctx;
}

void MTQUIC::print_debugging_info(flow_id fid){
    // ofstream cwndFile("data.csv",std::ios_base::app);
    // MyContext* ctx = (MyContext*)ctx_table[fid];
    // //if(ctx->send_next!=0)
    // cwndFile <<Simulator::Now().GetMilliSeconds()<<","<< ctx->cwnd_size <<","<<ctx->ssthresh<<","<<ctx->duplicate_acks<<endl;

}