#include "cbpc.h"
#include "Application.h"

#include <glad/glad.h>
#include "Cobalt/Input.h"

#include "Cobalt/ImGui/ImGuiLayer.h"

namespace Cobalt {


//jsut sets the eventFunction to be whatever is passed in


	Application* Application::s_instance = nullptr;

	Application::Application() {

		COBALT_CORE_ASSERT(!s_instance, "One Application Already Exists");

		s_instance = this;
		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetEventCallback(COBALT_BIND_EVENT_FUNCTION(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_vertexArray);
		glBindVertexArray(m_vertexArray);

		glGenBuffers(1, &m_vertextBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertextBuffer);


		//Without projection matrices the axis go from -1 to 1
		float vertices[3 * 3] = {
			-0.5f, -0.5f, -1.0f,
			0.5f, -0.5f, 1.0f,
			0.8f, 0.4f, 0.5f
		};

		//We need to upload the data to the GPU

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);
		
		glGenBuffers(1, &m_indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

		unsigned int indeces[3] = { 0,1,2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);


		std::string vertSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_position;

			out vec3 v_position;

			void main(){
				v_position = a_position;
				gl_Position = vec4(a_position,1);
			}
		)";

		std::string fragSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 o_color;
			
			in vec3 v_position;

			void main(){
				o_color = vec4(v_position + .5, 1);
			}
		)";

		m_shader.reset(new Shader(vertSrc, fragSrc));





	}
	Application::~Application() {

	}
	void Application::OnEvent(Event& e) {

		EventDispatcher eventDispatcher(e);
		eventDispatcher.Dispatch<WindowCloseEvent>(COBALT_BIND_EVENT_FUNCTION(Application::OnWindowClose));


		//COBALT_CORE_TRACE("{0}", e);

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();) {
			(*(--it))->OnEvent(e);
			if (e.m_Handled) {
				break;
			}
		}


	}
	

	void Application::Run() {
		
		while (m_running) {
			glClearColor(0, .2, .8, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_shader->Bind();

			glBindVertexArray(m_vertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_layerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_layerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
			//Input is now working
			//COBALT_CORE_INFO("{0}", Input::IsKeyPressed(65));
			m_window->OnUpdate();
		}

	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer) {
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		m_layerStack.PushOverlay(overlay);
		overlay->OnAttach(); 
	}

}