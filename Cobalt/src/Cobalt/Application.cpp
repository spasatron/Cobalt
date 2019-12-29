#include "cbpc.h"
#include "Application.h"

#include <glad/glad.h>


namespace Cobalt {


//jsut sets the eventFunction to be whatever is passed in



	Application* Application::s_instance = nullptr;

	Application::Application() {

		COBALT_CORE_ASSERT(!s_instance, "One Application Already Exists");

		s_instance = this;
		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetEventCallback(COBALT_BIND_EVENT_FUNCTION(Application::OnEvent));
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
			glClearColor(0, .2, .8, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_layerStack)
				layer->OnUpdate();

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