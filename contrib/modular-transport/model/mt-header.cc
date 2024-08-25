/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "mt-header.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("MTHeader");

NS_OBJECT_ENSURE_REGISTERED(MTHeader);

TypeId
MTHeader::GetTypeId()
{
    static TypeId tid = TypeId("ns3::MTHeader")
                            .SetParent<Header>()
                            .SetGroupName("ModularTransport")
                            .AddConstructor<MTHeader>();
    return tid;
}

TypeId
MTHeader::GetInstanceTypeId() const
{
    return GetTypeId();
}

MTHeader::MTHeader()
{}

MTHeader::~MTHeader()
{}

uint32_t
MTHeader::GetSerializedSize() const
{
    return 4;
}

void
MTHeader::Serialize(Buffer::Iterator start) const
{
    Buffer::Iterator i = start;
    i.WriteHtonU32(0);
}

uint32_t
MTHeader::Deserialize(Buffer::Iterator start)
{
    Buffer::Iterator i = start;
    int unusedForNow = i.ReadNtohU32();
    return GetSerializedSize();
}

std::ostream&
operator<<(std::ostream& os, const MTHeader& h)
{
    h.Print(os);
    return os;
}

} // ns3 namespace
