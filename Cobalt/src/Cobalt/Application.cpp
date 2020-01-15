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

		

		m_vertexArray.reset(VertexArray::Create());
		

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


		m_vertexArray->AddVertexBuffer(m_vertexBuffer);
		//Designates layout
		
		

		uint32_t indices[3] = { 0,1,2 };
		
		m_indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));

		m_vertexArray->SetIndexBuffer(m_indexBuffer);

		float verticesSq[3 * 4] = {
			-0.5f, 0.0f, 0.0f,
			0.5f, 0.0f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};

		m_vertexArraySq.reset(VertexArray::Create());
		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(verticesSq, sizeof(verticesSq)));

		BufferLayout layoutSq = {
				{ShaderDataType::Float3, "vertices"}
		};
		squareVB->SetLayout(layoutSq);

		uint32_t indicesSq[6] = { 0,1,2, 2, 3, 0};

		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(indicesSq, sizeof(indicesSq) / sizeof(uint32_t)));
		m_vertexArraySq->AddVertexBuffer(squareVB);
		m_vertexArraySq->SetIndexBuffer(squareIB);

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
		std::string vertSrcSq = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_position;

			out vec3 v_position;

			void main(){
				v_position = a_position;
				gl_Position = vec4(a_position,1);
			}
		)";

		std::string fragSrcSq = R"(
			#version 330 core
			
			layout(location = 0) out vec4 o_color;
			
			in vec3 v_position;
			
			void main(){
				o_color = vec4(.8, .2, .35, 1);
			}
		)";

		m_shaderSq.reset(new Shader(vertSrcSq, fragSrcSq));





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

			
			m_shaderSq->Bind();
			m_vertexArraySq->Bind();
			glDrawElements(GL_TRIANGLES, m_vertexArraySq->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_shader->Bind();
			m_vertexArray->Bind();
			

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