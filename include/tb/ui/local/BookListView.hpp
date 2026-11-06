#ifndef TB_UI_LOCAL_BOOK_LIST_DIALOG_HPP
#define TB_UI_LOCAL_BOOK_LIST_DIALOG_HPP

#include <tb/ui/interfaces/Component.hpp>

namespace tb::ui
{

class BookListDialog : public tb::ui::LocalComponent
{
public:
	BookListDialog(
		const std::shared_ptr<tb::events::EventDispatcher>& dispatcher,
		const std::shared_ptr<tb::core::Session>& session
	)
		: m_eventDispatcher(dispatcher), m_session(session)
	{

	}

	void OnInit();

	void OnUpdate();

	void OnRender();

	void OnShutdown();

	const char* GetComponentId() const;

}; // cl BookListDialog

} // ns tb::ui

#endif