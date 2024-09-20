#ifndef QUICHEADERS
#define QUICHEADERS

#include "ns3/mt-header.h"
#include "trailer.h"

class QuicHeader : public ns3::Header
{
	public:
	int pkt_id;
	QuicHeader(){}
	// to override the virtual functions
	uint32_t GetSerializedSize() const;
	void Serialize(ns3::Buffer::Iterator start) const;
	uint32_t Deserialize(ns3::Buffer::Iterator start);
	void Print(std::ostream& os) const;
	ns3::TypeId GetInstanceTypeId() const;
};

class QuicBody : public ns3::Trailer
{
	public:
	int pkt_id;
	QuicHeader(){}
	// to override the virtual functions
	uint32_t GetSerializedSize() const;
	void Serialize(ns3::Buffer::Iterator start) const;
	uint32_t Deserialize(ns3::Buffer::Iterator start);
	void Print(std::ostream& os) const;
	ns3::TypeId GetInstanceTypeId() const;
};

#endif