/*
================================================================================
 CHANGE LOG
================================================================================
 Date       | Author        | Task ID       | Description
------------+---------------+---------------+-----------------------------------
 2026-11-10 | Diego Vaccher | UI-0000002-M  | UI API calls refactor
================================================================================
*/

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
		const std::shared_ptr<tb::core::Session>& session,
		std::unique_ptr<tb::ui::ComponentData> data = nullptr
	)
		: tb::ui::GlobalComponent(dispatcher, session, std::move(data))
	{

	}

	void OnInit() override;

	void OnUpdate() override;

	void OnRender() override;

	void OnShutdown() override;

private:
	void RenderSignUpForm();

	void RenderSignInForm();

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