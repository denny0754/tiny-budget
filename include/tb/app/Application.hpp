#ifndef TB_APP_APPLICATION_HPP
#define TB_APP_APPLICATION_HPP

#include <tb/core/Application.hpp>

namespace tb::app
{

class Application : public tb::core::Application
{
private:
    bool BaseInit() override;
};

} // ns tb::app

#endif