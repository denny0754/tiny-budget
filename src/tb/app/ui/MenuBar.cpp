#include <tb/app/ui/MenuBar.hpp>
#include <tb/app/events/PushLocalComponentEvent.hpp>
#include <tb/app/ui/FinancialBookSetup.hpp>

#include <imgui.h>

namespace tb::app::ui
{

void MenuBar::OnInit()
{

}

void MenuBar::OnRender()
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const float sidebarWidth = 240.0f;

    // Pin the sidebar to the left edge of the main viewport
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(ImVec2(sidebarWidth, viewport->WorkSize.y));

    ImGuiWindowFlags sidebarFlags = ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoBringToFrontOnFocus;

    if (ImGui::Begin("SidebarNav", nullptr, sidebarFlags))
    {
        ImGui::TextDisabled("TINYBUDGET MENU");
        ImGui::Separator();
        ImGui::Spacing();

        // --- FILE SECTION ---
        if (ImGui::CollapsingHeader("File"))
        {
            if (ImGui::Selectable("New Transaction\tCtrl+N")) {}
            if (ImGui::Selectable("New Account")) {}
            ImGui::Separator();
            if (ImGui::Selectable("Settings\tCtrl+,")) {}
            ImGui::Separator();
            if (ImGui::Selectable("Log Out")) {}
            if (ImGui::Selectable("Exit\tAlt+F4")) {}
            ImGui::Spacing();
        }

        // --- FINANCIAL BOOKS SECTION ---
        if (ImGui::CollapsingHeader("Financial Books", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::TextDisabled(" Active Book:");

            // Radio/Selection style for active book
            if (ImGui::Selectable("  [x] Personal Budget")) {}
            if (ImGui::Selectable("  [ ] Business & Freelance")) {}
            if (ImGui::Selectable("  [ ] Household / Family")) {}

            ImGui::Separator();
            if (ImGui::Selectable("Create New Book..."))
            {
                // Launching "FinancialBookSetup" Window
                GetSessionContext()->eventDispatcher->QueueEvent<tb::app::events::PushLocalComponentEvent>(
                    tb::app::events::PushLocalComponentEvent(
                        []() -> std::unique_ptr<tb::app::ui::FinancialBookSetup>
                        {
                            return std::make_unique<tb::app::ui::FinancialBookSetup>();
                        })
                );
            }

            if (ImGui::Selectable("Manage Books...")) {}
            ImGui::Spacing();
        }

        // --- EDIT SECTION ---
        if (ImGui::CollapsingHeader("Edit"))
        {
            if (ImGui::Selectable("Undo\tCtrl+Z")) {}
            if (ImGui::Selectable("Redo\tCtrl+Y")) {}
            ImGui::Separator();
            if (ImGui::Selectable("Cut\tCtrl+X")) {}
            if (ImGui::Selectable("Copy\tCtrl+C")) {}
            if (ImGui::Selectable("Paste\tCtrl+V")) {}
            ImGui::Spacing();
        }

        // --- VIEW / WORKSPACE SECTION ---
        if (ImGui::CollapsingHeader("View", ImGuiTreeNodeFlags_DefaultOpen))
        {
            if (ImGui::Selectable("Dashboard")) {}
            if (ImGui::Selectable("Transactions List")) {}
            if (ImGui::Selectable("Accounts & Payees")) {}
            if (ImGui::Selectable("Budgets & Fiscal Periods")) {}
            ImGui::Separator();
            if (ImGui::Selectable("Reset Layout")) {}
            ImGui::Spacing();
        }

        // --- HELP SECTION ---
        if (ImGui::CollapsingHeader("Help"))
        {
            if (ImGui::Selectable("Documentation")) {}
            if (ImGui::Selectable("Check for Updates...")) {}
            ImGui::Separator();
            if (ImGui::Selectable("About TinyBudget")) {}
            ImGui::Spacing();
        }

        ImGui::End();
    }
}

void MenuBar::OnUpdate(double deltaTime)
{

}

void MenuBar::OnShutdown()
{

}

std::string MenuBar::GetComponentId() const
{
    return "MenuBar";
}

} // ns tb::app::ui