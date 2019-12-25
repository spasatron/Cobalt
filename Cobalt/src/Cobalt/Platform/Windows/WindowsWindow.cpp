
#include "cbpc.h"
#include "WindowsWindow.h"

#include <glad/glad.h>

namespace Cobalt {

	static bool s_GLFWInitialized = false;

	//error callback just log it
	static void GLFWErrorCallback(int error, const char* desc) {
		COBALT_CORE_ERROR("GLFW Error ({0})::{1}", error, desc);
	}

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
			//set the error callback
			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;

		}

		m_window = glfwCreateWindow((int)prop.width, (int)prop.height, prop.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		//This initiallizes glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		COBALT_CORE_ASSERT(status, "FAILED TO INITIALIZE GLAD");

		glfwSetWindowUserPointer(m_window, &m_data);
		SetVSync(true);
		
		//set glfw callbacks
		//When a window resize event happens
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.EventCallBack(event);
			
		});
		//Window close event
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallBack(event);
		});
		//Key callbacks
		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			//<!--TO DO::Change keycodes to be our engine specific-->
			switch (action) {
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallBack(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallBack(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallBack(event);
					break;
				}
				}
		});
		//mouse button callback
		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods){
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallBack(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.EventCallBack(event);
					break;
				}
			}
		});
		//mouse scroll callback
		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallBack(event);
			
		});
		//Mouse moved callback
		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallBack(event);
		});
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