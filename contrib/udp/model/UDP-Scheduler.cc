#include "UDP-Scheduler.h"
#include "UDP-Event.h"

bool UDPScheduler::enqueue(UDPEvent * new_event) {
  if (new_event->type == SEND) {
    send_queue.push(dynamic_cast<SendEvent*>(new_event));
    return true;
  }
  if (new_event->type == RECV) {
    add_queue.push(dynamic_cast<AddDataEvent*>(new_event));
    return true;
  }
  if (new_event->type == ERROR) {
    exit(1); // determine proper behaviour in this case
  }
}