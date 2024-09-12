#include"UDPRXApp.h"
#include"UDPEvents.h"

using namespace ns3;

MTEvent* UDPRXAppParser::request_parser(ns3::app_msg_t request){
    SEND_EVENT* ev = new SEND_EVENT(10,1);
    ev->addr = 0;
    ev->length = 32;
    std::cout<<"sending event"<<std::endl;
    return ev;
}