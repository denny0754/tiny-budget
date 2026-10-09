#ifndef TB_APP_UI_AUTHENTICATION_FORM_HPP
#define TB_APP_UI_AUTHENTICATION_FORM_HPP

#include <tb/app/ui/UIComponent.hpp>

namespace tb::app::ui
{

class AuthenticationForm : public UIComponent
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

}; // cl AuthenticationForm

} // ns tb::app::ui

#endif