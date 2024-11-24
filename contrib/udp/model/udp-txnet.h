#ifndef UDP_TX_NET_H
#define UDP_TX_NET_H

#include "ns3/mt-txnet.h"
#include "ns3/udp-event.h"

namespace ns3 {
    class UDPTXNetScheduler : public MTTXNetScheduler {
        public:
            // note that the txQueues flow_map could be just a flowMap of PktEvent* queues
            //  instead of event_t *

            UDPTXNetScheduler() {}
            ~UDPTXNetScheduler() override {}

            virtual pkt_t get_next_packet(MTEvent * e, flow_id id) override {
                txQueues[e->flowId].push(e);
                PktEvent * poppedEvent = (PktEvent *) txQueues[id].pop();

                // poppedEvent->header, poppedEvent->payload, poppedEvent->src_addr, poppedEvent->dest_addr
                pkt_t toReturn = pkt_t();

                delete poppedEvent;
                return toReturn;
            }
    };
}

#endif 