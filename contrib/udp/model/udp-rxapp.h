#ifndef UDP_RXAPP_H
#define UDP_RXAPP_H

#include "ns3/mt-rxapp.h"
#include "ns3/udp-event.h"
#include "ns3/udp-context.h"
#include <chrono>

namespace ns3 {
    class UDPRXAppParser : public MTRXAppParser {
        UDPContext * ctx;
        public:
            UDPRXAppParser() {};
            virtual ~UDPRXAppParser() {};
            
            virtual event_t * request_parser(app_msg_t request) {
                // remark: in spec, request_parser is meant to extract values from the
                //  request to the RXAppParser-defined app_hdr class
                //  but here, request goes in the message and not the header

                auto now = std::chrono::system_clock::now();
                long timestamp = std::chrono::system_clock::to_time_t(now);
                return new SendEvent(timestamp, request.flow_id);
            }
    };
}

#endif