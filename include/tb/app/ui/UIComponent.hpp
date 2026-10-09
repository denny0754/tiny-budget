#ifndef TB_APP_UI_UI_COMPONENT_HPP
#define TB_APP_UI_UI_COMPONENT_HPP

#include <string>

#include <tb/app/SessionContext.hpp>

namespace tb::app::ui
{

class UIController;

enum class UIComponentState
{
	OPENED,
	CLOSED
	
}; // en UIcomponentState

class UIComponent
{
public:
	virtual void OnInit() = 0;

	virtual void OnRender() = 0;

	virtual void OnUpdate(double deltaTime = 0.f) = 0;

	virtual void OnShutdown() = 0;

	virtual std::string GetComponentId() const = 0;

	inline UIComponentState GetState() const { return m_state; }

protected:
	inline void SetState(UIComponentState state) { m_state = state; }

private:
	friend class UIController;
	void BindSessionContext(std::shared_ptr<SessionContext> sessionCtx)
	{
		m_sessionCtx = sessionCtx;
	}

private:

	UIComponentState m_state{ UIComponentState::OPENED };

protected:
	std::shared_ptr<SessionContext> m_sessionCtx;

}; // cl UIComponent

} // ns tb::app::ui

#endif