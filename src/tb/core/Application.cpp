#include <tb/core/Application.hpp>

#include <tb/core/ev/MouseEvent.hpp>
#include <tb/core/ev/KeyboardEvent.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_opengl3_loader.h>

namespace tb::core
{

void Application::Init()
{
    m_eventBus = std::make_shared<ev::EventBus>();

    if(!glfwInit())
    {
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

    glfwSetWindowUserPointer(m_nativeWindow, this);

    glfwSetMouseButtonCallback(m_nativeWindow, [](GLFWwindow* window, int button, int action, int mods){
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        app->GetEventBus()->Push<ev::MouseEvent>(ev::MouseEvent(button, action, mods));
    });

    glfwSetKeyCallback(m_nativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        app->GetEventBus()->Push<ev::KeyboardEvent>(ev::KeyboardEvent(key, scancode, action, mods));
    });

    m_ready = true;
}

void Application::Run()
{
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while(m_ready)
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render and Update Modules

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

void Application::Shutdown()
{
    m_ready = false;
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