#include "QUICHeaders.h"

using namespace ns3;

uint32_t QuicHeader::GetSerializedSize()const{
    return 32;
}
void QuicHeader::Serialize(Buffer::Iterator start)const{
    Buffer::Iterator i = start;
    i.WriteHtonU32(pkt_id);
}
uint32_t QuicHeader::Deserialize(Buffer::Iterator start){
    Buffer::Iterator i = start;
    pkt_id = i.ReadNtohU32();

    return GetSerializedSize();

}
void QuicHeader::Print(std::ostream& os)const{

}
TypeId QuicHeader::GetInstanceTypeId()const{

}