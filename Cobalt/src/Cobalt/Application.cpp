#include "cbpc.h"
#include "Application.h"

#include "Cobalt/Input.h"
#include "Cobalt/Renderer/Renderer.h"
#include "Cobalt/KeyCodes.h"
#include "Cobalt/ImGui/ImGuiLayer.h"

namespace Cobalt {


//jsut sets the eventFunction to be whatever is passed in


	Application* Application::s_instance = nullptr;


	

	Application::Application(){

		COBALT_CORE_ASSERT(!s_instance, "One Application Already Exists");

		s_instance = this;
		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetEventCallback(COBALT_BIND_EVENT_FUNCTION(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);


	}
	Application::~Application() {

	}
	void Application::OnEvent(Event& e) {

		EventDispatcher eventDispatcher(e);
		eventDispatcher.Dispatch<WindowCloseEvent>(COBALT_BIND_EVENT_FUNCTION(Application::OnWindowClose));
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

		

			for (Layer* layer : m_layerStack)
				layer->OnUpdate();

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


	void Application::PushLayer(Layer* layer) {
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		m_layerStack.PushOverlay(overlay);
		overlay->OnAttach(); 
	}

}