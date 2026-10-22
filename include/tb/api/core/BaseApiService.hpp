#ifndef TB_API_BASE_API_SERVICE_HPP
#define TB_API_BASE_API_SERVICE_HPP

#include <tb/models/dto/Common.hpp>
#include <tb/api/Version.hpp>
#include <tb/api/interfaces/IAuthClient.hpp>
#include <tb/api/interfaces/IFinancialBookClient.hpp>
#include <tb/api/core/SessionContext.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>

namespace tb::api
{

class BaseApiService
{
public:

	virtual ~BaseApiService() = default;

    const std::unique_ptr<tb::api::IAuthClient>& GetAuthClient() const { return m_authClient; }
    const std::unique_ptr<tb::api::IFinancialBookClient>& GetFinancialBookClient() const { return m_financialBookClient; }

protected:

    std::unique_ptr<tb::api::IAuthClient> m_authClient;
    std::unique_ptr<tb::api::IFinancialBookClient> m_financialBookClient;

    std::shared_ptr<tb::api::SessionContext> m_apiCtx;

}; // cl BaseApiService

} // ns tb::api

#endif