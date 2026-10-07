#ifndef TB_APP_MODS_API_PROVIDER_HPP
#define TB_APP_MODS_API_PROVIDER_HPP

#include <tb/core/mod/Module.hpp>
#include <tb/core/ev/Event.hpp>

namespace tb::app::mods
{

class APIProvider : public tb::core::mod::Module
{
public:
    virtual void OnInit() = 0;

    virtual void OnUpdate(double delta_time = .0f) = 0;

    virtual void OnRender() = 0;

    virtual void OnShutdown() = 0;
};

} // ns tb::app::mods
#endif