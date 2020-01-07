#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Cobalt/ImGui/ImGuiLayer.h"

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

		inline static Application& GetApplication() { return *s_instance; }
		inline Window& GetWindow() { return *m_window;  }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_running = true;

		LayerStack m_layerStack;

		static Application* s_instance;

	};
	Application* CreateApplication();
}

