#ifndef TCPRXAPP_H
#define TCPRXAPP_H

#include"ns3/mt-rxapp.h"

class TCPRXAppParser: public ns3::MTRXAppParser {
    public:
      int id=0;
      TCPRXAppParser(){}
      ~TCPRXAppParser(){}
      ns3::MTEvent* request_parser(ns3::app_msg_t request);
  };

#endif