 #include <tb/core/Application.hpp>

#include <tb/core/ev/MouseEvent.hpp>
#include <tb/core/ev/KeyboardEvent.hpp>
#include <tb/core/ev/WindowResizeEvent.hpp>
#include <tb/core/ev/WindowCloseEvent.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace tb::core
{

void Application::Init()
{
    m_context = std::make_shared<tb::core::Context>();
    m_context->eventBus = std::make_shared<ev::EventBus>();

    // Initializing the default Application Logger:
    std::vector<spdlog::sink_ptr> logSinks;
    logSinks.push_back(
        std::make_shared<spdlog::sinks::rotating_file_sink_mt>("./logs/app.log", 52428800U, 7, false)
    );

    logSinks.push_back(
        std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
    );

    m_context->logger = std::make_shared<spdlog::logger>("TB", begin(logSinks), end(logSinks));

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
        app->GetContext()->eventBus->Push<ev::MouseEvent>(ev::MouseEvent(button, action, mods));
        app->GetContext()->logger->trace("Mouse Button Callback initialized succesfully!");
    });

    glfwSetKeyCallback(m_nativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        app->GetContext()->eventBus->Push<ev::KeyboardEvent>(ev::KeyboardEvent(key, scancode, action, mods));
        app->GetContext()->logger->trace("Keyboard Callback initialized succesfully!");
    });

    glfwSetWindowSizeCallback(m_nativeWindow, [](GLFWwindow* window, int width, int height){
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        app->GetContext()->eventBus->Push<ev::WindowResizeEvent>(ev::WindowResizeEvent(width,height));
        app->GetContext()->logger->trace("Window Resize Callback initialized succesfully!");
    });

    glfwSetWindowCloseCallback(m_nativeWindow, [](GLFWwindow* window){                                                                                                                                                                                  
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        app->GetContext()->eventBus->Push<ev::WindowCloseEvent>(ev::WindowCloseEvent());
        app->GetContext()->logger->trace("Window Close Callback initialized succesfully!");
    });

    m_context->eventBus->Subscribe<ev::PushModuleEvent>(TB_BIND_EVENT_FN(OnPushModule));
    m_context->eventBus->Subscribe<ev::PopModuleEvent>(TB_BIND_EVENT_FN(OnPopModule));
    m_context->eventBus->Subscribe<ev::WindowCloseEvent>(TB_BIND_EVENT_FN(OnShutdown));

    if(BaseInit())
    {
        m_context->logger->info("Application succesfully initialized...Setting status to ready!");
        m_ready = true;
    }
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

void Application::PushModule(std::shared_ptr<mod::Module> module)
{
    module->BindContext(m_context);
    module->OnInit();
    m_modules.push_back(module);
}

void Application::OnPopModule(const ev::PopModuleEvent& event)
{
    m_pendingRemovalModules.push_back(event.TargetModule);
    event.Handled = true;
}

void Application::OnPushModule(const ev::PushModuleEvent& event)
{
    m_pendingModules.push_back(event.NewModule);
    event.Handled = true;
}

void Application::OnShutdown(const ev::WindowCloseEvent& event)
{
    m_ready = false;
}

void Application::Shutdown()
{
    m_ready = false;
}

std::shared_ptr<tb::core::Context> Application::GetContext()
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