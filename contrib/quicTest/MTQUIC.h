#ifndef MTUDP_H
#define MTUDP_H

#include "ns3/modular-transport.h"
#include "ns3/mt-context.h"

class MTQUIC: public ns3::ModularTransport
{
private:
    /* data */
public:
    MTQUIC(/* args */);
    ~MTQUIC();
    ns3::MTContext* InitContext(flow_id fid)override;
    void print_debugging_info(flow_id fid)override;
};

#endif