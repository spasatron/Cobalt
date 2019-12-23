#include "cbpc.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
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
		COBALT_CORE_INFO("{0}", e);
	}
	void Application::Run() {
		
		while (m_running) {
			glClearColor(.7, .5, .02, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->OnUpdate();
		}

	}
}