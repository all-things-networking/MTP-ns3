#ifndef MT_EVENTPROCESSOR_H
#define MT_EVENTPROCESSOR_H

#include <vector>
#include <utility> // std::pair
#include "mt-event.h"

namespace ns3
{
class MTEvent;
class MTContext;
class Packet;

// child class must initialize intermOutput field using its own subclass of MTIntermediateOutput
struct EventProcessorOutput {
    std::vector<MTEvent *> events;
    MTContext* ctx;
    MTIntermediateOutput* intermOutput;
    std::vector<Packet> packets;
    // TODO: Add tx_module

    // public:
    //     EventProcessorOutput(std::vector<MTEvent*> newEvents, MTContext* ctx) : events(events), ctx(ctx) {}
    //     EventProcessorOutput(std::vector<MTEvent*> newEvents, MTContext* ctx, MTIntermediateOutput* intermOutput) : ctx(ctx), events(events), intermOutput(intermOutput) {}
};
 
/**
 * \brief The base class for event processor. This is virtual class.
 */
class MTEventProcessor
{
public:
    MTEventProcessor() {}
    virtual ~MTEventProcessor() {}

    /**
     * \brief Process the event and return the processed results.
     * \param e The input event to be processed.
     * \param c The context of the Mt connection.
     * \return The modified context and new generated event if exits.
     */
    virtual EventProcessorOutput* process(MTEvent* e, EventProcessorOutput* epOut) = 0;

    // DEPRECATED
    /**
     * \brief Check if the input event is valid event type for the processor.
     * \param e The input event to be processed.
     * \return True if input event type matches the processor type, false otherwise.
     */
    // virtual bool isValidEvent(MTEvent* e) = 0;
};

} // namespace ns3

#endif