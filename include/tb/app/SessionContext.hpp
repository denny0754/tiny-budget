 #ifndef TB_APP_SESSION_CONTEXT_HPP
#define TB_APP_SESSION_CONTEXT_HPP

#include <memory>

#include <tb/app/providers/APIProvider.hpp>

#include <spdlog/spdlog.h>

namespace tb::app
{

struct SessionContext
{
	std::shared_ptr<tb::app::providers::APIProvider> apiProvider;

	std::shared_ptr<spdlog::logger> logger;
}; // st SessionContext

} // ns tb::app

#endif