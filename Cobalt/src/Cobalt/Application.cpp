#include "cbpc.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include <GLFW/glfw3.h>


namespace Cobalt {

	Application::Application() {
		m_window = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application() {

	}
	void Application::Run() {
		
		while (m_running) {
			glClearColor(.7, .5, .02, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->OnUpdate();
		}

	}
}