#ifndef TB_APP_UI_LOCAL_COMPONENT_HPP
#define TB_APP_UI_LOCAL_COMPONENT_HPP

#include <tb/app/ui/IComponent.hpp>

namespace tb::app::ui
{

class LocalComponent : public IComponent
{
public:
	virtual void OnInit() = 0;

	virtual void OnRender() = 0;

	virtual void OnUpdate(double deltaTime = .0f) = 0;

	virtual void OnShutdown() = 0;
}; // cl LocalComponent

} // ns tb::app::ui

#endif