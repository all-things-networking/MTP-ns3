#ifndef MT_QUEUE_H
#define MT_QUEUE_H

#include <type_traits> // static_assert
#include <deque>
class MTEvent;

namespace ns3 {
  template<typename event>
  class queue_t {
    // static_assert to ensure that queue event type is derived from MTEvent

    std::deque<event> eventQueue;
    int upper_limit;
    int lower_limit;
    bool (*drop_policy) (event);
    bool paused;

    public:
      queue_t();
      queue_t(int lower_limit, int upper_limit, bool (*drop_policy) (event));
      ~queue_t();
      bool pause();
      bool unpause();
      void active();
      void push(event e);
      bool empty();
      event pop();
  };

}

#include "mt-queue.cc"

#endif