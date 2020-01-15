#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Cobalt/ImGui/ImGuiLayer.h"

#include "Cobalt/Renderer/Shader.h"
#include "Cobalt/Renderer/Buffer.h"
#include "Cobalt/Renderer/VertexArray.h"

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

		std::shared_ptr<Shader> m_shader;
		std::shared_ptr<VertexArray> m_vertexArray;
		std::shared_ptr<VertexBuffer> m_vertexBuffer;
		std::shared_ptr<IndexBuffer> m_indexBuffer;

		//Drawing a square

		std::shared_ptr<VertexArray> m_vertexArraySq;
		std::shared_ptr<Shader> m_shaderSq;

		LayerStack m_layerStack;

		static Application* s_instance;

		//Rendering a triangle, temporary
		

	};
	Application* CreateApplication();
}

