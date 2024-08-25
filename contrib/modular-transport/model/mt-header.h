/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef MT_HEADER_H
#define MT_HEADER_H

#include "ns3/header.h"

namespace ns3
{

class MTHeader : public Header {
  public:

    static TypeId GetTypeId();

    MTHeader();
    ~MTHeader() override;
    
    /**
     * \brief Print an MT header into an output stream
     *
     * \param os output stream
     * \param h MT header to print
     * \return The ostream passed as first argument
     */
    friend std::ostream& operator<<(std::ostream& os, const MTHeader& h);
    TypeId GetInstanceTypeId() const override;
    uint32_t GetSerializedSize() const override;
    void Serialize(Buffer::Iterator start) const override;
    uint32_t Deserialize(Buffer::Iterator start) override;
};

} // namespace ns3

#endif /* MT_HEADER_H */
