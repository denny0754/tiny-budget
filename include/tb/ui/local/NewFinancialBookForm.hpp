#ifndef TB_UI_LOCAL_NEW_FINANCIAL_BOOK_FORM_HPP
#define TB_UI_LOCAL_NEW_FINANCIAL_BOOK_FORM_HPP

#include <tb/ui/interfaces/Component.hpp>

namespace tb::ui
{

class NewFinancialBookForm : public tb::ui::LocalComponent
{
public:
	NewFinancialBookForm(
		const std::shared_ptr<tb::events::EventDispatcher>& dispatcher,
		const std::shared_ptr<tb::core::Session>& session
	)
		: tb::ui::LocalComponent(dispatcher, session)
	{
		 
	}

	void OnInit() override;

	void OnUpdate() override;

	void OnRender() override;

	void OnShutdown() override;

	const char* GetComponentId() const override;

}; // cl NewFinancialBookForm

} // ns tb::ui

#endif