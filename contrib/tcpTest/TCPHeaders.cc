#include "TCPHeaders.h"

using namespace ns3;

uint32_t TCPheader::GetSerializedSize()const{
    return 6*32;
}
void TCPheader::Serialize(Buffer::Iterator start)const{
    Buffer::Iterator i = start;
    i.WriteHtonU32(src_port);
    i.WriteHtonU32(dest_port);
    i.WriteHtonU32(seq);
    i.WriteHtonU32(ack_seq);
    i.WriteHtonU32(ack);
    i.WriteHtonU32(window);
}
uint32_t TCPheader::Deserialize(Buffer::Iterator start){
    Buffer::Iterator i = start;
    src_port = i.ReadNtohU32();
    dest_port = i.ReadNtohU32();
    seq = i.ReadNtohU32();
    ack_seq = i.ReadNtohU32();
    ack = i.ReadNtohU32();
    window = i.ReadNtohU32();

    return GetSerializedSize();

}
void TCPheader::Print(std::ostream& os)const{

}
TypeId TCPheader::GetInstanceTypeId()const{

}