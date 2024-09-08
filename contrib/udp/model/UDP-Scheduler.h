#ifndef UDP_SCHEDULER_H
#define UDP_SCHEDULER_H

#include "UDP-Event.h"
#include "ns3/mt-scheduler.h"

#include <queue>
#include <vector>

namespace ns3
{
class MTScheduler;
class MTEvent;
class UDPEvent;
class SendEvent;
class ReceiveEvent;
class MTHeader;

// ==========================================================================================
// QUESTIONS/TODOS:
//   - What are flows and how are they incorporated?
//     - represents connections
//     - scheduler chooses between flows (skip) and then chooses between events from that flow
//   - Slightly lost as to what functionality we need to implement to ensure compatibility with
//     MTP specification i.e. Listing 8
//     - which aspects of this functionality will be implemented in the MTP UDP example vs. in here?
//     - best way to reimplement the below in terms of TX and RX queues/scheduling
//   - in enqueue function: implement logic for dropping packets once we determine what max queue size is
//   - determine which portions of the scheduler will be implemented in the MTP UDP example vs. which
//     will be implemented here
// ==========================================================================================

class UDPScheduler : public MTScheduler
{
  public:
    std::queue<SendEvent*> sendQueue;
    std::queue<ReceiveEvent*> receiveQueue;

    UDPScheduler();
    // MTEvent* GetNextEvent();        // event_t next_event(queue_t send_queue, queue_t ack_queue, queue_t
                                       // add_queue)
    bool enqueue(UDPEvent* new_event); // bool enqueue(queue_t ack_queue, event_t new_event)
    int send_drop()         { return sendQueue.size() - 1;       };  // int add_drop(queue_t add_queue, event_t new_event)
    int receive_drop()      { return receiveQueue.size() - 1;    };
    bool is_send_empty()    { return this->sendQueue.empty();    };
    bool is_receive_empty() { return this->receiveQueue.empty(); };
};
} // namespace ns3

#endif