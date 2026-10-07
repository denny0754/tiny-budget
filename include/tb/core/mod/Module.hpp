#ifndef TB_CORE_INTF_MODULE_HPP
#define TB_CORE_INTF_MODULE_HPP

#include <memory>
#include <functional>
#include <vector>
#include <memory>

#include <tb/core/Context.hpp>

namespace tb::core { class Application; }

namespace tb::core::mod
{

class Module : std::enable_shared_from_this<Module>
{
private:
    friend class Application;

    void BindContext(std::shared_ptr<tb::core::Context> context)
    {
        m_context = context;
    }

    std::vector<std::function<void()>> m_unsubscribers;

protected:
    template<typename T>
    void SubscribeEvent(ev::EventBus::EventListenerRef<T> listener)
    {
        auto id = m_context->eventBus->Subscribe<T>(listener);

        m_unsubscribers.push_back([this, id](){
            if(m_context->eventBus)
            {
                m_context->eventBus->Unsubscribe<T>(id);
            }
        });
    }

public:
    virtual void OnInit() = 0;

    virtual void OnUpdate(double delta_time = .0f) = 0;

    virtual void OnRender() = 0;

    virtual void OnShutdown() = 0;

    ~Module()
    {
        for(auto& unsubscriber_handler : m_unsubscribers)
        {
            unsubscriber_handler();
        }
        m_unsubscribers.clear();
    }

protected:
    std::shared_ptr<tb::core::Context> m_context;
};

} // ns tb::core::mod

#endif