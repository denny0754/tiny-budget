#ifndef TB_APP_MODULES_SESSION_HPP
#define TB_APP_MODULES_SESSION_HPP

#include <memory> 

#include <tb/core/BaseModule.hpp>
#include <tb/app/SessionContext.hpp>

namespace tb::app::modules
{

class Session : public core::BaseModule
{
public:

	void OnInit() override;

	void OnRender() override;

	void OnUpdate(double deltaTime = 0.f) override;

	void OnShutdown() override;

private:
	void OnSessionOpen();

	void OnSessionClose();

private:
	std::shared_ptr<SessionContext> m_sessionCtx;

	int m_sessionTypeInt = 0; // 0 = Local, 1 = Remote
	bool m_isSignUpMode = false;

	char m_emailBuf[128] = "";
	char m_passwordBuf[128] = "";
	char m_firstNameBuf[64] = "";
	char m_lastNameBuf[64] = "";

}; // cl Session

} // ns tb::app::modules

#endif