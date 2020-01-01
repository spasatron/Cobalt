#include "cbpc.h"
#include "ImGuiLayer.h"

#include "Cobalt/Application.h"

#include "imgui.h"
#include "GLFW/glfw3.h"
#include "Cobalt/Platform/OpenGL/ImGuiOpenGL.h"



namespace Cobalt {

	ImGuiLayer::ImGuiLayer() : Layer("ImGui Overlay") {}

	ImGuiLayer::~ImGuiLayer()
	{


	}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsClassic();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		//Set up keymaps for ImGui
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;


		//Initialization

		ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImGuiLayer::OnDetach()
	{


	}

	void ImGuiLayer::OnUpdate()
	{
		

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::GetApplication();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();

		io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
		m_time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		
		


		static bool show = true;

		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		EventDispatcher eventDispatcher(e);
		eventDispatcher.Dispatch<MouseButtonPressedEvent>(COBALT_BIND_EVENT_FUNCTION(ImGuiLayer::ImGuiOnMousePress));
		eventDispatcher.Dispatch<MouseMovedEvent>(COBALT_BIND_EVENT_FUNCTION(ImGuiLayer::ImGuiOnMouseMoved));
		eventDispatcher.Dispatch<MouseButtonReleasedEvent>(COBALT_BIND_EVENT_FUNCTION(ImGuiLayer::ImGuiOnMouseReleased));
		eventDispatcher.Dispatch<MouseScrolledEvent>(COBALT_BIND_EVENT_FUNCTION(ImGuiLayer::ImGuiOnMouseScroll));

	}
	bool ImGuiLayer::ImGuiOnMousePress(MouseButtonPressedEvent& e)
	{

		ImGuiIO& io = ImGui::GetIO();

		io.MouseDown[e.GetMouseButton()] = true;
		//COBALT_INFO("Clicked {}", e.GetMouseButton());

		return false;
	}
	bool ImGuiLayer::ImGuiOnMouseMoved(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());
		//COBALT_CORE_INFO("{0}, {1}", e.GetX(), e.GetY());

		return false;
	}
	bool ImGuiLayer::ImGuiOnMouseReleased(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.MouseDown[e.GetMouseButton()] = false;

		//COBALT_INFO("Released {}", e.GetMouseButton());

		return false;
	}
	bool ImGuiLayer::ImGuiOnMouseScroll(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.MouseWheel += e.GetYOffset();
		io.MouseWheelH += e.GetXOffset();

		return false;
	}
}


