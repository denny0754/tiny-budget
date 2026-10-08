#include <tb/app/Application.hpp>

#include <tb/app/modules/SessionSelector.hpp>

namespace tb::app
{

bool Application::BaseInit()
{
    PushModule(std::make_shared<tb::app::mods::SessionSelector>());

    return true;
}

} // ns tb::app