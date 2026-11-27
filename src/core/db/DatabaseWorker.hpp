#ifndef TB_CORE_DB_DATABASE_WORKER_HPP
#define TB_CORE_DB_DATABASE_WORKER_HPP

#include "SecuritySession.hpp"
#include "UserSession.hpp"

#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include <variant>

namespace tb::db
{

class DatabaseWorker
{
public:
	DatabaseWorker() = default;

	void Start();

	void Stop();

	void InitializeSecuritySession(const std::string& dbPath, const std::string& hexKey256);

	void InitializeUserSession(const std::string& dbPath, const std::string& hexKey256);

	void PostSystemTask(std::function<void(const tb::db::SecuritySession&)> task);

	void PostUserTask(std::function<void(const tb::db::UserSession&)> task);

private:
	void Run(std::stop_token token);

	std::jthread m_executor;

	std::unique_ptr<tb::db::SecuritySession> m_securitySession;
	std::unique_ptr<tb::db::UserSession> m_userSession;

	enum class InternalTaskType
	{
		SystemTask,
		UserTask
	}; // ec InternalTaskType

	struct InternalTaskData
	{
		using SystemTaskHandlerRef = std::function<void(const tb::db::SecuritySession&)>;
		using UserTaskHandlerRef = std::function<void(const tb::db::UserSession&)>;
		std::variant<SystemTaskHandlerRef, UserTaskHandlerRef> handler;
		InternalTaskType type;
	}; // st InternalTaskData

	std::vector<InternalTaskData> m_tasks;
	std::vector<InternalTaskData> m_execTasks;

	std::mutex m_mutex;

}; // cl DatabaseWorker

} // ns tb::db

#endif