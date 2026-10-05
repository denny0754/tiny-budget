#ifndef TB_CORE_INTF_MODULE_HPP
#define TB_CORE_INTF_MODULE_HPP

#include <memory>
#include <functional>
#include <vector>

#include <tb/core/ev/EventBus.hpp>

namespace tb::core { class Application; }

namespace tb::core::mod
{

class Module
{
private:
    friend class Application;

    void BindEventBus(std::shared_ptr<core::ev::EventBus> event_bus);

    std::vector<std::function<void()>> m_unsubscribers;

protected:
    template<typename T>
    void SubscribeEvent(ev::EventBus::EventListenerRef<T> listener)
    {
        auto id = m_eventBus->Subscribe<T>(listener);

        m_unsubscribers.push_back([this, id](){
            if(m_eventBus)
            {
                m_eventBus->Unsubscribe<T>(id);
            }
        });
    }

public:
    virtual void OnInit() = 0;

    virtual void OnUpdate(double delta_time = .0f);

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
    std::shared_ptr<core::ev::EventBus> m_eventBus;
};

} // ns tb::core::mod

#endif