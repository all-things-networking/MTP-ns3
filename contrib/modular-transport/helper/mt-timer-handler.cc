#include "mt-timer-handler.h"

MTTimerHandler* MTTimerHandler::instance = NULL;

MTTimerHandler* MTTimerHandler::getInstance(ns3::ModularTransport* mt){
    if(!instance)
        instance = new MTTimerHandler(mt);
    return instance;
}

void MTTimerHandler::triggerTimeout(ns3::MTEvent* event){
    mt->HandleTimeout(event);
}

 MTTimerHandler::~MTTimerHandler(){
 }