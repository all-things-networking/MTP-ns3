#ifndef MTUDP_H
#define MTUDP_H

#include "ns3/modular-transport.h"
#include "ns3/mt-context.h"

class MTTCP: public ns3::ModularTransport
{
private:
    /* data */
public:
    MTTCP(/* args */);
    ~MTTCP();
    ns3::MTContext* InitContext(flow_id fid)override;
    void print_debugging_info(flow_id fid)override;
};

#endif