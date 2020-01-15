#include "cbpc.h"
#include "Application.h"

#include <glad/glad.h>
#include "Cobalt/Input.h"

#include "Cobalt/ImGui/ImGuiLayer.h"

namespace Cobalt {


//jsut sets the eventFunction to be whatever is passed in


	Application* Application::s_instance = nullptr;


	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type) {
		switch (type)
		{
			
		case Cobalt::ShaderDataType::Float:
		
		case Cobalt::ShaderDataType::Float2:

		case Cobalt::ShaderDataType::Float3:

		case Cobalt::ShaderDataType::Float4:

		case Cobalt::ShaderDataType::Mat3:

		case Cobalt::ShaderDataType::Mat4:
			return GL_FLOAT;

		case Cobalt::ShaderDataType::Int:

		case Cobalt::ShaderDataType::Int2:

		case Cobalt::ShaderDataType::Int3:

		case Cobalt::ShaderDataType::Int4:
			return GL_INT;

		case Cobalt::ShaderDataType::Bool:
			return GL_BOOL;
		}

		COBALT_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;

	}

	Application::Application() {

		COBALT_CORE_ASSERT(!s_instance, "One Application Already Exists");

		s_instance = this;
		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetEventCallback(COBALT_BIND_EVENT_FUNCTION(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		//Getting removed
		glGenVertexArrays(1, &m_vertexArray);
		glBindVertexArray(m_vertexArray);


		//Without projection matrices the axis go from -1 to 1
		float vertices[3 * 6] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f
		};

		//We need to upload the data to the GPU
		m_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout = {
				{ShaderDataType::Float3, "vertices"},
				{ShaderDataType::Float3, "color"}
			};
			m_vertexBuffer->SetLayout(layout);
		}
		
		const auto& layout = m_vertexBuffer->GetLayout();

		uint32_t index = 0;

		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLType(element.type), element.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.offset);
			index++;
		}

		//Designates layout
		
		

		uint32_t indices[3] = { 0,1,2 };
		
		m_indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));

		std::string vertSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_position;
			layout(location = 1) in vec3 a_color;

			out vec3 v_position;
			out vec3 v_color;
			void main(){
				v_position = a_position;
				v_color = a_color;
				gl_Position = vec4(a_position,1);
			}
		)";

		std::string fragSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 o_color;
			
			in vec3 v_position;
			in vec3 v_color;
			
			void main(){
				o_color = vec4(v_color, 1);
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
			glDrawElements(GL_TRIANGLES, m_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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