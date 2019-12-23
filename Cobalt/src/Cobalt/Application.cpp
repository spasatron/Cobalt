#include "cbpc.h"
#include "Application.h"

#include <GLFW/glfw3.h>


namespace Cobalt {


//jsut sets the eventFunction to be whatever is passed in

#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application() {
		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));
	}
	Application::~Application() {

	}
	void Application::OnEvent(Event& e) {

		EventDispatcher eventDispatcher(e);
		eventDispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(Application::OnWindowClose));


		COBALT_CORE_TRACE("{0}", e);
	}
	

	void Application::Run() {
		
		while (m_running) {
			glClearColor(.7, .5, .02, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->OnUpdate();
		}

	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_running = false;
		return true;
	}
}