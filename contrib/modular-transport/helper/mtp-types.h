#ifndef MTP_TYPES_H
#define MTP_TYPES_H

#include "ns3/mt-flow-id.h"     // flow_id
#include "ns3/mt-addr.h"        // addr_t
#include "ns3/mt-flow-map.h"    // flow_map
#include "ns3/mt-queue.h"       // queue_t
#include "ns3/mt-app.h"         // app_msg_t, app_hdr_t
#include "ns3/mt-header.h"      // MTHeader
#include "ns3/packet.h"         // ns3::Packet

namespace ns3 {

  class MTIntermediateOutput {
    public:
      virtual ~MTIntermediateOutput() {};
  };

  typedef MTIntermediateOutput interm_output;

  // event_t
  // typedef MTEvent event_t;

} // namespace ns3

#endif // MTP_TYPES_H