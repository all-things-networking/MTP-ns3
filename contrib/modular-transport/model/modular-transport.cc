/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "modular-transport.h"

#include "ns3/ipv4-l3-protocol.h"
#include "ns3/node.h"
#include "mt-eventprocessor.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("ModularTransport");

NS_OBJECT_ENSURE_REGISTERED(ModularTransport);

TypeId
ModularTransport::GetTypeId()
{
    static TypeId tid = TypeId("ns3::ModularTransport")
                            .SetParent<IpL4Protocol>()
                            .SetGroupName("ModularTransport")
                            .AddConstructor<ModularTransport>();
    return tid;
}

ModularTransport::ModularTransport()
{
    this->scheduler = new MTScheduler();
    NS_LOG_FUNCTION(this);
}

ModularTransport::~ModularTransport()
{
    NS_LOG_FUNCTION(this);
}

void ModularTransport::ReceiveAppMessage(
                             const Ipv4Address& saddr,
                             const Ipv4Address& daddr){
    MTEvent* ev = rxapp->request_parser(ns3::app_msg_t());
    std::cout <<"created the send event for flow "<< ev->flowId << std::endl;
    scheduler->enqueue_event(ev->flowId,ev);
    Mainloop();
}

void ModularTransport::ReceiveNetPacket(
                             const Ipv4Address& saddr,
                             const Ipv4Address& daddr/*,
                             MTContext* StartContext*/){

    Mainloop();
}

void ModularTransport::Start(
                             const Ipv4Address& saddr,
                             const Ipv4Address& daddr/*,
                             MTContext* StartContext*/){

    Mainloop();
}
void ModularTransport::Mainloop(){
    // This is the main loop of the transport layer
       // that calls the different components of our model
       // to process events
    while (!this->scheduler->is_empty()){
        MTEvent* e = this->scheduler->get_next_event();
        std::cout <<"Main Loop: Currently Processing Event "<< typeid(*e).name() << std::endl;
        std::vector<MTEventProcessor*> ep= this->dispatcher->dispatch(e);
        //std::cout <<"got event procs : "<< ep.size() << std::endl;
        MTContext* ctx = this->ctx_table[e->flowId];
        if(!ctx){
            std::cout <<"Main Loop: Creating New Context For Flow Id "<<e->flowId<< std::endl;
            ctx = InitContext(e->flowId);
        }

         std::vector<MTEvent*> newEvents;

        EventProcessorOutput* epout = new EventProcessorOutput{newEvents, ctx, interm_output};

        //  // run through all processors
         for (auto processor : ep) 
         {
            std::cout <<"MainLoop: Entering Eventproc: "<<typeid(*processor).name()<< std::endl;
            epout = processor->process(e, epout);
         }

         for (auto newEvent : epout->events)
         {
            switch (newEvent->subtype){
                case PROG_EVENT:
                    scheduler->enqueue_event(e->flowId,newEvent);
                    break;
                case NET_EVENT:
                    std::cout <<"sending out a packet "<< std::endl;
                    break;
                default:
                    std::cout <<"event type unsupported "<< std::endl;
                    break;
            }      
         }
         std::cout <<"_______________________________________________"<< std::endl;

    }
     std::cout <<"_______________________________________________"<< std::endl;
}
void
ModularTransport::DoDispose()
{
    NS_LOG_FUNCTION(this);
    m_node = nullptr;
    m_downTarget.Nullify();
    m_downTarget6.Nullify();
    IpL4Protocol::DoDispose();
}

void
ModularTransport::SetNode(Ptr<Node> node)
{
    NS_LOG_FUNCTION(this);
    m_node = node;
}

void
ModularTransport::NotifyNewAggregate()
{   
    NS_LOG_FUNCTION(this);
    Ptr<Node> node = this->GetObject<Node>();
    Ptr<Ipv4> ipv4 = this->GetObject<Ipv4>();
    
    if (!m_node)
    {   
        if (node && ipv4)
        {   
            this->SetNode(node);
        }
    }
    
    // We set the down target to the IPv4 send function.  
    if (ipv4 && m_downTarget.IsNull())
    {
        ipv4->Insert(this);
        this->SetDownTarget(MakeCallback(&Ipv4::Send, ipv4));
    }
    IpL4Protocol::NotifyNewAggregate();
}

