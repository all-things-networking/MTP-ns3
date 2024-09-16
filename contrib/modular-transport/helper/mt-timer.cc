#include"ns3/simulator.h"
#include"mt-timer.h"
#include"ns3/modular-transport.h"
#include"ns3/mt-timer-handler.h"

using namespace ns3;

void MTTimer::start(MTEvent* event){
    if(isActive()){
        stop();
    }
    std::cout<<"Timer: Starting With Duration "<<duration<<std::endl;
    this->event = *event;
    this->timer = Simulator::Schedule (Seconds(duration),
                       &MTTimerHandler::triggerTimeout,
                       MTTimerHandler::getInstance(), event);
}

void MTTimer::stop(){
    Simulator::Cancel (timer);
}

void MTTimer::restart(int duration){
    this->duration = duration;
    if(isActive()){
        stop();
    }
    start(new MTEvent(event));//TODO: Fix the problem with multiple timer starts/restarts for the same timer.
}

void MTTimer::set_duration(int duration){
    this->duration = duration;
}

bool MTTimer::isActive(){
    return !Simulator::IsExpired(timer);
}