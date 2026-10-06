#ifndef TB_CORE_EV_EVENT_BUS_HPP
#define TB_CORE_EV_EVENT_BUS_HPP

#include <functional>
#include <typeindex>
#include <vector>
#include <algorithm>

#include <tb/core/ev/Event.hpp>

namespace tb::core::ev
{

class EventBus
{
public:
    using SubscriptionId = uint32_t;

    template<typename T>
    using EventListenerRef = std::function<void(const T&)>;

    template<typename T>
    SubscriptionId Subscribe(EventListenerRef<T> listener, int priority = 0)
    {
        auto typeIndex = std::type_index(typeid(T));
        SubscriptionId id = ++m_nextId;
        
        auto& vector = m_listeners[typeIndex];
        
        vector.push_back({
            id,
            priority,
            [listener](const Event& e) {
                listener(static_cast<const T&>(e));
            }
        });
        
        std::stable_sort(vector.begin(), vector.end(), [](const Handler& a, const Handler& b) {
            return a.priority > b.priority;
        });
        
        return id;
    }

    template<typename T>
    void Unsubscribe(SubscriptionId id)
    {
        auto typeIndex = std::type_index(typeid(T));
        auto it = m_listeners.find(typeIndex);
        
        if (it != m_listeners.end()) {
            auto& vector = it->second;
            
            // Erase-remove idiom to safely filter out the matching ID
            vector.erase(
                std::remove_if(vector.begin(), vector.end(), 
                    [id](const Handler& h) { return h.id == id; }),
                vector.end()
            );
        }
    }

    // Pushes an event to all subscribed listeners
    template<typename T>
    void Push(const T& event)
    {
        auto typeIndex = std::type_index(typeid(T));
        auto it = m_listeners.find(typeIndex);
        
        if (it != m_listeners.end()) {
            for (auto& handler : it->second) {
                // If a higher-priority listener consumed this event, stop propagating
                if (event.Handled) {
                    break; 
                }
                
                handler.callback(event);
            }
        }
    }

private:
    struct EventHandlerData
    {
        SubscriptionId id;
        EventListenerRef<Event> handler;
        int priority;        
    };

    std::unordered_map<std::type_index, std::vector<EventHandlerData>> m_listeners;

    SubscriptionId m_nextSubId = 1;
};

} // ns tb::core::ev

#define TB_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#endif