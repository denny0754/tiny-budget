#ifndef TB_CORE_EVENTS_POP_MODULE_EVENT_HPP
#define TB_CORE_EVENTS_POP_MODULE_EVENT_HPP

#include <memory>

#include <tb/core/events/BaseEvent.hpp>
#include <tb/core/BaseModule.hpp>

namespace tb::core::events
{

struct PopModuleEvent : public BaseEvent
{
    std::shared_ptr<tb::core::BaseModule> TargetModule;

    explicit PopModuleEvent(std::shared_ptr<tb::core::BaseModule> module)
        : TargetModule(std::move(module)) {}

    const char* GetName() const override { 
        return "PopModuleEvent"; 
    }
};

} // ns tb::core::events

#endif