#ifndef TB_UI_GLOBAL_AUTH_FORM_HPP
#define TB_UI_GLOBAL_AUTH_FORM_HPP

#include <tb/ui/interfaces/Component.hpp>

namespace tb::ui
{

class AuthForm : public tb::ui::GlobalComponent
{
public:
	AuthForm(
		const std::shared_ptr<tb::events::EventDispatcher>& dispatcher,
		const std::shared_ptr<tb::core::Session>& session
	)
		: tb::ui::GlobalComponent(dispatcher, session)
	{

	}

	void OnInit() override;

	void OnUpdate() override;

	void OnRender() override;

	void OnShutdown() override;

	const char* GetComponentId() const override;

private:
	int m_sessionTypeInt = 0; // 0 = Local, 1 = Remote
	bool m_isSignUpMode = false;

	char m_emailBuf[128] = "";
	char m_passwordBuf[128] = "";
	char m_firstNameBuf[64] = "";
	char m_lastNameBuf[64] = "";

	bool m_isProcessing{ false };
	std::string m_errorMessage;
	std::string m_successMessage;
}; // cl AuthForm

} // ns tb::ui

#endif