#ifndef TB_TOOLS_LOGGING_HPP
#define TB_TOOLS_LOGGING_HPP

#include <spdlog/spdlog.h>

#include <memory>

namespace tb::tools::log
{

std::shared_ptr<spdlog::logger> GetApiLogger();
std::shared_ptr<spdlog::logger> GetCoreLogger();
std::shared_ptr<spdlog::logger> GetSessionLogger();

}

#endif