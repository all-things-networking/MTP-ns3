#ifndef QUICRXAPP_H
#define QUICRXAPP_H

#include"ns3/mt-rxapp.h"

class QUICRXAppParser: public ns3::MTRXAppParser {
    public:
      int id=0;
      QUICRXAppParser(){}
      ~QUICRXAppParser(){}
      ns3::MTEvent* request_parser(ns3::app_msg_t request);
  };

#endif