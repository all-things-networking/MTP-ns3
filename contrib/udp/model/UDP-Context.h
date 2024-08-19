#ifndef UDP_CONTEXT_H
#define UDP_CONTEXT_H

#include <map>
#include <unordered_map>
#include <vector>
#include <queue>
#include "ns3/mt-state.h"
namespace ns3
{

class ModularTransport;

class UDPContext : public MTContext
{ 
public:
    UDPContext();
    ~UDPContext();

    // max payload size in UDP over IPv4 is 65507
    //  20 bytes for IP header and 8 bytes for UDP header out of 65535 (2^16 - 1) bytes for an IP packet
    int size_limit = 65507;
};
} // namespace ns3


#endif