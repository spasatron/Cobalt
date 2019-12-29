#pragma once

#include "Cobalt/Window.h"

#include <GLFW/glfw3.h>

namespace Cobalt {


	class WindowsWindow : public Window{
	public:
		WindowsWindow(const WindowProp& prop);
		virtual ~WindowsWindow();
		
		void OnUpdate() override;


		inline unsigned int GetWidth() const override { return m_data.width; }
		inline unsigned int GetHeight() const override { return m_data.height; }


		inline void SetEventCallback(const EventCallBackFunc& callback) override { m_data.EventCallBack = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;


	private:

		virtual void Init(const WindowProp& prop);
		virtual void Shutdown();


		GLFWwindow* m_window;

		struct WindowData {
			std::string title;
			unsigned int width, height;
			bool vSync;

			EventCallBackFunc EventCallBack;
		};
		WindowData m_data;
	};

}