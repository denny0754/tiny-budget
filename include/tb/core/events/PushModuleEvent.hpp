#ifndef TB_CORE_EVENTS_PUSH_MODULE_EVENT_HPP
#define TB_CORE_EVENTS_PUSH_MODULE_EVENT_HPP

#include <memory>

#include <tb/core/events/BaseEvent.hpp>
#include <tb/core/BaseModule.hpp>

namespace tb::core::events
{

struct PushModuleEvent : public BaseEvent
{
    std::shared_ptr<tb::core::BaseModule> NewModule;

    explicit PushModuleEvent(std::shared_ptr<tb::core::BaseModule> module)
        : NewModule(std::move(module)) {}

    const char* GetName() const override { 
        return "PushModuleEvent"; 
    }
};

} // ns tb::core::events

#endif