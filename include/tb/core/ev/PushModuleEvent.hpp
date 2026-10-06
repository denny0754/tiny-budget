#ifndef TB_CORE_EV_PUSH_MODULE_EVENT_HPP
#define TB_CORE_EV_PUSH_MODULE_EVENT_HPP

#include <memory>

#include <tb/core/ev/Event.hpp>
#include <tb/core/mod/Module.hpp>

namespace tb::core::ev
{

struct PushModuleEvent : public tb::core::ev::Event
{
    std::shared_ptr<tb::core::mod::Module> NewModule;

    explicit PushModuleEvent(std::shared_ptr<tb::core::mod::Module> module)
        : NewModule(std::move(module)) {}

    const char* GetName() const override { 
        return "PushModuleEvent"; 
    }
};

} // ns tb::core::ev

#endif