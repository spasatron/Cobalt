#include "cbpc.h"


#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>



namespace Cobalt {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_windowHandle(windowHandle){
		COBALT_CORE_ASSERT(windowHandle, "The Window Hander is Null!");
	}

	void OpenGLContext::Init(){
		glfwMakeContextCurrent(m_windowHandle);
		//This initiallizes glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		COBALT_CORE_ASSERT(status, "FAILED TO INITIALIZE GLAD");
	}

	void OpenGLContext::SwapBuffers(){
		glfwSwapBuffers(m_windowHandle);
	}


}