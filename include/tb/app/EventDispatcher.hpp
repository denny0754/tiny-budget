#ifndef TB_APP_EVENT_DISPATCHER_HPP
#define TB_APP_EVENT_DISPATCHER_HPP

#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <algorithm>
#include <cstdint>

// Includes UserEvent (the base event class)
#include <tb/app/events/BaseUserEvent.hpp>

namespace tb::app {

class EventDispatcher
{
public:
    using SubscriptionId = std::uint32_t;

    template<typename T>
    using EventListenerRef = std::function<void(const T&)>;

    template<typename T>
    SubscriptionId Subscribe(EventListenerRef<T> listener, int priority = 0)
    {
        static_assert(std::is_base_of_v<events::BaseUserEvent, T>, "T must derive from UserEvent");

        auto typeIndex = std::type_index(typeid(T));
        SubscriptionId id = ++m_nextSubId;

        auto& vector = m_listeners[typeIndex];

        vector.push_back({
            id,
            priority,
            [listener](const events::BaseUserEvent& e) {
                listener(static_cast<const T&>(e));
            }
            });

        // Sort higher priority handlers first
        std::stable_sort(vector.begin(), vector.end(), [](const EventListenerData& a, const EventListenerData& b) {
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

            vector.erase(
                std::remove_if(vector.begin(), vector.end(),
                    [id](const EventListenerData& h) { return h.id == id; }),
                vector.end()
            );
        }
    }

    template<typename T>
    void Publish(const T& event)
    {
        static_assert(std::is_base_of_v<events::BaseUserEvent, T>, "T must derive from UserEvent");

        auto typeIndex = std::type_index(typeid(T));
        auto it = m_listeners.find(typeIndex);

        if (it != m_listeners.end()) {
            // Copy vector before iteration to safely allow unsubscribing during callback execution
            auto handlers = it->second;
            for (const auto& handler : handlers) {
                handler.callback(event);
            }
        }
    }

    template<typename EventType>
    void QueueEvent(const EventType& event)
    {
        m_deferredQueue.push_back([this, event]() {
            Publish(event);
            });
    }

    void DispatchQueued()
    {
        std::vector<std::function<void()>> processingQueue;
        processingQueue.swap(m_deferredQueue);

        for (const auto& dispatchAction : processingQueue) {
            dispatchAction();
        }
    }

private:
    struct EventListenerData
    {
        SubscriptionId id{ 0 };
        int priority{ 0 };
        std::function<void(const events::BaseUserEvent&)> callback;
    };

    SubscriptionId m_nextSubId{ 0 };
    std::unordered_map<std::type_index, std::vector<EventListenerData>> m_listeners;
    std::vector<std::function<void()>> m_deferredQueue;
};

} // namespace tb::app

#define TB_APP_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#endif // TB_APP_EVENT_DISPATCHER_HPP