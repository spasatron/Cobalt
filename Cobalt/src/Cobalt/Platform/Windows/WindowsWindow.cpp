
#include "cbpc.h"
#include "WindowsWindow.h"



namespace Cobalt {

	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProp& prop) {
		return new WindowsWindow(prop);
	}

	WindowsWindow::WindowsWindow(const WindowProp& prop) {
		Init(prop);
	}
	WindowsWindow::~WindowsWindow() {

	}
	
	void WindowsWindow::Init(const WindowProp& prop) {
		m_data.title = prop.title;
		m_data.width = prop.width;
		m_data.height = prop.height;

		COBALT_CORE_INFO("Creating Window {0} ({1} {2})", prop.title, prop.width, prop.height);

		if (!s_GLFWInitialized) {

			int success = glfwInit();

			COBALT_CORE_ASSERT(success, "Could not initiallize GLFW");
			s_GLFWInitialized = true;

		}

		m_window = glfwCreateWindow((int)prop.width, (int)prop.height, prop.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		SetVSync(true);


	}


	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_window);
	}


	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void WindowsWindow::SetVSync(bool enabled) {
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_data.vSync = enabled;
	}
	
	bool WindowsWindow::IsVSync() const {
		return m_data.vSync;
	}

}