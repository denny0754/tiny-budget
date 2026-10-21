#ifndef TB_CORE_CONTEXT_HPP
#define TB_CORE_CONTEXT_HPP

#include <spdlog/spdlog.h>

#include <memory>
#include <tb/core/EventBus.hpp>

namespace tb::core
{

struct AppContext
{
    std::shared_ptr<tb::core::EventBus> eventBus;
};

} // ns tb::core

#endif