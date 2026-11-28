#include "ui/ViewManager.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace tb::ui
{

ViewManager::ViewManager(
	const tb::ui::SystemStore& sys_store, const tb::ui::UserStore& usr_store,
	const tb::ui::ViewContext& view_context = { 1280, 720, "Tiny-Budget" }
)
{
	if (!glfwInit())
	{
		//TODO: Implement logging and error management
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	float mainScale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
	m_nativeWindow = glfwCreateWindow(
		(int)(view_context.width * mainScale),
		(int)(view_context.height * mainScale),
		view_context.title.c_str(),
		nullptr,
		nullptr
	);

	if (m_nativeWindow == nullptr)
	{
		//TODO: Implement logging and error management
	}

	glfwMakeContextCurrent(m_nativeWindow);
	glfwSwapInterval(1);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(mainScale);
	style.FontScaleDpi = mainScale;

	ImGui_ImplGlfw_InitForOpenGL(m_nativeWindow, true);
	ImGui_ImplOpenGL3_Init(nullptr);

	glfwSetWindowUserPointer(m_nativeWindow, this);
}

bool ViewManager::ShouldClose()
{

}

void ViewManager::PollEvents()
{
	glfwPollEvents();
}

void ViewManager::Update()
{

}

void ViewManager::Render()
{
	static auto clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ApplyCustomTheme();

	ImGui::Render();
	int displayWidth;
	int displayHeight;
	glfwGetFramebufferSize(m_nativeWindow, &display_w, &display_h);
	glViewport(0, 0, displayWidth, displayHeight);
	glClearColor(clearColor.x * clearColor.w, clearColor.y * clearColor.w, clearColor.z * clearColor.w, clearColor.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(m_nativeWindow);
}


ViewManager::~ViewManager()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_nativeWindow);
	glfwTerminate();
	m_nativeWindow = nullptr;
}

} // ns tb::ui