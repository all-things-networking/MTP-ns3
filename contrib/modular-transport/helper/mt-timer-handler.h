#include "ns3/modular-transport.h"
#include "ns3/mt-event.h"

class MTTimerHandler
{
private:
    MTTimerHandler(ns3::ModularTransport* mt):mt{mt}{}
    ns3::ModularTransport* mt;
    static MTTimerHandler* instance;
public:
    static MTTimerHandler* getInstance(ns3::ModularTransport* mt = NULL);
    void triggerTimeout(ns3::MTEvent* event);
    ~MTTimerHandler();
};


