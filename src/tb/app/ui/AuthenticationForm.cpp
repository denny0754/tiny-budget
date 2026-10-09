#include <tb/app/ui/AuthenticationForm.hpp>

#include <imgui.h>

namespace tb::app::ui
{

void AuthenticationForm::OnInit()
{

}

void AuthenticationForm::OnRender()
{
    // Center window on viewport
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 centerPos{ io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f };
    ImGui::SetNextWindowPos(centerPos, ImGuiCond_Once, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize({ 480.0f, 0.0f }, ImGuiCond_Always);

    ImGui::Begin(
        "TinyBudget - Authentication",
        nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove
    );

    float fullWidth = ImGui::GetContentRegionAvail().x;

    // --- SESSION TYPE SELECTION (Radio Buttons) ---
    ImGui::TextUnformatted("Session Type:");
    ImGui::SameLine();
    ImGui::RadioButton("Local", &m_sessionTypeInt, 0); // 0 = Local
    ImGui::SameLine();
    ImGui::RadioButton("Remote", &m_sessionTypeInt, 1); // 1 = Remote

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // --- FORM MODE TABS (Sign-In / Sign-Up) ---
    if (ImGui::BeginTabBar("AuthTabBar"))
    {
        // SIGN-IN TAB
        if (ImGui::BeginTabItem("Sign-In"))
        {
            m_isSignUpMode = false;
            ImGui::Spacing();

            ImGui::InputText("Email", m_emailBuf, sizeof(m_emailBuf));
            ImGui::InputText("Password", m_passwordBuf, sizeof(m_passwordBuf), ImGuiInputTextFlags_Password);

            ImGui::Spacing();

            if (ImGui::Button("Sign-In", { fullWidth, 32.0f }))
            {
                // Pure UI - Action Triggered
                // m_sessionTypeInt == 0 -> Local API
                // m_sessionTypeInt == 1 -> Remote API
            }

            ImGui::EndTabItem();
        }

        // SIGN-UP TAB
        if (ImGui::BeginTabItem("Sign-Up"))
        {
            m_isSignUpMode = true;
            ImGui::Spacing();

            ImGui::InputText("First Name", m_firstNameBuf, sizeof(m_firstNameBuf));
            ImGui::InputText("Last Name", m_lastNameBuf, sizeof(m_lastNameBuf));
            ImGui::InputText("Email", m_emailBuf, sizeof(m_emailBuf));
            ImGui::InputText("Password", m_passwordBuf, sizeof(m_passwordBuf), ImGuiInputTextFlags_Password);

            ImGui::Spacing();

            if (ImGui::Button("Sign-Up", { fullWidth, 32.0f }))
            {
                // Pure UI - Action Triggered
                // m_sessionTypeInt == 0 -> Local API
                // m_sessionTypeInt == 1 -> Remote API
            }

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}

void AuthenticationForm::OnUpdate(double deltaTime)
{
    
}

void AuthenticationForm::OnShutdown()
{

}

std::string AuthenticationForm::GetComponentId() const
{
    return "AuthenticationForm";
}

} // ns tb::app::ui