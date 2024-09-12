#ifndef MT_RX_APP_H
#define MT_RX_APP_H

#include "../helper/mtp-types.h"
#include "ns3/mt-event.h"

namespace ns3 {
  class MTRXAppParser {
    public:
      MTRXAppParser(){}
      ~MTRXAppParser(){}
      virtual MTEvent* request_parser(app_msg_t request)=0;
  };
}

#endif // MT_RX_APP_H