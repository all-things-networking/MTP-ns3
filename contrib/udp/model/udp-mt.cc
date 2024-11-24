#include "ns3/udp-mt.h"
#include "ns3/udp-rxapp.h"
#include "ns3/udp-txnet.h"
#include "ns3/udp-rxnet.h"
#include "ns3/udp-dispatcher.h"

namespace ns3 {
  MTUDP::MTUDP() {
    scheduler = new MTScheduler();
    rxapp = new UDPRXAppParser();
    // txnet = new UDPTXNetScheduler();
    // rxnet = new UDPRXNetParser(scheduler);
    dispatcher = new UDPDispatcher();
    // interm_output = new MTIntermediateOutput();
    ctx_table = flow_map<MTContext*>();
  }

  MTContext * MTUDP::InitContext(flow_id fid) {
    ctx_table[fid] = new UDPContext();
    return ctx_table[fid];
  }

  MTUDP::~MTUDP() {
    delete rxapp;
    delete scheduler;
    delete dispatcher;
    // delete txnet;
    // delete rxnet;
    // delete interm_output;
  }
}