#ifndef TB_APP_MODULES_SESSION_MODULE_HPP
#define TB_APP_MODULES_SESSION_MODULE_HPP

#include <tb/core/mod/Module.hpp>
#include <tb/app/api/APIProvider.hpp>

namespace tb::app::modules
{

class Session : public tb::core::mod::Module
{
public:
    virtual void OnInit();

    virtual void OnUpdate(double delta_time = .0f);

    virtual void OnRender();

    virtual void OnShutdown();

protected:
    std::shared_ptr<tb::app::common::APIProvider> m_apiProvider;
};

} // ns tb::app::modules

#endif