 #ifndef TB_APP_SESSION_CONTEXT_HPP
#define TB_APP_SESSION_CONTEXT_HPP

#include <memory>

#include <tb/api/core/BaseApiService.hpp>
#include <tb/app/EventDispatcher.hpp>

#include <spdlog/spdlog.h>

namespace tb::app
{

struct SessionContext
{
	std::shared_ptr<tb::api::BaseApiService> apiService;

	std::shared_ptr<tb::app::EventDispatcher> eventDispatcher;
}; // st SessionContext

} // ns tb::app

#endif