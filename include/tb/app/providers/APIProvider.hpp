#ifndef TB_APP_PROVIDERS_API_PROVIDER_HPP
#define TB_APP_PROVIDERS_API_PROVIDER_HPP

#include <functional>
#include <vector>

#include <tb/models/dto/Dto.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace tb::app::providers
{

class APIProvider
{
public:
	template<typename T>
	using APICallback = std::function<void(const tb::models::dto::APIResult<T>&)>;

	APIProvider()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.push_back(
			std::make_shared<spdlog::sinks::rotating_file_sink_mt>("./logs/api.log", 52428800U, 7, false)
		);
		logSinks.push_back(
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
		);
		m_logger = std::make_shared<spdlog::logger>("API", begin(logSinks), end(logSinks));
		m_logger->set_level(spdlog::level::level_enum::trace);
		m_logger->set_pattern("[%Y-%m-%d %H:%M:%S] %n - %^%l%$: %v");
	}

	virtual ~APIProvider() = default;

	virtual void SignUp(
		const tb::models::dto::SignUpRequest& data,
		APICallback<tb::models::dto::SignUpResponse>
	) = 0;

	virtual void SignIn(
		const tb::models::dto::SignInRequest& data,
		APICallback<tb::models::dto::SignInResponse>
	) = 0;

	virtual void CreateFinancialBook(
		const tb::models::dto::CreateFinancialBookRequest& data,
		APICallback<tb::models::dto::CreateFinancialBookResponse>
	) = 0;

protected:
	std::shared_ptr<spdlog::logger> GetLogger() const { return m_logger; }

private:
	std::shared_ptr<spdlog::logger> m_logger;

}; // cl APIProvider

} // ns tb::app::providers

#endif