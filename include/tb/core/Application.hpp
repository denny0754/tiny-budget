#ifndef TB_CORE_APPLICATION_HPP
#define TB_CORE_APPLICATION_HPP

#include <tb/core/Session.hpp>
#include <tb/events/EventDispatcher.hpp>
#include <tb/ui/Controller.hpp>
#include <tb/events/system/WindowCloseEvent.hpp>

#include <memory>

#include <glfw/glfw3.h>

namespace tb::core
{

class Application
{
public:
    Application();

    void Run();

    ~Application();

protected:
    void Render();

    void Update();

    void OnShutdown(const tb::events::WindowCloseEvent& event);

private:
    GLFWwindow* m_nativeWindow;

    bool m_ready{false};

    std::shared_ptr<tb::core::Session> m_session;
    std::shared_ptr<tb::events::EventDispatcher> m_eventDispatcher;
    std::shared_ptr<tb::ui::Controller> m_uiController;
};

} // ns tb::core

#endif