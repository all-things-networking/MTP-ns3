#include"TCPRXApp.h"
#include"TCPEvents.h"

using namespace ns3;

MTEvent* TCPRXAppParser::request_parser(ns3::app_msg_t request){
    SEND* ev = new SEND(10,id);
    ev->data_size = 1000000;
    return ev;
}