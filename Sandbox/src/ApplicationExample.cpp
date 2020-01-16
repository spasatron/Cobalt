#include <Cobalt.h>

#include "imgui/imgui.h"




class ExampleLayer : public Cobalt::Layer {

public:
	ExampleLayer() : Layer("Example Layer"), m_camera(-1.6f, 1.6f, -.9f, .9f){
	}

	void OnUpdate() override{


		if (Cobalt::Input::IsKeyPressed(COBALT_KEY_Q)) {
			m_camera.SetRotation(m_camera.GetRotation() - 1);
		}
		if (Cobalt::Input::IsKeyPressed(COBALT_KEY_E)) {
			m_camera.SetRotation(m_camera.GetRotation() + 1);
		}


		Cobalt::RenderCommand::SetClearColor(clearColor);
		Cobalt::RenderCommand::Clear();

		Cobalt::Renderer::BeginScene(m_camera);

		Cobalt::Renderer::Submit(m_shaderSq, m_vertexArraySq);
		Cobalt::Renderer::Submit(m_shader, m_vertexArray);

		Cobalt::Renderer::EndScene();


	}



	void OnEvent(Cobalt::Event& e) override {


	}


	void OnImGuiRender() override {
		
		ImGui::Begin("Pick Background Color");
		ImGui::ColorPicker3("Pick Background", &clearColor.x);
		ImGui::End();
		
	}




	void OnAttach() override {

		m_vertexArray.reset(Cobalt::VertexArray::Create());


		//Without projection matrices the axis go from -1 to 1
		float vertices[3 * 6] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f
		};

		//We need to upload the data to the GPU
		m_vertexBuffer.reset(Cobalt::VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			Cobalt::BufferLayout layout = {
				{Cobalt::ShaderDataType::Float3, "vertices"},
				{Cobalt::ShaderDataType::Float3, "color"}
			};
			m_vertexBuffer->SetLayout(layout);
		}


		m_vertexArray->AddVertexBuffer(m_vertexBuffer);
		//Designates layout


		uint32_t indices[3] = { 0,1,2 };

		m_indexBuffer.reset(Cobalt::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_vertexArray->SetIndexBuffer(m_indexBuffer);

		float verticesSq[3 * 4] = {
			-0.6f, -.6f, 0.0f,
			0.6f, -.6f, 0.0f,
			0.6f, 0.6f, 0.0f,
			-0.6f, 0.6f, 0.0f
		};

		m_vertexArraySq.reset(Cobalt::VertexArray::Create());
		std::shared_ptr<Cobalt::VertexBuffer> squareVB;
		squareVB.reset(Cobalt::VertexBuffer::Create(verticesSq, sizeof(verticesSq)));



		Cobalt::BufferLayout layoutSq = {
				{Cobalt::ShaderDataType::Float3, "vertices"}
		};
		squareVB->SetLayout(layoutSq);

		uint32_t indicesSq[6] = { 0,1,2, 2, 3, 0 };

		std::shared_ptr<Cobalt::IndexBuffer> squareIB;
		squareIB.reset(Cobalt::IndexBuffer::Create(indicesSq, sizeof(indicesSq) / sizeof(uint32_t)));
		m_vertexArraySq->AddVertexBuffer(squareVB);
		m_vertexArraySq->SetIndexBuffer(squareIB);

		std::string vertSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_position;
			layout(location = 1) in vec3 a_color;
			
			uniform mat4 u_viewProjection;

			out vec3 v_position;
			out vec3 v_color;
			void main(){
				v_position = a_position;
				v_color = a_color;
				gl_Position = u_viewProjection*vec4(a_position,1);
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
		m_shader.reset(new Cobalt::Shader(vertSrc, fragSrc));
		std::string vertSrcSq = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_position;
			uniform mat4 u_viewProjection;			

			out vec4 v_position;

			void main(){
				gl_Position = u_viewProjection*vec4(a_position,1);
				v_position = gl_Position;
			}
		)";

		std::string fragSrcSq = R"(
			#version 330 core
			
			layout(location = 0) out vec4 o_color;
			
			in vec4 v_position;
			
			void main(){
				o_color = vec4(.8, .2, .35, 1);
				o_color = v_position + .5;
			}
		)";

		m_shaderSq.reset(new Cobalt::Shader(vertSrcSq, fragSrcSq));

	}

private:

	std::shared_ptr<Cobalt::Shader> m_shader;
	std::shared_ptr<Cobalt::VertexArray> m_vertexArray;
	std::shared_ptr<Cobalt::VertexBuffer> m_vertexBuffer;
	std::shared_ptr<Cobalt::IndexBuffer> m_indexBuffer;
	std::shared_ptr<Cobalt::VertexArray> m_vertexArraySq;
	std::shared_ptr<Cobalt::Shader> m_shaderSq;
	Cobalt::OrthographicCamera m_camera;
	glm::vec4 clearColor = { 0, .2, .8, 1 };

};




class Sandbox : public Cobalt::Application {
public: 
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {
		
	}

};


Cobalt::Application* Cobalt::CreateApplication(){
	return new Sandbox();
}









/*
class SLayer : public Cobalt::Layer {
public:

	SLayer() : Layer("New Layer") {}

	void OnUpdate() override {
		//COBALT_INFO("Update");
	}

	void OnEvent(Cobalt::Event& e) override {
		//The OnEvent function is where you want to implement the event dispatcher
		if (e.GetEventType() == Cobalt::EventType::KeyPressed) {
			Cobalt::KeyPressedEvent& event = (Cobalt::KeyPressedEvent&)e;
			COBALT_INFO("{0}", (char)event.GetKeyCode());
		}

		//COBALT_TRACE("Event Detected{0}", e);

	}
	//How to override th ImGui Layer
	void OnImGuiRender() override {

		ImGui::Begin("Text");
		ImGui::TextColored(ImVec4(1, 0, 0, 1), "Hello");
		ImGui::End();

	}

};
*/