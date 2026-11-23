#ifndef TB_UI_STORES_GENERIC_STORE_HPP
#define TB_UI_STORES_GENERIC_STORE_HPP

#include <functional>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <cassert>

namespace tb::ui
{

class GenericStore
{
public:
	/**
	 * @brief Default constructor.
	*/
	GenericStore() = default;

	/**
	 * @brief Virtual default destructor.
	*/
	virtual ~GenericStore() = default;

	GenericStore(const GenericStore&) = delete;
	GenericStore& operator=(const GenericStore&) = delete;
	GenericStore(GenericStore&&) = delete;
	GenericStore& operator=(GenericStore&&) = delete;

	/**
	 * @brief Dequeues and executes all pending tasks on the calling thread.
	 */
	void Poll()
	{
		for (auto& [key, subStore] : m_subStores)
		{
			subStore->Poll();
		}

		std::vector<std::function<void()>> pendingTasks;
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			pendingTasks.swap(m_tasks);
		}

		for (auto& task : pendingTasks)
		{
			if (task)
			{
				task();
			}
		}
	}

	/**
	 * @brief Enqueues a task handler to be executed during a subsequent Poll() cycle.
	 * @param handler Callable function object to enqueue.
	 */
	void PostTask(std::function<void()> task)
	{
		if (task)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_tasks.emplace_back(std::move(task));
		}
	}

	template<class SubStore>
	std::weak_ptr<SubStore> GetSubStore() const
	{
		static_assert(
			std::is_base_of_v<GenericStore, SubStore> &&
			!std::is_same_v<GenericStore, std::remove_cv_t<SubStore>>,
			"SubStore needs to derive from tb::ui::GenericStore!"
		);

		const auto typeIndex = std::type_index(typeid(SubStore));
		if (const auto it = m_subStores.find(typeIndex); it != m_subStores.end())
		{
			return std::static_pointer_cast<SubStore>(it->second);
		}

		return {};
	}

protected:

	template<class SubStore>
	void RegisterSubStore()
	{
		static_assert(
			std::is_base_of_v<GenericStore, SubStore> &&
			!std::is_same_v<GenericStore, std::remove_cv_t<SubStore>>,
			"SubStore needs to derive from tb::ui::GenericStore!"
		);

		auto typeIndex = std::type_index(typeid(SubStore));

		m_subStores[typeIndex] = std::make_shared<SubStore>();
	}

private:
	std::vector<std::function<void()>> m_tasks;

	std::mutex m_mutex;

	std::unordered_map<std::type_index, std::shared_ptr<tb::ui::GenericStore>> m_subStores;
}; // cl GenericStore

} // ns tb::ui

#endif