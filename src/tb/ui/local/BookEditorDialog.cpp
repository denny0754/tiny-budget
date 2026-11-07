#include <tb/ui/local/BookEditorDialog.hpp>
#include <tb/api/CurrencyClient.hpp>

#include <imgui.h>

namespace tb::ui
{

BookEditorDialog::BookEditorDialog(
	const std::shared_ptr<tb::events::EventDispatcher>& dispatcher,
	const std::shared_ptr<tb::core::Session>& session,
	std::unique_ptr<tb::ui::BookEditorData> data
)
	: tb::ui::LocalComponent(dispatcher, session, std::move(data))
{

	tb::models::dto::APIQueryParams params;
	params.Page = 0;
	params.PageSize = 250;

	GetSession()->GetService()->GetClient<tb::api::CurrencyClient>()->GetAny(params, [this](const tb::models::dto::PaginatedAPIResult<tb::models::dto::GetCurrencyResponse>& result) {
		if (result.Success)
		{
			m_currencies = result.Data;

			if (!m_currencies.empty())
			{
				m_selectedCurrencyIndex = 0;
			}
		}
		else
		{
			m_errorMessage = result.ErrorMessage;
		}
		});
}

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
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(460.0f, 0.0f), ImGuiCond_Appearing);

	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoDocking;

	if (ImGui::Begin(std::format("Create New Financial Book##{}", GetComponentId()).c_str(), nullptr, windowFlags))
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.22f, 0.82f, 0.52f, 1.00f));
		ImGui::TextUnformatted("Set Up Your Financial Book");
		ImGui::PopStyleColor();

		ImGui::TextDisabled("A book encapsulates all your accounts, transactions, and payees.");
		ImGui::Separator();
		ImGui::Spacing();

		ImGui::Text("Book Name *");
		ImGui::SetNextItemWidth(-1.0f);
		ImGui::InputText("##BookName", m_nameBuffer, sizeof(m_nameBuffer));

		ImGui::Spacing();

		ImGui::Text("Description");
		ImGui::SetNextItemWidth(-1.0f);
		ImGui::InputTextMultiline("##BookDesc", m_descriptionBuffer, sizeof(m_descriptionBuffer), ImVec2(0, 60));

		ImGui::Spacing();

		ImGui::Text("Base Currency *");
		ImGui::SetNextItemWidth(-1.0f);

		std::string comboPreview = "Select Currency...";
		if (m_selectedCurrencyIndex >= 0 && m_selectedCurrencyIndex < static_cast<int>(m_currencies.size()))
		{
			const auto& selected = m_currencies[m_selectedCurrencyIndex];
			comboPreview = std::format("{} - {} ({})", selected.IsoCode, selected.Label, selected.Symbol);
		}

		if (ImGui::BeginCombo("##CurrencyCombo", comboPreview.c_str()))
		{
			for (int i = 0; i < static_cast<int>(m_currencies.size()); ++i)
			{
				const bool isSelected = (m_selectedCurrencyIndex == i);
				const auto& curr = m_currencies[i];
				std::string itemLabel = std::format("{} - {} ({})", curr.IsoCode, curr.Label, curr.Symbol);

				if (ImGui::Selectable(itemLabel.c_str(), isSelected))
				{
					m_selectedCurrencyIndex = i;
				}

				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		if (!m_errorMessage.empty())
		{
			ImGui::Spacing();
			ImGui::TextColored(ImVec4(1.0f, 0.36f, 0.36f, 1.0f), "%s", m_errorMessage.c_str());
		}

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		const bool isNameValid = (std::strlen(m_nameBuffer) > 0);
		const bool isCurrencyValid = (m_selectedCurrencyIndex >= 0 && m_selectedCurrencyIndex < static_cast<int>(m_currencies.size()));
		const bool isFormValid = isNameValid && isCurrencyValid;

		const float buttonWidth = 110.0f;
		const float itemSpacing = ImGui::GetStyle().ItemSpacing.x;
		const float padding = ImGui::GetStyle().WindowPadding.x;

		ImGui::SetCursorPosX(ImGui::GetWindowWidth() - (buttonWidth * 2.0f + itemSpacing + padding));

		if (ImGui::Button("Cancel", ImVec2(buttonWidth, 0.0f)))
		{
			Close();
		}

		ImGui::SameLine();

		if (!isFormValid)
		{
			ImGui::BeginDisabled();
		}

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.40f, 0.28f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.16f, 0.50f, 0.35f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.20f, 0.60f, 0.42f, 1.00f));

		if (ImGui::Button("Create Book", ImVec2(buttonWidth, 0.0f)))
		{
			//TODO: Call GetSession()->GetService()->GetClient<tb::api::BookClient>()->Create(...) once implemented.
			Close();
		}

		ImGui::PopStyleColor(3);

		if (!isFormValid)
		{
			ImGui::EndDisabled();
			if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
			{
				if (!isNameValid)
				{
					ImGui::SetTooltip("Please enter a book name.");
				}
				else if (!isCurrencyValid)
				{
					ImGui::SetTooltip("Please select a valid base currency.");
				}
			}
		}

		ImGui::End();
	}
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