//void
// ModularTransport::SendPacket(Ptr<Packet> packet,
//                              const MTHeader& outgoing,
//                              const Ipv4Address& saddr,
//                              const Ipv4Address& daddr) const
// {
//     NS_LOG_FUNCTION(this << packet << saddr << daddr);
//     // TODO:Use NS_LOG_LOGIC to record information about the segment/packet being sent out.

//     MTHeader outgoingHeader = outgoing;
   
//     packet->AddHeader(outgoingHeader);

//     Ptr<Ipv4> ipv4 = m_node->GetObject<Ipv4>();
//     if (ipv4)
//     {
//         Ipv4Header header;
//         header.SetSource(saddr);
//         header.SetDestination(daddr);
//         header.SetProtocol(PROT_NUMBER);
//         Socket::SocketErrno errno_;
//         Ptr<Ipv4Route> route;
//         if (ipv4->GetRoutingProtocol())
//         {
//             route = ipv4->GetRoutingProtocol()->RouteOutput(packet, header, nullptr, errno_);
//         }
//         else
//         {
//             NS_LOG_ERROR("No IPV4 Routing Protocol");
//             route = nullptr;
//         }
//         m_downTarget(packet, saddr, daddr, PROT_NUMBER, route);
//     }
//     else
//     {
//         NS_FATAL_ERROR("Trying to use ModularTransport on a node without an Ipv4 interface");
//     }
// }

enum IpL4Protocol::RxStatus
ModularTransport::Receive(Ptr<Packet> packet,
                          const Ipv4Header& incomingIpHeader,
                          Ptr<Ipv4Interface> incomingInterface)
{
    NS_LOG_FUNCTION(this << packet << incomingIpHeader << incomingInterface);
    NS_LOG_UNCOND("Received packet in ModularTransport");
    return IpL4Protocol::RX_OK;
}

void
ModularTransport::SetDownTarget(IpL4Protocol::DownTargetCallback callback)
{
    m_downTarget = callback;
}

int
ModularTransport::GetProtocolNumber() const
{
    return PROT_NUMBER;
}

IpL4Protocol::DownTargetCallback
ModularTransport::GetDownTarget() const
{
    return m_downTarget;
}

/* ****** ICMP ******** */
void
ModularTransport::ReceiveIcmp(Ipv4Address icmpSource,
                              uint8_t icmpTtl,
                              uint8_t icmpType,
                              uint8_t icmpCode,
                              uint32_t icmpInfo,
                              Ipv4Address payloadSource,
                              Ipv4Address payloadDestination,
                              const uint8_t payload[8])
{
    NS_LOG_UNCOND("ModularTransport: ICMP over IPv4 is not supported");
}

void
ModularTransport::ReceiveIcmp(Ipv6Address icmpSource,
                              uint8_t icmpTtl,
                              uint8_t icmpType,
                              uint8_t icmpCode,
                              uint32_t icmpInfo,
                              Ipv6Address payloadSource,
                              Ipv6Address payloadDestination,
                              const uint8_t payload[8])
{
    NS_LOG_UNCOND("ModularTransport: ICMP over IPv6 is not supported");
}

/* ********** IPv6-related functions ************ */
enum IpL4Protocol::RxStatus
ModularTransport::Receive(Ptr<Packet> packet,
                          const Ipv6Header& incomingIpHeader,
                          Ptr<Ipv6Interface> interface)
{
    NS_LOG_UNCOND("ModularTransport: IPv6 Receive not supported");
    return IpL4Protocol::RX_ENDPOINT_UNREACH;
}

void
ModularTransport::SetDownTarget6(IpL4Protocol::DownTargetCallback6 callback)
{
    m_downTarget6 = callback;
}

IpL4Protocol::DownTargetCallback6
ModularTransport::GetDownTarget6() const
{
    return m_downTarget6;
}

} // ns3 namespace
