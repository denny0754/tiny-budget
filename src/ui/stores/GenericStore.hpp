#ifndef TB_UI_STORES_GENERIC_STORE_HPP
#define TB_UI_STORES_GENERIC_STORE_HPP

#include <cassert>
#include <functional>
#include <memory>
#include <mutex>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

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
	 * @brief Dequeues and executes all pending tasks across sub-stores and this store on the calling thread.
	 */
	void Poll()
	{
		for (const auto& [key, subStore] : m_subStores)
		{
			subStore->Poll();
		}

		std::vector<std::function<void()>> pendingTasks;
		{
			std::scoped_lock<std::mutex> lock(m_mutex);
			pendingTasks.swap(m_tasks);
		}

		for (const auto& task : pendingTasks)
		{
			if (task)
			{
				task();
			}
		}
	}

	/**
	 * @brief Enqueues a task handler to be executed during a subsequent Poll() cycle.
	 * @param task Callable function object to enqueue.
	 */
	void PostTask(std::function<void()> task)
	{
		if (task)
		{
			std::scoped_lock<std::mutex> lock(m_mutex);
			m_tasks.emplace_back(std::move(task));
		}
	}

	/**
	 * @brief Retrieves a non-owning pointer to a registered sub-store of the requested type.
	 * @tparam SubStore Derived GenericStore type to look up.
	 * @return Weak pointer to the sub-store instance, or expired weak pointer if not registered.
	 */
	template<class SubStore>
	[[nodiscard]] std::weak_ptr<SubStore> GetSubStore() const
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
	/**
		 * @brief Retrieves a reference to a registered sub-store of the requested type.
		 * @tparam SubStore Derived GenericStore type to look up.
		 * @return Reference to the registered sub-store instance.
		 * @throws std::logic_error If the requested sub-store type has not been registered.
		 */
	template<class SubStore>
	[[nodiscard]] SubStore& GetSubStore()
	{
		static_assert(
			std::is_base_of_v<GenericStore, SubStore> &&
			!std::is_same_v<GenericStore, std::remove_cv_t<SubStore>>,
			"SubStore needs to derive from tb::ui::GenericStore!"
			);

		const auto typeIndex = std::type_index(typeid(SubStore));
		const auto it = m_subStores.find(typeIndex);

		assert(it != m_subStores.end() && "SubStore is not registered!");
		if (it == m_subStores.end())
		{
			throw std::logic_error("Requested SubStore is not registered.");
		}

		return static_cast<SubStore&>(*it->second);
	}

	/**
	 * @brief Retrieves a const reference to a registered sub-store of the requested type.
	 * @tparam SubStore Derived GenericStore type to look up.
	 * @return Const reference to the registered sub-store instance.
	 * @throws std::logic_error If the requested sub-store type has not been registered.
	 */
	template<class SubStore>
	[[nodiscard]] const SubStore& GetSubStore() const
	{
		return const_cast<GenericStore*>(this)->GetSubStore<SubStore>();
	}

	/**
	 * @brief Discards all unpolled tasks in this store and recursively in all registered sub-stores.
	 */
	void ClearTasks()
	{
		for (const auto& [key, subStore] : m_subStores)
		{
			subStore->ClearTasks();
		}

		std::scoped_lock<std::mutex> lock(m_mutex);
		m_tasks.clear();
	}

private:
	std::vector<std::function<void()>> m_tasks;

	std::mutex m_mutex;

	std::unordered_map<std::type_index, std::shared_ptr<tb::ui::GenericStore>> m_subStores;

}; // cl GenericStore

} // ns tb::ui

#endif