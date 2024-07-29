#ifndef UDP_HEADER_H
#define UDP_HEADER_H
namespace ns3{
//#Modular transport TCP header
class UDPHeader {
    public:
        int seqnum; //32 bits
        int acknum; // 32 bits
        int DOffset; //4 bits
        int Reserved; //4 bits
        int* ControlBits[6]; //1 bit each
        int Window; //16 bits
        int CheckSum; //16 bits
        int UrgentPointer; // 16 bits
        int* Options; // (DOFFset - 5 ) *32
        char* data;
        UDPHeader();
        ~UDPHeader();
        int GenPseudoHeader();
        int ComputeCheckSum();
        void OpsBeforeSend(); // Compute Hash, call by processor before send?
        void OpsAfterRecieved(); //Just produce event, leave verify hash to processor?

};
}
#endif /* UDP_HEADER_H */
