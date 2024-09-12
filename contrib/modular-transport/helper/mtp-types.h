#ifndef MTP_TYPES_H
#define MTP_TYPES_H

#include "mt-flow-id.h"     // flow_id
#include "mt-flow-map.h"    // flow_map
//#include "mt-queue.h"       // queue_t
#include "mt-app.h"         // app_msg_t, app_hdr_t
//#include "mt-stream.h"      // stream
#include "mt-addr.h"        // addr_t
//#include "mt-packet.h"      // pkt_t

namespace ns3 {

  class IntermediateOutput {
    // to ensure the class is abstract/not instantiable
    virtual ~IntermediateOutput() = 0;
  };

  // should this happen here? or only once a concrete subclass is implemented?
  typedef IntermediateOutput interm_output;

  // event_t
  //typedef MTEvent event_t;

} // namespace ns3

#endif // MTP_TYPES_H