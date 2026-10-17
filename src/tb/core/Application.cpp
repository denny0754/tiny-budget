 #include <tb/core/Application.hpp>

#include <tb/core/events/MouseEvent.hpp>
#include <tb/core/events/KeyboardEvent.hpp>
#include <tb/core/events/WindowResizeEvent.hpp>
#include <tb/core/events/WindowCloseEvent.hpp>
#include <tb/app/modules/Session.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace tb::core
{

void ApplyCustomTheme()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // --- 1. SIZES, PADDING & ROUNDING ---
    style.WindowRounding = 10.0f; // Smooth window edges
    style.ChildRounding = 8.0f;
    style.FrameRounding = 6.0f;  // Modern rounded inputs and buttons
    style.PopupRounding = 8.0f;
    style.ScrollbarRounding = 12.0f;
    style.GrabRounding = 4.0f;
    style.TabRounding = 6.0f;

    style.WindowPadding = ImVec2(14.0f, 14.0f);
    style.FramePadding = ImVec2(10.0f, 6.0f);
    style.ItemSpacing = ImVec2(10.0f, 8.0f);
    style.ItemInnerSpacing = ImVec2(6.0f, 6.0f);
    style.ScrollbarSize = 12.0f;
    style.GrabMinSize = 12.0f;

    style.WindowBorderSize = 1.0f;  // Subtle 1px outline for modern dark themes
    style.ChildBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.TabBorderSize = 0.0f;

    // --- 2. COLOR PALETTE (Modern Slate & Emerald Accent) ---

    // Backgrounds
    colors[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.08f, 0.10f, 1.00f); // #12141A Deep Slate
    colors[ImGuiCol_ChildBg] = ImVec4(0.09f, 0.10f, 0.13f, 1.00f); // #171A21
    colors[ImGuiCol_PopupBg] = ImVec4(0.09f, 0.10f, 0.13f, 0.98f);

    // Borders
    colors[ImGuiCol_Border] = ImVec4(0.16f, 0.18f, 0.22f, 1.00f); // Low contrast border
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    // Text
    colors[ImGuiCol_Text] = ImVec4(0.92f, 0.93f, 0.95f, 1.00f); // High contrast soft white
    colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.43f, 0.48f, 1.00f);

    // Frame Backgrounds (Text inputs, checkboxes, combos)
    colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.14f, 0.18f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.16f, 0.18f, 0.24f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.30f, 1.00f);

    // Headers & Tree Nodes
    colors[ImGuiCol_Header] = ImVec4(0.14f, 0.16f, 0.20f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.18f, 0.21f, 0.27f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.22f, 0.26f, 0.34f, 1.00f);

    // Primary Buttons
    colors[ImGuiCol_Button] = ImVec4(0.13f, 0.40f, 0.28f, 1.00f); // Emerald Accent
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.16f, 0.50f, 0.35f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.60f, 0.42f, 1.00f);

    // Sliders, Checkmarks & Active Controls
    colors[ImGuiCol_CheckMark] = ImVec4(0.22f, 0.82f, 0.52f, 1.00f); // Vibrant Mint
    colors[ImGuiCol_SliderGrab] = ImVec4(0.22f, 0.82f, 0.52f, 0.80f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.22f, 0.82f, 0.52f, 1.00f);

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4(0.10f, 0.11f, 0.15f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.18f, 0.21f, 0.27f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.14f, 0.16f, 0.21f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.09f, 0.12f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.12f, 0.14f, 0.18f, 1.00f);

    // Title Bars & Menus
    colors[ImGuiCol_TitleBg] = ImVec4(0.07f, 0.08f, 0.10f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.09f, 0.10f, 0.13f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.07f, 0.08f, 0.10f, 0.75f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.09f, 0.10f, 0.13f, 1.00f);

    // Scrollbars
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.07f, 0.08f, 0.10f, 0.50f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.18f, 0.20f, 0.25f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.25f, 0.28f, 0.35f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.30f, 0.34f, 0.42f, 1.00f);

    // Miscellaneous
    colors[ImGuiCol_Separator] = ImVec4(0.16f, 0.18f, 0.22f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.22f, 0.82f, 0.52f, 0.78f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.22f, 0.82f, 0.52f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.22f, 0.82f, 0.52f, 0.25f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.22f, 0.82f, 0.52f, 1.00f);
}


