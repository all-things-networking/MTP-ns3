#include"QUICRXApp.h"
#include"QUICEvents.h"

using namespace ns3;

MTEvent* QUICRXAppParser::request_parser(ns3::app_msg_t request){
    ADD_DATA* ev = new ADD_DATA(10,id);
    ev->server_side = 1;
    ev->address = '0';
    ev->data_length = 1000;
    return ev;
}