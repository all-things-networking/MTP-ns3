#ifndef UDPRXAPP_H
#define UDPRXAPP_H

#include"ns3/mt-rxapp.h"

class UDPRXAppParser: public ns3::MTRXAppParser {
    public:
      UDPRXAppParser(){}
      ~UDPRXAppParser(){}
      ns3::MTEvent* request_parser(ns3::app_msg_t request);
  };

#endif