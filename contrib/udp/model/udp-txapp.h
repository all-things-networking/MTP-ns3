#ifndef UDP_TX_APP_H
#define UDP_TX_APP_H

#include "ns3/mt-txapp.h"

namespace ns3 {
    class UDPTXAppScheduler : public MTTXAppScheduler {
        void initialize() override {}

        // flow_id next_feedback() override {
        //     flow_id id;
        //     do {
        //         id = this->next_flow();
        //     } while (flowMap[id].is_empty());
        //     return id;
        // }

        // flow_id next_feedback() override {
        //     flow_id id;
        //     auto it = flowMap.begin();
        //     do {
        //         it = flowMap.next(it);
        //     } while (flowMap[it->first].is_empty());
        //     return it->first;
        // }

        void send_app_event(event_t * e) override {
            // send to app layer
        }

        public:
            UDPTXAppScheduler() {}
    };  
}

#endif