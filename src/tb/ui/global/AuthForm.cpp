/*
================================================================================
 CHANGE LOG
================================================================================
 Date       | Author        | Task ID       | Description
------------+---------------+---------------+-----------------------------------
 2026-11-10 | Diego Vaccher | UI-0000002-M  | UI API calls refactor
================================================================================
*/

#include <tb/ui/global/AuthForm.hpp>
#include <tb/api/AuthClient.hpp>
#include <tb/models/dto/Common.hpp>
#include <tb/models/dto/Auth.hpp>
#include <tb/events/session/IdentitySignedInEvent.hpp>

#include <imgui.h>

#include <thread>

namespace tb::ui
{

void AuthForm::OnInit()
{

}

void AuthForm::OnRender()
{
    // START-REFACTOR
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 centerPos{ io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f };
    ImGui::SetNextWindowPos(centerPos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize({ 480.0f, 0.0f }, ImGuiCond_Always);

    ImGui::Begin(
        "Sign-In/Sign-Up",
        nullptr,
        ImGuiWindowFlags_::ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoMove
    );

    if (ImGui::BeginTabBar("AUTH_TAB_BAR"))
    {
        RenderSignInForm();
        RenderSignUpForm();
        ImGui::EndTabBar();
    }

    // Display error feedback banner if any API operation failed
    if (!m_errorMessage.empty())
    {
        ImGui::Separator();
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
        ImGui::TextWrapped("%s", m_errorMessage.c_str());
        ImGui::PopStyleColor();
        ImGui::Spacing();
    }

    ImGui::End();
}

void AuthForm::OnUpdate()
{

}

void AuthForm::OnShutdown()
{

}

void AuthForm::RenderSignInForm()
{
    float localWindowWidth = ImGui::GetContentRegionAvail().x;

    // Sign-In Form Tab
    if (ImGui::BeginTabItem("Sign-In"))
    {
        ImGui::BeginDisabled(m_isProcessing);

        ImGui::Spacing();

        ImGui::InputText("Email", m_emailBuf, sizeof(m_emailBuf));
        ImGui::InputText("Password", m_passwordBuf, sizeof(m_passwordBuf), ImGuiInputTextFlags_::ImGuiInputTextFlags_Password);

        ImGui::Spacing();

        if (ImGui::Button("Sign-In", ImVec2(localWindowWidth, 32.f)))
        {
            if (std::strlen(m_emailBuf) == 0 || std::strlen(m_passwordBuf) == 0)
            {
                m_errorMessage = "Please enter email and password.";
            }
            else
            {
                m_isProcessing = true;

                std::thread(
                    [this]() {
                        tb::models::dto::SignInRequest requestData{};
                        requestData.Email = m_emailBuf;
                        requestData.Password = m_passwordBuf;

                        auto response = GetSession()->GetService()->GetClient<tb::api::AuthClient>()->SignIn(
                            requestData
                        );

                        // Removing local password data from memory.
                        std::memset(m_passwordBuf, 0, sizeof(m_passwordBuf));

                        if (response.Ok())
                        {
                            auto responseData = response.GetData();
                            if (responseData.size() == 1)
                            {
                                auto userData = responseData[0];
                                //TODO: Dipatch `IdentitySignInEvent`
                                GetEventDispatcher()->Enqueue(
                                    std::make_unique<tb::events::IdentitySignedInEvent>(
                                        userData.IdentityGuid,
                                        userData.Email,
                                        "",
                                        ""
                                    )
                                );
                                Close();
                            }
                        }
                        else
                        {
                            //TODO: Parse API error and set m_errorMessage based on it.
                        }

                        m_isProcessing = false;
                    }
                ).detach();
            }
        }

        ImGui::EndDisabled();
        ImGui::EndTabItem();
    }
}

void AuthForm::RenderSignUpForm()
{
    float localWindowWidth = ImGui::GetContentRegionAvail().x;

    // Sign-Up Form Tab
    if (ImGui::BeginTabItem("Sign-Up"))
    {
        ImGui::Spacing();

        // Render success feedback banner in green
        if (!m_successMessage.empty())
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.3f, 0.9f, 0.3f, 1.0f));
            ImGui::TextWrapped("%s", m_successMessage.c_str());
            ImGui::PopStyleColor();
            ImGui::Spacing();
        }

        ImGui::InputText("First Name", m_firstNameBuf, sizeof(m_firstNameBuf));
        ImGui::InputText("Last Name", m_lastNameBuf, sizeof(m_lastNameBuf));
        ImGui::InputText("Email", m_emailBuf, sizeof(m_emailBuf));
        ImGui::InputText("Password", m_passwordBuf, sizeof(m_passwordBuf), ImGuiInputTextFlags_Password);

        ImGui::Spacing();

        ImGui::BeginDisabled(m_isProcessing);

        if (ImGui::Button("Sign-Up", { localWindowWidth, 32.0f }))
        {
            m_errorMessage.clear();
            m_successMessage.clear();

            // Basic client-side validation
            if (std::strlen(m_emailBuf) == 0 || std::strlen(m_passwordBuf) == 0 ||
                std::strlen(m_firstNameBuf) == 0 || std::strlen(m_lastNameBuf) == 0)
            {
                m_errorMessage = "Please fill in all required fields.";
            }
            else
            {
                m_isProcessing = true;

                std::thread(
                    [this]() {
                        models::dto::SignUpRequest requestData;
                        requestData.FirstName = m_firstNameBuf;
                        requestData.LastName = m_lastNameBuf;
                        requestData.Email = m_emailBuf;
                        requestData.Password = m_passwordBuf;

                        auto response = GetSession()->GetService()->GetClient<tb::api::AuthClient>()->SignUp(
                            requestData
                        );

                        if (response.Ok())
                        {
                            std::memset(m_firstNameBuf, 0, sizeof(m_firstNameBuf));
                            std::memset(m_lastNameBuf, 0, sizeof(m_lastNameBuf));
                            std::memset(m_passwordBuf, 0, sizeof(m_passwordBuf));
                            //TODO: Dipatch `IdentitySignInEvent`
                        }
                        else
                        {
                            //TODO: Parse API error and set m_errorMessage based on it.
                        }
                        
                        m_isProcessing = false;

                    }
                ).detach();
            }
        }

        ImGui::EndDisabled();
        ImGui::EndTabItem();
    }
}

} // ns tb::ui