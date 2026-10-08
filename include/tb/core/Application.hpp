#ifndef TB_CORE_APPLICATION_HPP
#define TB_CORE_APPLICATION_HPP

#include <memory>

#include <tb/core/BaseModule.hpp>
#include <tb/core/events/PopModuleEvent.hpp>
#include <tb/core/events/PushModuleEvent.hpp>
#include <tb/core/events/WindowCloseEvent.hpp>
#include <tb/core/AppContext.hpp>

#include <glfw/glfw3.h>

namespace tb::core
{

class Application
{
public:
    Application() = default;

    void Init();

    void Run();

    void Shutdown();

    void PushModule(std::shared_ptr<BaseModule> module);

    std::shared_ptr<tb::core::AppContext> GetContext();

    ~Application();
private:
    void OnPushModule(const events::PushModuleEvent& event);

    void OnPopModule(const events::PopModuleEvent& event);

    void OnShutdown(const events::WindowCloseEvent& event);

private:
    std::shared_ptr<tb::core::AppContext> m_context;

    GLFWwindow* m_nativeWindow;

    bool m_ready{false};

    std::vector<std::shared_ptr<BaseModule>> m_modules;
    std::vector<std::shared_ptr<BaseModule>> m_pendingModules;
    std::vector<std::shared_ptr<BaseModule>> m_pendingRemovalModules;
};

} // ns tb::core

#endif