#ifndef MT_CONTEXT_H
#define MT_CONTEXT_H

#include <ctime> // std::time_t
#include <map>
#include "ns3/ipv4-address.h"

namespace ns3
{
class ModularTransport;

/**
 * \brief contains information that is shared among all event processors of a given connection
*/
class MTContext{
public:
    MTContext();
    virtual ~MTContext();
};

} // namespace ns3

#endif
