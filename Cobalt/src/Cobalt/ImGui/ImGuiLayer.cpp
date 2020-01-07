#include "cbpc.h"
#include "ImGuiLayer.h"

#include "Cobalt/Application.h"

#include "imgui.h"
#include "GLFW/glfw3.h"


#include "examples/imgui_impl_opengl3.h"
#include "examples/imgui_impl_glfw.h"


namespace Cobalt {

	ImGuiLayer::ImGuiLayer() : Layer("ImGui Overlay") {}

	ImGuiLayer::~ImGuiLayer()
	{


	}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; //  Keyboard Control
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; //Enable docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; //Enable viewports
		//
		ImGui::StyleColorsClassic();

		ImGuiStyle& style = ImGui::GetStyle();
		//Set up some stuff if viewport is enabled
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::GetApplication();

		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin(){
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		
		ImGui::NewFrame();
	}

	void ImGuiLayer::End(){
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::GetApplication();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
		//render
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//check to see if viewports are enabled
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* back_up_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(back_up_context);
		}



	}
	//Render is the function you will use in order to create a context
	void ImGuiLayer::OnImGuiRender() {
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}


}


