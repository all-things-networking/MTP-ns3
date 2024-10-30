#ifndef UDP_TX_APP_H
#define UDP_TX_APP_H

#include "ns3/mt-txapp.h"

namespace ns3 {
    class UDPTXAppScheduler : public MTTXAppScheduler {
        UDPTXAppScheduler(ModularTransport *mt, int lower_limit, int upper_limit, bool (*drop_policy)(MTEvent *)) 
        : MTTXAppScheduler(mt, lower_limit, upper_limit, drop_policy) {}

        void initialize() override {}
        flow_id next_feedback() override {
            flow_id id;
            do {
                id = this->next_flow();
            } while (flowMap[id].is_empty());
        }
    };  
}

#endif