#ifndef TB_APP_UI_MENU_BAR_HPP
#define TB_APP_UI_MENU_BAR_HPP

#include <tb/app/ui/GlobalComponent.hpp>

#include <unordered_map>

namespace tb::app::ui
{

class MenuBar : public tb::app::ui::GlobalComponent
{
public:
	void OnInit();

	void OnRender();

	void OnUpdate(double deltaTime = 0.f);

	void OnShutdown();

	std::string GetComponentId() const;

private:
	std::unordered_map<std::string, std::string> m_financialBooksList;

}; // cl MenuBar

} // ns tb::app::ui

#endif