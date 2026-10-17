#include <tb/app/ui/FinancialBookSetup.hpp>

#include <imgui.h>

namespace tb::app::ui
{

void FinancialBookSetup::OnInit()
{

}

void FinancialBookSetup::OnRender()
{
    // --- Center Window on Screen ---
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(460, 0), ImGuiCond_Appearing); // Auto-fit height

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoDocking;

    if (ImGui::Begin("Create New Financial Book##dialog", nullptr, windowFlags))
    {
        // --- Header Section ---
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.22f, 0.82f, 0.52f, 1.00f)); // Mint Accent
        ImGui::TextUnformatted("Set Up Your Financial Book");
        ImGui::PopStyleColor();

        ImGui::TextDisabled("A book encapsulates all your accounts, transactions, and payees.");
        ImGui::Separator();
        ImGui::Spacing();

        // --- Form Controls ---
        ImGui::Text("Book Name *");
        ImGui::SetNextItemWidth(-1.0f); // Stretch to right edge
        ImGui::InputText("##BookName", m_nameBuffer, sizeof(m_nameBuffer));

        ImGui::Spacing();

        ImGui::Text("Description");
        ImGui::SetNextItemWidth(-1.0f);
        ImGui::InputTextMultiline("##BookDesc", m_descBuffer, sizeof(m_descBuffer), ImVec2(0, 60));

        ImGui::Spacing();

        ImGui::Text("Base Currency");
        ImGui::SetNextItemWidth(-1.0f);
        static const char* currencies[] = {
            "EUR - Euro (€)",
            "USD - US Dollar ($)",
            "GBP - British Pound (£)",
            "CHF - Swiss Franc (CHF)",
            "JPY - Japanese Yen (¥)"
        };
        ImGui::Combo("##CurrencyCombo", &m_selectedCurrencyIdx, currencies, IM_ARRAYSIZE(currencies));

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // --- Helper Options ---
        ImGui::Checkbox("Seed default accounts (Checking, Savings, Cash)", &m_createDefaultAccounts);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // --- Action Buttons ---
        bool isNameValid = (std::strlen(m_nameBuffer) > 0);
        float buttonWidth = 110.0f;
        float itemSpacing = ImGui::GetStyle().ItemSpacing.x;
        float padding = ImGui::GetStyle().WindowPadding.x;

        // Align buttons to the right
        ImGui::SetCursorPosX(ImGui::GetWindowWidth() - (buttonWidth * 2.0f + itemSpacing + padding));

        if (ImGui::Button("Cancel", ImVec2(buttonWidth, 0.0f)))
        {
            Close(); // Marks component for closure in Controller
        }

        ImGui::SameLine();

        // Disable "Create" if mandatory fields are missing
        if (!isNameValid)
        {
            ImGui::BeginDisabled();
        }

        // Highlight Primary Action
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.40f, 0.28f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.16f, 0.50f, 0.35f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.20f, 0.60f, 0.42f, 1.00f));

        if (ImGui::Button("Create Book", ImVec2(buttonWidth, 0.0f)))
        {
            // TODO: Execute book persistence logic via SessionContext / Repository
            // e.g. m_sessionCtx->CreateBook(m_nameBuffer, m_descBuffer, currencyCode);

            Close();
        }

        ImGui::PopStyleColor(3);

        if (!isNameValid)
        {
            ImGui::EndDisabled();
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            {
                ImGui::SetTooltip("Please enter a book name.");
            }
        }

        ImGui::End();
    }
}

void FinancialBookSetup::OnUpdate(double deltaTime)
{

}

void FinancialBookSetup::OnShutdown()
{

}

} // ns tb::app::ui