void Application::Init()
{
    m_context = std::make_shared<tb::core::AppContext>();
    m_context->eventBus = std::make_shared<EventBus>();

    // Initializing the default Application Logger:
    std::vector<spdlog::sink_ptr> logSinks;
    logSinks.push_back(
        std::make_shared<spdlog::sinks::rotating_file_sink_mt>("./logs/app.log", 52428800U, 7, false)
    );
    logSinks.push_back(
        std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
    );
    m_context->logger = std::make_shared<spdlog::logger>("Core", begin(logSinks), end(logSinks));
    m_context->logger->set_level(spdlog::level::level_enum::trace);
    m_context->logger->set_pattern("[%Y-%m-%d %H:%M:%S] %n - %^%l%$: %v");

    if(!glfwInit())
    {
        m_context->logger->critical("An error occured while trying to initialize GLFW...");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
    m_nativeWindow = glfwCreateWindow((int)(1280 * main_scale), (int)(800 * main_scale), "tiny-budget", nullptr, nullptr);

    if(m_nativeWindow == nullptr)
    {
        return;
    }

    glfwMakeContextCurrent(m_nativeWindow);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    
    ImGui::StyleColorsDark();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    style.FontScaleDpi = main_scale;        // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_nativeWindow, true);
    ImGui_ImplOpenGL3_Init(nullptr);

    glfwSetWindowUserPointer(m_nativeWindow, this);

    glfwSetMouseButtonCallback(m_nativeWindow, [](GLFWwindow* window, int button, int action, int mods){
        ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        app->GetContext()->eventBus->Push<events::MouseEvent>(events::MouseEvent(button, action, mods));
        //app->GetContext()->logger->trace("Mouse Button Callback initialized succesfully!");
    });

    glfwSetKeyCallback(m_nativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        app->GetContext()->eventBus->Push<events::KeyboardEvent>(events::KeyboardEvent(key, scancode, action, mods));
        //app->GetContext()->logger->trace("Keyboard Callback initialized succesfully!");
    });

    glfwSetWindowSizeCallback(m_nativeWindow, [](GLFWwindow* window, int width, int height){
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        app->GetContext()->eventBus->Push<events::WindowResizeEvent>(events::WindowResizeEvent(width,height));
        //app->GetContext()->logger->trace("Window Resize Callback initialized succesfully!");
    });

    glfwSetWindowCloseCallback(m_nativeWindow, [](GLFWwindow* window){                                                                                                                                                                                  
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        app->GetContext()->eventBus->Push<events::WindowCloseEvent>(events::WindowCloseEvent());
        //app->GetContext()->logger->trace("Window Close Callback initialized succesfully!");
    });

    m_context->eventBus->Subscribe<events::PushModuleEvent>(TB_BIND_EVENT_FN(OnPushModule));
    m_context->eventBus->Subscribe<events::PopModuleEvent>(TB_BIND_EVENT_FN(OnPopModule));
    m_context->eventBus->Subscribe<events::WindowCloseEvent>(TB_BIND_EVENT_FN(OnShutdown));

    PushModule(std::make_shared<tb::app::modules::Session>());

    m_context->logger->info("Application succesfully initialized...Setting status to ready!");
    m_ready = true;
}

void Application::Run()
{
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while(m_ready)
    {
        if (!m_pendingRemovalModules.empty())
        {
            for (auto& modToRem : m_pendingRemovalModules)
            {
                // Trigger user shutdown sequence
                modToRem->OnShutdown();

                // Erase from active vector. Dropping the shared_ptr ref count 
                // triggers the destructor, automatically running unsubscription lambdas.
                auto it = std::find(m_modules.begin(), m_modules.end(), modToRem);
                if (it != m_modules.end()) {
                    m_modules.erase(it);
                }
            }
            m_pendingRemovalModules.clear();
        }

        if (!m_pendingModules.empty())
        {
            for (auto& modToAdd : m_pendingModules)
            {
                modToAdd->BindContext(m_context);
                modToAdd->OnInit();
                m_modules.push_back(modToAdd);
            }
            m_pendingModules.clear();
        }

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Rendering modules
        for(auto& module : m_modules)
        {
            module->OnRender();
        }

        ApplyCustomTheme();

        // Updating modules
        for(auto& module : m_modules)
        {
            module->OnUpdate();
        }

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(m_nativeWindow, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_nativeWindow);
    }
}

void Application::PushModule(std::shared_ptr<BaseModule> module)
{
    module->BindContext(m_context);
    module->OnInit();
    m_modules.push_back(module);
}

void Application::OnPopModule(const events::PopModuleEvent& event)
{
    m_pendingRemovalModules.push_back(event.TargetModule);
    event.Handled = true;
}

void Application::OnPushModule(const events::PushModuleEvent& event)
{
    m_pendingModules.push_back(event.NewModule);
    event.Handled = true;
}

void Application::OnShutdown(const events::WindowCloseEvent& event)
{
    m_ready = false;
}

void Application::Shutdown()
{
    m_ready = false;
}

std::shared_ptr<tb::core::AppContext> Application::GetContext()
{
    return m_context;
}

Application::~Application()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_nativeWindow);
    glfwTerminate();
    m_nativeWindow = nullptr;
}

} // ns tb::core