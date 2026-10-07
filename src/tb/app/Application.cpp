#include <tb/app/Application.hpp>

#include <tb/app/mods/LocalDBModule.hpp>
#include <tb/app/mods/LocalSessionModule.hpp>

namespace tb::app
{

bool Application::BaseInit()
{
    PushModule(std::make_shared<tb::app::mods::LocalDBModule>());
    PushModule(std::make_shared<tb::app::mods::LocalSessionModule>());

    return true;
}

} // ns tb::app