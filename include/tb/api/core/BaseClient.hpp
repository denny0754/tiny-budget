#ifndef TB_API_BASE_CLIENT_HPP
#define TB_API_BASE_CLIENT_HPP

#include <tb/api/core/SessionContext.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>

namespace tb::api
{

class BaseClient
{
public:
    explicit BaseClient(std::shared_ptr<tb::api::SessionContext> ctx)
        : m_sessionCtx(ctx)
    {
        
    }

    std::shared_ptr<tb::api::SessionContext> GetSessionContext() const
    {
        return m_sessionCtx;
    }

    virtual ~BaseClient() = default;

private:
    std::shared_ptr<tb::api::SessionContext> m_sessionCtx;
}; // cl BaseClient

} // ns tb::api

#endif