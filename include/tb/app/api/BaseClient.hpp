#ifndef TB_APP_API_BASE_CLIENT_HPP
#define TB_APP_API_BASE_CLIENT_HPP

#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>

namespace tb::app::api
{

class BaseClient
{
public:
    virtual ~BaseClient() = default;

protected:
    std::shared_ptr<spdlog::logger> GetLogger()
    {
        auto logger = spdlog::get("API");
        if (!logger)
        {
            std::vector<spdlog::sink_ptr> sinks = {
                std::make_shared<spdlog::sinks::rotating_file_sink_mt>("./logs/api.log", 52428800U, 7, false),
                std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
            };
            logger = std::make_shared<spdlog::logger>("API", sinks.begin(), sinks.end());
            logger->set_level(spdlog::level::trace);
            logger->set_pattern("[%Y-%m-%d %H:%M:%S] %n - %^%l%$: %v");
            spdlog::register_logger(logger);
        }
        return logger;
    }
}; // cl BaseClient

} // ns tb::app::api

#endif