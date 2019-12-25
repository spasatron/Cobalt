#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"

namespace Cobalt {
	class COBALT_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* Overlay);


	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_window;
		bool m_running = true;

		LayerStack m_layerStack;

	};
	Application* CreateApplication();
}

