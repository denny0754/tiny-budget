#ifndef TB_UI_GLOBAL_SIDE_MENU_HPP
#define TB_UI_GLOBAL_SIDE_MENU_HPP

#include <tb/ui/interfaces/Component.hpp>

namespace tb::ui
{

class SideMenu : public tb::ui::GlobalComponent
{
public:
	SideMenu(
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

}; // cl SideMenu

} // ns tb::ui

#endif