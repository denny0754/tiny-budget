#ifndef TB_CORE_INTF_MODULE_HPP
#define TB_CORE_INTF_MODULE_HPP

#include <memory>
#include <functional>
#include <vector>
#include <memory>

#include <tb/core/AppContext.hpp>

namespace tb::core { class Application; }

namespace tb::core
{

class BaseModule : std::enable_shared_from_this<BaseModule>
{
private:
    friend class Application;

    void BindContext(std::shared_ptr<tb::core::AppContext> context)
    {
        m_appCtx = context;
    }

    std::vector<std::function<void()>> m_unsubscribers;

protected:
    template<typename T>
    void SubscribeEvent(EventBus::EventListenerRef<T> listener)
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

    ~BaseModule()
    {
        for(auto& unsubscriber_handler : m_unsubscribers)
        {
            unsubscriber_handler();
        }
        m_unsubscribers.clear();
    }

protected:
    std::shared_ptr<tb::core::AppContext> m_appCtx;
};

} // ns tb::core

#endif