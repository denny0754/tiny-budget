#include "DatabaseWorker.hpp"

namespace tb::core::db
{

void DatabaseWorker::Start()
{
	m_executor = std::jthread(std::bind_front(&DatabaseWorker::Run, this));
}

void DatabaseWorker::Stop()
{
	m_executor.request_stop();
}

void DatabaseWorker::InitializeSecuritySession(const std::string& dbPath, const std::string& hexKey256)
{
	m_securitySession = std::make_unique<tb::core::db::SecuritySession>();
	m_securitySession->Open(dbPath, hexKey256);
}

void DatabaseWorker::InitializeUserSession(const std::string& dbPath, const std::string& hexKey256)
{
	m_userSession = std::make_unique<tb::core::db::UserSession>();
	m_userSession->Open(dbPath, hexKey256);
}

void DatabaseWorker::Run(std::stop_token token)
{
	while (!token.stop_requested())
	{
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_execTasks.swap(m_tasks);
		}

		for (auto& task : m_execTasks)
		{
			switch (task.type)
			{
				case InternalTaskType::SystemTask:
				{
					if (m_securitySession)
					{
						std::get<InternalTaskData::SystemTaskHandlerRef>(task.handler)(*m_securitySession);
					}
					break;
				}
				case InternalTaskType::UserTask:
				{
					if(m_userSession)
					{
						std::get<InternalTaskData::UserTaskHandlerRef>(task.handler)(*m_userSession);
					}
					break;
				}
				default:
				{
					//TODO: Log "Unknown database task type"
					break;
				}
			}
		}
	}
}

void DatabaseWorker::PostSystemTask(std::function<void(const tb::core::db::SecuritySession&)> task)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	InternalTaskData data{};
	data.handler = std::move(task);
	data.type = InternalTaskType::SystemTask;
	m_tasks.emplace_back(std::move(data));
}

void DatabaseWorker::PostUserTask(std::function<void(const tb::core::db::UserSession&)> task)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	InternalTaskData data{};
	data.handler = std::move(task);
	data.type = InternalTaskType::UserTask;
	m_tasks.emplace_back(std::move(data));
}

} // ns tb::core::db