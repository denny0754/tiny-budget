/*
================================================================================
 CHANGE LOG
================================================================================
 Date       | Author        | Task ID       | Description
------------+---------------+---------------+-----------------------------------
 2026-11-10 | Diego Vaccher | UI-0000006-M  | Visualize Active Books on Side Menu
================================================================================
*/

#include <tb/ui/global/SideMenu.hpp>
#include <tb/events/ui/PushLocalComponentEvent.hpp>
#include <tb/ui/local/BookEditorDialog.hpp>
#include <tb/tools/Logging.hpp>

#include <imgui.h>

namespace tb::ui
{

void SideMenu::OnInit()
{

}

void SideMenu::OnRender()
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
            auto& activeBooks = GetSession()->GetService()->GetSessionContext()->ActiveBooks;
            for (const auto& book : activeBooks)
            {
                if (ImGui::Selectable(std::format("{}##{}", book.GetName(), book.GetGuid()).c_str(), false));
            }

            ImGui::Separator();
            if (ImGui::Selectable("Create New Book..."))
            {
                // Launching "FinancialBookSetup" Window
                GetEventDispatcher()->Enqueue<tb::events::PushLocalComponentEvent>(
                    std::make_unique<tb::events::PushLocalComponentEvent>(
                        [](tb::events::ConstEventDispatcherRef dispatcher, tb::core::ConstSessionRef session, std::unique_ptr<tb::ui::ComponentData> data) -> std::unique_ptr<tb::ui::BookEditorDialog> {
                            auto bookEditorData = std::make_unique<tb::ui::BookEditorData>(
                                tb::ui::EditorMode::New
                            );
                            tb::tools::log::GetCoreLogger()->debug("Creating instance of BookEditorDialog...");
                            bookEditorData->Mode = tb::ui::EditorMode::New;

                            return std::make_unique<tb::ui::BookEditorDialog>(
                                dispatcher,
                                session,
                                std::move(bookEditorData)
                            );
                        }
                    )
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

void SideMenu::OnUpdate()
{

}

void SideMenu::OnShutdown()
{

}

} // ns tb::ui