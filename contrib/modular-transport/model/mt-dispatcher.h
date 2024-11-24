#ifndef MT_DISPATCHER_H
#define MT_DISPATCHER_H

#include <vector>
#include <utility> // std::pair
#include <unordered_map>
#include <string>
#include "ns3/mt-event.h"

namespace ns3
{
class MTEvent;
class MTEventProcessor;
class ModularTransport;

// to review: called MTDispatcher but compiler calls it Dispatcher
class MTDispatcher {
    protected:
        ModularTransport * mt;

        // review this: note this is the type that will be returned when getEventMap is called in the compiler
        // std::unordered_map<std::pair<ns3::EventType, ns3::EventSubtype>, std::vector<MTEventProcessor*>> eventMap;
        std::unordered_map<std::string, std::vector<MTEventProcessor*>> eventMap;

    public:
        // to ensure the class is abstract
        virtual ~MTDispatcher() {};

        // map event to processor
        virtual std::vector<MTEventProcessor*> dispatch(MTEvent* e);

        // for compiler
        virtual std::unordered_map<std::string, std::vector<MTEventProcessor*>> getEventMap();
    };
}
#endif
