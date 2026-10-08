#include <tb/app/modules/Session.hpp>

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <imgui.h>

namespace tb::app::modules
{

void Session::OnInit()
{
    m_sessionCtx = std::make_shared<SessionContext>();

    // Initializing the default Application Logger:
    std::vector<spdlog::sink_ptr> logSinks;
    logSinks.push_back(
        std::make_shared<spdlog::sinks::rotating_file_sink_mt>("./logs/session.log", 52428800U, 7, false)
    );
    logSinks.push_back(
        std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
    );
    m_sessionCtx->logger = std::make_shared<spdlog::logger>("Session", begin(logSinks), end(logSinks));
    m_sessionCtx->logger->set_level(spdlog::level::level_enum::trace);
    m_sessionCtx->logger->set_pattern("[%Y-%m-%d %H:%M:%S] %n - %^%l%$: %v");
}

void Session::OnRender()
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

void Session::OnUpdate(double deltaTime)
{

}

void Session::OnShutdown()
{

}

} // ns tb::app::mods