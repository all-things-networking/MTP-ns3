#ifndef MT_RX_APP_H
#define MT_RX_APP_H

#include "../helper/mtp-types.h"
#include "mt-scheduler.h"

namespace ns3 {
  // responsible for creating events based on packets received from application layer
  class MTRXAppParser {
    public:
      MTRXAppParser() {};
      virtual ~MTRXAppParser() {};

      // not sure this needs to be a field
      app_hdr_t header;
      
      virtual event_t * request_parser(app_msg_t request) = 0;
  };
}

#endif // MT_RX_APP_H