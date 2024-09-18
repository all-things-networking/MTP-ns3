#include "ns3/simulator.h"

#include"ns3/mt-event.h"

class MTTimer{
    private:
        int duration;
        ns3::EventId timer;
        ns3::MTEvent* event;
    public:
        void start(ns3::MTEvent* event);
        void stop();
        void restart(int duration);
        void set_duration(int duration);
        bool isActive();
};