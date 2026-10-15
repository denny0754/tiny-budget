#include <tb/app/ui/MenuBar.hpp>

#include <imgui.h>

namespace tb::app::ui
{

void MenuBar::OnInit()
{

}

void MenuBar::OnRender()
{
    if (ImGui::BeginMainMenuBar())
    {
        // --- FILE MENU ---
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Transaction", "Ctrl+N")) {}
            if (ImGui::MenuItem("New Account")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Settings", "Ctrl+,")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Log Out")) {}
            if (ImGui::MenuItem("Exit", "Alt+F4")) {}
            ImGui::EndMenu();
        }

        // --- FINANCIAL BOOKS (Hardcoded Selection) ---
        if (ImGui::BeginMenu("Financial Books"))
        {
            ImGui::TextDisabled("Select Active Book:");
            ImGui::Separator();

            if (ImGui::MenuItem("Personal Budget", nullptr, true)) {}  // Currently selected
            if (ImGui::MenuItem("Business & Freelance", nullptr, false)) {}
            if (ImGui::MenuItem("Household / Family", nullptr, false)) {}

            ImGui::Separator();
            if (ImGui::MenuItem("Create New Book...")) {}
            if (ImGui::MenuItem("Manage Books...")) {}

            ImGui::EndMenu();
        }

        // --- EDIT MENU ---
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) {}
            if (ImGui::MenuItem("Redo", "Ctrl+Y")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "Ctrl+X")) {}
            if (ImGui::MenuItem("Copy", "Ctrl+C")) {}
            if (ImGui::MenuItem("Paste", "Ctrl+V")) {}
            ImGui::EndMenu();
        }

        // --- VIEW / WORKSPACE MENU ---
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Dashboard")) {}
            if (ImGui::MenuItem("Transactions List")) {}
            if (ImGui::MenuItem("Accounts & Payees")) {}
            if (ImGui::MenuItem("Budgets & Fiscal Periods")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Reset Layout")) {}
            ImGui::EndMenu();
        }

        // --- HELP MENU ---
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("Documentation")) {}
            if (ImGui::MenuItem("Check for Updates...")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("About TinyBudget")) {}
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
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