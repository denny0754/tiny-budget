#ifndef TB_CORE_CONTEXT_HPP
#define TB_CORE_CONTEXT_HPP

#include <spdlog/spdlog.h>

#include <memory>
#include <tb/core/ev/EventBus.hpp>

namespace tb::core
{

struct Context
{
    std::shared_ptr<tb::core::ev::EventBus> eventBus;

    std::shared_ptr<spdlog::logger> logger;
};

} // ns tb::core

#endif