#ifndef TB_CORE_APPLICATION_HPP
#define TB_CORE_APPLICATION_HPP

#include <memory>

#include <tb/core/ev/EventBus.hpp>
#include <tb/core/mod/Module.hpp>
#include <tb/core/ev/PopModuleEvent.hpp>
#include <tb/core/ev/PushModuleEvent.hpp>
#include <tb/core/ev/WindowCloseEvent.hpp>

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

    void PushModule(std::shared_ptr<mod::Module> module);

    std::shared_ptr<ev::EventBus> GetEventBus();

    ~Application();
private:
    void OnPushModule(const ev::PushModuleEvent& event);

    void OnPopModule(const ev::PopModuleEvent& event);

    void OnShutdown(const ev::WindowCloseEvent& event);

private:
    std::shared_ptr<ev::EventBus> m_eventBus;

    GLFWwindow* m_nativeWindow;

    bool m_ready{false};

    std::vector<std::shared_ptr<mod::Module>> m_modules;
    std::vector<std::shared_ptr<mod::Module>> m_pendingModules;
    std::vector<std::shared_ptr<mod::Module>> m_pendingRemovalModules;
};

} // ns tb::core

#endif