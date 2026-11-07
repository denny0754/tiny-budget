#ifndef TB_UI_LOCAL_BOOK_EDITOR_DIALOG_HPP
#define TB_UI_LOCAL_BOOK_EDITOR_DIALOG_HPP

#include <tb/ui/interfaces/Component.hpp>
#include <tb/models/dto/Currency.hpp>

namespace tb::ui
{

struct BookEditorData : public ComponentData
{
	BookEditorData(
		tb::ui::EditorMode mode,
		const std::string& bookId = std::string()
	)
		: Mode(mode), BookId(bookId)
	{ }

	tb::ui::EditorMode Mode;

	std::string BookId;
}; // st BookEditorData

class BookEditorDialog : public tb::ui::LocalComponent
{
public:
	BookEditorDialog(
		const std::shared_ptr<tb::events::EventDispatcher>& dispatcher,
		const std::shared_ptr<tb::core::Session>& session,
		std::unique_ptr<tb::ui::BookEditorData> data
	);

	void OnInit();

	void OnUpdate();

	void OnRender();

	void OnShutdown();

private:
	void Render_Read();

	void Render_Edit();

	void Render_New();

	// Form input buffers
	char m_nameBuffer[128]{ "" };
	char m_descriptionBuffer[512]{ "" };

	// Currency selection cache
	std::vector<tb::models::dto::GetCurrencyResponse> m_currencies;
	int m_selectedCurrencyIndex{ -1 };

	// State tracking
	std::string m_errorMessage;
	bool m_isSubmitting{ false };

}; // cl BookEditorDialog

} // ns tb::ui

#endif