#ifndef TX_APP_SCHEDULER_H
#define TX_APP_SCHEDULER_H
#include "ns3/packet.h"
#include "ns3/modular-transport.h"
#include "ns3/mt-event.h"
#include "ns3/mt-scheduler.h"
#include "ns3/mtp-types.h"

namespace ns3 {
    class MTTXAppScheduler {
        protected:
            // stream memory;
            flow_map<queue_set> flowMap;

            // for choosing next event/flow
            flow_map<unsigned int> eventSelector;
            unsigned int flowSelector;

        public:
            MTTXAppScheduler(ModularTransport *mt) : flowMap(queue_set()) {
                eventSelector = flow_map<unsigned int>(0);
                flowSelector = 0;
            }
            virtual ~MTTXAppScheduler();

            // initializes the scheduler when first instantiated
            virtual void initialize();

            // determine which flow should send the next feedback
            virtual flow_id next_feedback();

            // receives outgoing application events and enqueues them into the queue of the event's flow
            virtual void enqueue_app_event(event_t * e);
    };
}

#endif // TX_APP_SCHEDULER_H