#include <tb/ui/local/BookEditorDialog.hpp>

#include <imgui.h>

namespace tb::ui
{

void BookEditorDialog::OnInit()
{

}

void BookEditorDialog::OnUpdate()
{

}

void BookEditorDialog::OnRender()
{

	switch (GetDataAs<tb::ui::BookEditorData>()->Mode)
	{
		case tb::ui::EditorMode::New:
		{
			Render_New();
			break;
		}
		case tb::ui::EditorMode::Edit:
		{
			Render_Edit();
			break;
		}
		case tb::ui::EditorMode::Read:
		{
			Render_Read();
			break;
		}

	}
}

void BookEditorDialog::OnShutdown()
{

}

void BookEditorDialog::Render_New()
{
	ImGui::Begin(std::format("Create Financial Book##{}", GetComponentId()).c_str());

	ImGui::End();
}

void BookEditorDialog::Render_Edit()
{
	ImGui::Begin("Edit Financial Book");

	ImGui::End();
}

void BookEditorDialog::Render_Read()
{
	ImGui::Begin("Financial Book - {NameOfTheBook}");

	ImGui::End();
}

} // tb::ui