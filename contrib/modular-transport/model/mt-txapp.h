#ifndef TX_APP_SCHEDULER_H
#define TX_APP_SCHEDULER_H
#include "ns3/packet.h"
#include "modular-transport.h"
#include "mt-event.h"
#include "mt-scheduler.h"
#include "../helper/mtp-types.h"

namespace ns3 {
    class MTTXAppScheduler {
        stream memory;
        flow_map<queue_set> flowMap;
        MTScheduler * sched;

        // for choosing next event/flow
        flow_map<unsigned int> eventSelector;
        unsigned int flowSelector;

        public:
            MTTXAppScheduler(ModularTransport *mt, MTScheduler * sched);
            virtual ~MTTXAppScheduler();

            // initializes the scheduler when first instantiated
            virtual void initialize();

            // determine which flow should send the next feedback
            virtual void next_feedback();

            // receives outgoing application events and enqueues them into the queue of the event's flow
            virtual void enqueue_app_event(event_t * e);
    };
}

#endif // TX_APP_SCHEDULER_H