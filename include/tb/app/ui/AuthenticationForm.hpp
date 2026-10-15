#ifndef TB_APP_UI_AUTHENTICATION_FORM_HPP
#define TB_APP_UI_AUTHENTICATION_FORM_HPP

#include <tb/app/ui/GlobalComponent.hpp>

namespace tb::app::ui
{

class AuthenticationForm : public tb::app::ui::GlobalComponent
{
public:
	void OnInit();

	void OnRender();

	void OnUpdate(double deltaTime = 0.f);

	void OnShutdown();

	std::string GetComponentId() const;

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

}; // cl AuthenticationForm

} // ns tb::app::ui

#endif