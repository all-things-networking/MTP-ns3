class IPheader : public Header
{
	public:
	bool ecn;
	int identification;
	int flags;
	int ttl;
	int protocol;
	int hdrChecksum;
	uint16 tot_len;
	char src_addr;
	char dst_addr;
	IPheader();
	// to override the virtual functions
	int_t GetSerializedSize() const;
	void Serialize(Buffer::Iterator start) const;
	int_t Deserialize(Buffer::Iterator start);
	void Print(std::ostream& os) const;
	TypeId GetInstanceTypeId() const;
};
class TCPheader : public Header
{
	public:
	int src_port;
	int dest_port;
	int seq;
	int ack_seq;
	int ack;
	int window;
	TCPheader();
	// to override the virtual functions
	int_t GetSerializedSize() const;
	void Serialize(Buffer::Iterator start) const;
	int_t Deserialize(Buffer::Iterator start);
	void Print(std::ostream& os) const;
	TypeId GetInstanceTypeId() const;
};
