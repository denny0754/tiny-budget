 #ifndef TB_APP_SESSION_CONTEXT_HPP
#define TB_APP_SESSION_CONTEXT_HPP

#include <memory>

#include <tb/app/api/BaseApiService.hpp>
#include <tb/app/EventDispatcher.hpp>

#include <spdlog/spdlog.h>

namespace tb::app
{

struct SessionData
{
	std::string identityId;

	std::string email;

	std::string firstName;

	std::string lastName;

}; // st SessionData

struct SessionContext
{
	SessionData sessionData;

	std::shared_ptr<tb::app::api::BaseApiService> apiService;

	std::shared_ptr<tb::app::EventDispatcher> eventDispatcher;

	std::shared_ptr<spdlog::logger> logger;
}; // st SessionContext

} // ns tb::app

#endif