#ifndef TB_APP_SERVICE_REGISTRY_HPP
#define TB_APP_SERVICE_REGISTRY_HPP

#include <memory>

#include <tb/api/core/BaseApiService.hpp>
#include <tb/app/EventDispatcher.hpp>

#include <spdlog/spdlog.h>

namespace tb::app
{

struct ServiceRegistry
{
	std::shared_ptr<tb::api::BaseApiService> apiService;

	std::shared_ptr<tb::app::EventDispatcher> eventDispatcher;
}; // st ServiceRegistry

} // ns tb::app

#endif