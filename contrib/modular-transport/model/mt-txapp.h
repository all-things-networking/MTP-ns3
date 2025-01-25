#ifndef TX_APP_SCHEDULER_H
#define TX_APP_SCHEDULER_H

#include "ns3/mt-event.h"
#include "ns3/mt-scheduler.h"
#include "ns3/mtp-types.h"

namespace ns3 {
    // creates messages for app to process packets received in transport layer
    //  e.g. after processing RecvEvent's
    class MTTXAppScheduler {
        protected:
            flow_map<queue_set> flowMap;

            // for choosing next event/flow
            flow_map<unsigned int> eventSelector;
            unsigned int flowSelector;

        public:
            MTTXAppScheduler();
            virtual ~MTTXAppScheduler();

            // initializes the scheduler when first instantiated
            virtual void initialize();

            // (deprecated) determine which flow should send the next feedback 
            // virtual flow_id next_feedback();

            // receives outgoing application events and enqueues them into the queue of the event's flow
            // virtual void enqueue_app_event(event_t * e);
            // (NOV 28) should be send_app_event and send directly to the app layer

            // receives outgoing application events and sends them directly to the app layer
            virtual void send_app_event(event_t * e);
    };
}

#endif // TX_APP_SCHEDULER_H