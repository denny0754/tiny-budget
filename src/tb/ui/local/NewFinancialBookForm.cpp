#include <tb/ui/local/NewFinancialBookForm.hpp>

#include <imgui.h>

namespace tb::ui
{

void NewFinancialBookForm::OnInit()
{

}

void NewFinancialBookForm::OnUpdate()
{

}

void NewFinancialBookForm::OnRender()
{
	ImGui::Begin("New Financial Book Form");

	ImGui::End();
}

void NewFinancialBookForm::OnShutdown()
{

}

const char* NewFinancialBookForm::GetComponentId() const
{
	return "NewFinancialBookForm";
}

} // tb::ui