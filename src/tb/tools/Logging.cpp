#include <tb/tools/Logging.hpp>

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace tb::tools::log
{

std::shared_ptr<spdlog::logger> GetApiLogger()
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

std::shared_ptr<spdlog::logger> GetCoreLogger()
{
    auto logger = spdlog::get("APP");
    if (!logger)
    {
        std::vector<spdlog::sink_ptr> sinks = {
            std::make_shared<spdlog::sinks::rotating_file_sink_mt>("./logs/app.log", 52428800U, 7, false),
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
        };
        logger = std::make_shared<spdlog::logger>("APP", sinks.begin(), sinks.end());
        logger->set_level(spdlog::level::trace);
        logger->set_pattern("[%Y-%m-%d %H:%M:%S] %n - %^%l%$: %v");
        spdlog::register_logger(logger);
    }
    return logger;
}

std::shared_ptr<spdlog::logger> GetSessionLogger()
{
    auto logger = spdlog::get("SESSION");
    if (!logger)
    {
        std::vector<spdlog::sink_ptr> sinks = {
            std::make_shared<spdlog::sinks::rotating_file_sink_mt>("./logs/session.log", 52428800U, 7, false),
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
        };
        logger = std::make_shared<spdlog::logger>("SESSION", sinks.begin(), sinks.end());
        logger->set_level(spdlog::level::trace);
        logger->set_pattern("[%Y-%m-%d %H:%M:%S] %n - %^%l%$: %v");
        spdlog::register_logger(logger);
    }
    return logger;
}


}