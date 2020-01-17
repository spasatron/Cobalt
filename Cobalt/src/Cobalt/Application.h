#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Cobalt/ImGui/ImGuiLayer.h"

#include "Cobalt/Renderer/Shader.h"
#include "Cobalt/Renderer/Buffer.h"
#include "Cobalt/Renderer/VertexArray.h"

#include "Cobalt/Core/TimeStep.h"

#include "Cobalt/Renderer/OrthographicCamera.h"

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
	private:
		std::unique_ptr<Window> m_window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_running = true;

		float m_lastFrameTime = 0.0f;
		

		LayerStack m_layerStack;

		static Application* s_instance;

		//Rendering a triangle, temporary
		

	};
	Application* CreateApplication();
}

