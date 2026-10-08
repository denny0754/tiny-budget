#ifndef TB_APP_MODULES_LOCAL_SESSION_HPP
#define TB_APP_MODULES_LOCAL_SESSION_HPP

#include <tb/app/modules/Session.hpp>

namespace tb::app::modules
{

class LocalSession : public tb::app::modules::Session
{
public:
    void OnInit();

    void OnUpdate(double delta_time = .0f);

    void OnRender();

    void OnShutdown();
};

} // ns tb::app::modules

#endif