#include "ns3/mt-header.h"

class TCPheader : public ns3::MTHeader
{
	public:
	int src_port;
	int dest_port;
	int seq;
	int ack_seq;
	int ack;
	int window;
	uint32_t GetSerializedSize() const;
	void Serialize(ns3::Buffer::Iterator start) const;
	uint32_t Deserialize(ns3::Buffer::Iterator start);
	void Print(std::ostream& os) const;
	ns3::TypeId GetInstanceTypeId() const;
};