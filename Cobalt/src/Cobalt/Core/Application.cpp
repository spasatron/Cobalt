#include "cbpc.h"
#include "Application.h"

#include "Cobalt/Core/Input.h"
#include "Cobalt/Renderer/Renderer.h"
#include "Cobalt/Core/KeyCodes.h"
#include "Cobalt/ImGui/ImGuiLayer.h"

#include <GLFW/glfw3.h>

namespace Cobalt {


//jsut sets the eventFunction to be whatever is passed in


	Application* Application::s_instance = nullptr;


	

	Application::Application(){

		COBALT_CORE_ASSERT(!s_instance, "One Application Already Exists");

		s_instance = this;
		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetEventCallback(COBALT_BIND_EVENT_FUNCTION(Application::OnEvent));


		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);


	}
	Application::~Application() {

	}
	void Application::OnEvent(Event& e) {

		EventDispatcher eventDispatcher(e);
		eventDispatcher.Dispatch<WindowCloseEvent>(COBALT_BIND_EVENT_FUNCTION(Application::OnWindowClose));
		eventDispatcher.Dispatch<WindowResizeEvent>(COBALT_BIND_EVENT_FUNCTION(Application::OnWindowResize));
		//COBALT_CORE_TRACE("{0}", e);

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();) {
			(*(--it))->OnEvent(e);
			if (e.m_Handled) {
				break;
			}
		}


	}
	

	void Application::Run() {
		
		while (m_running) {

			//Renderer::Flush()

			float time = (float)glfwGetTime(); //Needs to be platform independant
			TimeStep timeStep = time - m_lastFrameTime;
			m_lastFrameTime = time;


			if (!m_minimized) {

				for (Layer* layer : m_layerStack)
					layer->OnUpdate(timeStep);
			}
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_layerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
			//Input is now working
			//COBALT_CORE_INFO("{0}", Input::IsKeyPressed(65));
			m_window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		if (e.GetHeight() == 0 || e.GetWidth() == 0) {
			m_minimized = true;
		}
		m_minimized = false;

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}


	void Application::PushLayer(Layer* layer) {
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		m_layerStack.PushOverlay(overlay);
		overlay->OnAttach(); 
	}

}