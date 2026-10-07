#include <tb/app/mods/LocalSessionModule.hpp>

#include <imgui.h>

namespace tb::app::mods
{

void LocalSessionModule::OnInit()
{
    m_uiData = UIData();
}

void LocalSessionModule::OnUpdate(double deltaTime)
{

}

void LocalSessionModule::OnRender()
{
    if (m_uiData.signInBtnPressed)
    {
        RenderSignInForm();
    }
    else if (m_uiData.signUpBtnPressed)
    {
        RenderSignUpForm();
    }

    ImGuiIO& imgui_io = ImGui::GetIO();

    auto win_size = imgui_io.DisplaySize;
    ImVec2 selectorWinSize{ (float)win_size.x / 4.0f, (float)win_size.y / 2.0f };
    ImVec2 selectorWinPos{ selectorWinSize.x / 2.0f, selectorWinSize.y / 2.0f };

    ImGui::SetNextWindowSize(selectorWinSize, ImGuiCond_Once);
    ImGui::SetNextWindowPos(selectorWinPos, ImGuiCond_Once);

    ImGui::Begin(
        "Sign-In/Sign-Up",
        nullptr,
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoNav |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize
    );

    // Calculate required button width and horizontal padding for centering
    float buttonWidth = selectorWinSize.x / 1.5f;
    float windowWidth = ImGui::GetWindowSize().x;
    float centeredX = (windowWidth - buttonWidth) * 0.5f;

    // Render "Sign-Up" button centered
    ImGui::SetCursorPosX(centeredX);
    m_uiData.signUpBtnPressed = ImGui::Button("Sign-Up", { buttonWidth, 30.0f });

    // Render "Sign-In" button centered
    ImGui::SetCursorPosX(centeredX);
    m_uiData.signInBtnPressed = ImGui::Button("Sign-In", { buttonWidth, 30.0f });

    ImGui::Text("Connection Type:");
    ImGui::End();
}

void LocalSessionModule::RenderSignInForm()
{
    // Rendering the Sign-In Form
}

void LocalSessionModule::RenderSignUpForm()
{
    // Renders the Sign-Up Form
}

void LocalSessionModule::OnShutdown()
{

}

} // ns tb::app::mods