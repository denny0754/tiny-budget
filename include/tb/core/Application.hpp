#ifndef TB_CORE_APPLICATION_HPP
#define TB_CORE_APPLICATION_HPP

#include <memory>

#include <tb/core/ev/EventBus.hpp>

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

    std::shared_ptr<ev::EventBus> GetEventBus();

    ~Application();

private:
    std::shared_ptr<ev::EventBus> m_eventBus;

    GLFWwindow* m_nativeWindow;

    bool m_ready{false};
};

} // ns tb::core

#endif