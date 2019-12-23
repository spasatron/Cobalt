#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace Cobalt {
	class COBALT_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_window;
		bool m_running = true;
	};
	Application* CreateApplication();
}

