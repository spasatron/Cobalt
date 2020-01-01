#include "cbpc.h"
#include "WindowsInput.h"

#include "Cobalt/Application.h"
#include <GLFW/glfw3.h>




namespace Cobalt {

	Input* Input::s_instance = new WindowsInput();


	bool WindowsInput::IsKeyPressedImpl(int keyCode)
	{

		auto window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keyCode);
		//if it is either of these things the key is pressed
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int mouseButton)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, mouseButton);

		return state == GLFW_PRESS;
	}

	/*
		Returns the X position and then the Y position in the form of an std::pair<float,float>
	*/
	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
		double xPos, yPos;

		glfwGetCursorPos(window, &xPos, &yPos);

		return { (float)xPos, (float)yPos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();

		return y;
	}

}




