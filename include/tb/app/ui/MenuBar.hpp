#ifndef TB_APP_UI_MENU_BAR_HPP
#define TB_APP_UI_MENU_BAR_HPP

#include <tb/app/ui/GlobalComponent.hpp>

namespace tb::app::ui
{

class MenuBar : public GlobalComponent
{
public:
	void OnInit();

	void OnRender();

	void OnUpdate(double deltaTime = 0.f);

	void OnShutdown();

	std::string GetComponentId() const;
}; // cl MenuBar

} // ns tb::app::ui

#endif