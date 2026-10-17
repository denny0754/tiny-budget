#include <tb/app/ui/AuthenticationForm.hpp>
#include <tb/app/events/IdentitySignedInEvent.hpp>

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
    ImGui::RadioButton("Local", &m_sessionTypeInt, 0);
    ImGui::SameLine();
    ImGui::RadioButton("Remote", &m_sessionTypeInt, 1);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // Display error feedback banner if any API operation failed
    if (!m_errorMessage.empty())
    {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
        ImGui::TextWrapped("%s", m_errorMessage.c_str());
        ImGui::PopStyleColor();
        ImGui::Spacing();
    }

    // --- FORM MODE TABS (Sign-In / Sign-Up) ---
    if (ImGui::BeginTabBar("AuthTabBar"))
    {
        // ==================== SIGN-IN TAB ====================
        if (ImGui::BeginTabItem("Sign-In"))
        {
            m_isSignUpMode = false;
            ImGui::Spacing();

            ImGui::InputText("Email", m_emailBuf, sizeof(m_emailBuf));
            ImGui::InputText("Password", m_passwordBuf, sizeof(m_passwordBuf), ImGuiInputTextFlags_Password);

            ImGui::Spacing();

            // Disable button during pending async requests
            if (m_isProcessing) ImGui::BeginDisabled();

            if (ImGui::Button("Sign-In", { fullWidth, 32.0f }))
            {
                m_errorMessage.clear();

                // Basic client-side validation
                if (std::strlen(m_emailBuf) == 0 || std::strlen(m_passwordBuf) == 0)
                {
                    m_errorMessage = "Please enter both email and password.";
                }
                else
                {
                    m_isProcessing = true;

                    models::dto::SignInRequest request;
                    request.Email = m_emailBuf;
                    request.Password = m_passwordBuf;

                    GetSessionContext()->apiProvider->SignIn(
                        request,
                        [this](const models::dto::APIResult<models::dto::SignInResponse>& result) {
                            m_isProcessing = false;

                            if (result.Success)
                            {
                                // Notify application about successful login
                                GetSessionContext()->eventDispatcher->QueueEvent(
                                    events::IdentitySignedInEvent{
                                        result.Result.IdentityId,
                                        result.Result.Email,
                                        result.Result.FirstName,
                                        result.Result.LastName
                                    }
                                );

                                // Close authentication window
                                Close();
                            }
                            else
                            {
                                m_errorMessage = result.ErrorMessage.empty()
                                    ? "Invalid email or password."
                                    : result.ErrorMessage;
                            }
                        }
                    );
                }
            }

            if (m_isProcessing) ImGui::EndDisabled();

            ImGui::EndTabItem();
        }

        // ==================== SIGN-UP TAB ====================
        if (ImGui::BeginTabItem("Sign-Up"))
        {
            m_isSignUpMode = true;
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

            if (m_isProcessing) ImGui::BeginDisabled();

            if (ImGui::Button("Sign-Up", { fullWidth, 32.0f }))
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

                    models::dto::SignUpRequest request;
                    request.FirstName = m_firstNameBuf;
                    request.LastName = m_lastNameBuf;
                    request.Email = m_emailBuf;
                    request.Password = m_passwordBuf;

                    GetSessionContext()->apiProvider->SignUp(
                        request,
                        [this](const models::dto::APIResult<models::dto::SignUpResponse>& result) {
                            m_isProcessing = false;

                            if (result.Success)
                            {
                                // 1. Set temporary success message
                                m_successMessage = "Sign up successful! Please switch to Sign-In to log in.";

                                // 2. Clear sensitive input fields
                                m_passwordBuf[0] = '\0';
                                m_firstNameBuf[0] = '\0';
                                m_lastNameBuf[0] = '\0';

                                // NOTE: Window remains OPEN and UserAuthenticatedEvent is NOT dispatched.
                            }
                            else
                            {
                                m_errorMessage = result.ErrorMessage.empty()
                                    ? "Sign-Up failed. Please check your data."
                                    : result.ErrorMessage;
                            }
                        }
                    );
                }
            }

            if (m_isProcessing) ImGui::EndDisabled();

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