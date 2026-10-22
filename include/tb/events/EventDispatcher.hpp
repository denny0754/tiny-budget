#ifndef TB_EVENTS_EVENT_DISPATCHER_HPP
#define TB_EVENTS_EVENT_DISPATCHER_HPP

#include <tb/events/Event.hpp>

#include <queue>
#include <functional>
#include <vector>
#include <typeindex>
#include <memory>
#include <unordered_map>

namespace tb::events
{

template<typename T>
using EventListenerRef = std::function<void(const T&)>;

using SubscriptionId = uint32_t;

class EventDispatcher
{
public:
	EventDispatcher();

	~EventDispatcher();

	template<typename ECls>
	SubscriptionId Subscribe(EventListenerRef<ECls> listener, int priority = 0)
	{
		static_assert(std::is_base_of_v<tb::events::Event, ECls>, "ECls must derive from Event.");

		auto typeIndex = std::type_index(typeid(ECls));
		SubscriptionId id = ++m_nextSubId;

		auto& vector = m_listeners[typeIndex];

		vector.push_back({
			id,
			priority,
			[listener](const tb::events::Event& e) {
				listener(static_cast<const ECls&>(e));
			}
		});

		std::stable_sort(vector.begin(), vector.end(), [](const EventHandlerData& a, const EventHandlerData& b) {
			return a.priority > b.priority;
		});

		return id;
	}

	template<typename ECls>
	void Enqueue(std::unique_ptr<ECls> event)
	{
		static_assert(
			std::is_base_of_v<tb::events::SystemEvent, ECls> ||
			std::is_base_of_v<tb::events::SessionEvent, ECls> ||
			std::is_base_of_v<tb::events::UserInterfaceEvent, ECls>,
			"ECls must derive from one of the following: SystemEvent, SessionEvent or UserInterfaceEvent. None was detected!"
		);

		if constexpr (std::is_base_of_v<tb::events::SystemEvent, ECls>)
		{
			m_systemQueue.push(std::move(event));
		}
		else if constexpr (std::is_base_of_v<tb::events::SessionEvent, ECls>)
		{
			m_sessionQueue.push(std::move(event));
		}
		else if constexpr (std::is_base_of_v<tb::events::UserInterfaceEvent, ECls>)
		{
			m_userQueue.push(std::move(event));
		}
	}

	void Flush()
	{
		FlushQueue(m_systemQueue);
		FlushQueue(m_sessionQueue);
		FlushQueue(m_userQueue);
	}

private:
	template<typename TQueueItem>
	void FlushQueue(std::queue<std::unique_ptr<TQueueItem>>& queue)
	{
		while (!queue.empty())
		{
			auto event = std::move(queue.front());
			queue.pop();

			DispatchToSubscribers(*event);
		}
	}

	void DispatchToSubscribers(const tb::events::Event& event)
	{
		auto typeIndex = std::type_index(typeid(event));
		auto it = m_listeners.find(typeIndex);
		if (it == m_listeners.end())
		{
			return;
		}

		for (const auto& handler : it->second)
		{
			if (event.Handled)
			{
				break;
			}
			handler.callback(event);
		}
	}

	std::queue<std::unique_ptr<tb::events::SystemEvent>> m_systemQueue;
	std::queue<std::unique_ptr<tb::events::SessionEvent>> m_sessionQueue;
	std::queue<std::unique_ptr<tb::events::UserInterfaceEvent>> m_userQueue;

	struct EventHandlerData
	{
		SubscriptionId id;
		int priority;
		EventListenerRef<tb::events::Event> callback;
	};

	std::unordered_map<std::type_index, std::vector<EventHandlerData>> m_listeners;
}; // cl EventBus

} // ns tb::events

#define TB_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#endif