#ifndef TB_UI_VIEW_MANAGER_HPP
#define TB_UI_VIEW_MANAGER_HPP

#include "ui/stores/SystemStore.hpp"
#include "ui/stores/UserStore.hpp"
#include "ui/ViewContext.hpp"

#include <glfw/glfw3.h>

namespace tb::ui
{

class ViewManager
{
public:
	ViewManager(
		const tb::ui::SystemStore& sys_store, const tb::ui::UserStore& usr_store,
		const tb::ui::ViewContext& view_context = {1280, 720, "Tiny-Budget"}
	);

	bool ShouldClose();

	void PollEvents();

	void Update();

	void Render();

	~ViewManager();

private:
	GLFWWindow* m_nativeWindow;
};

} // ns tb::ui

#endif