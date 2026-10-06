#ifndef TB_CORE_EV_POP_MODULE_EVENT_HPP
#define TB_CORE_EV_POP_MODULE_EVENT_HPP

#include <memory>

#include <tb/core/ev/Event.hpp>
#include <tb/core/mod/Module.hpp>

namespace tb::core::ev
{

struct PopModuleEvent : public tb::core::ev::Event
{
    std::shared_ptr<tb::core::mod::Module> TargetModule;

    explicit PopModuleEvent(std::shared_ptr<tb::core::mod::Module> module)
        : TargetModule(std::move(module)) {}

    const char* GetName() const override { 
        return "PopModuleEvent"; 
    }
};

} // ns tb::core::ev

#endif