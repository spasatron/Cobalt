#include <Cobalt.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Cobalt/Platform/OpenGL/OpenGLShader.h"



class ExampleLayer : public Cobalt::Layer {

public:
	ExampleLayer() : Layer("Example Layer"), m_camera(-1.6f, 1.6f, -.9f, .9f){
	}

	void OnUpdate(Cobalt::TimeStep ts) override{

		if (Cobalt::Input::IsKeyPressed(COBALT_KEY_Q)) {
			m_camera.SetRotation(m_camera.GetRotation() - 200*ts);
		}
		if (Cobalt::Input::IsKeyPressed(COBALT_KEY_E)) {
			m_camera.SetRotation(m_camera.GetRotation() + 200*ts);
		}
		if (Cobalt::Input::IsKeyPressed(COBALT_KEY_A)) {
			squarePosition.x -= 1 * ts;
		}
		if (Cobalt::Input::IsKeyPressed(COBALT_KEY_D)) {
			squarePosition.x += 1 * ts;
		}
		if (Cobalt::Input::IsKeyPressed(COBALT_KEY_S)) {
			squarePosition.y -= 1 * ts;
		}
		if (Cobalt::Input::IsKeyPressed(COBALT_KEY_W)) {
			squarePosition.y += 1 * ts;
		}


		Cobalt::RenderCommand::SetClearColor(clearColor);
		Cobalt::RenderCommand::Clear();

		Cobalt::Renderer::BeginScene(m_camera);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), squarePosition);
		/*
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				glm::mat4 trans = glm::translate(glm::mat4(1.0f), { squarePosition.x + i / (6.0f), squarePosition.y - j/(6.0f), squarePosition.z }) * glm::scale(glm::mat4(1.0f), glm::vec3(.1f));
				Cobalt::Renderer::Submit(m_shaderSq, m_vertexArraySq, trans);
			}
		}
		//	Cobalt::Renderer::Submit(m_shader, m_vertexArray);
		*/
		m_textureTest->Bind();
		Cobalt::Renderer::Submit(m_textureShader, m_vertexArraySq);
		m_textureAlien->Bind();
		Cobalt::Renderer::Submit(m_textureShader, m_vertexArraySq);
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

		float verticesSq[5 * 4] = {
			-1.2f, -0.6f, 0.0f, 0.0f, 0.0f,
			1.2f, -0.6f, 0.0f, 1.0f, 0.0f,
			1.2f, 0.6f, 0.0f, 1.0f, 1.0f,
			-1.2f, 0.6f, 0.0f, 0.0f, 1.0f
		};

		m_vertexArraySq.reset(Cobalt::VertexArray::Create());
		Cobalt::Ref<Cobalt::VertexBuffer> squareVB;
		squareVB.reset(Cobalt::VertexBuffer::Create(verticesSq, sizeof(verticesSq)));



		Cobalt::BufferLayout layoutSq = {
			{Cobalt::ShaderDataType::Float3, "vertices"},
			{Cobalt::ShaderDataType::Float2, "u_texture"}
		};
		squareVB->SetLayout(layoutSq);

		uint32_t indicesSq[6] = { 0, 1, 2, 2, 3, 0};

		Cobalt::Ref<Cobalt::IndexBuffer> squareIB;
		squareIB.reset(Cobalt::IndexBuffer::Create(indicesSq, sizeof(indicesSq) / sizeof(uint32_t)));
		m_vertexArraySq->AddVertexBuffer(squareVB);
		m_vertexArraySq->SetIndexBuffer(squareIB);

		std::string vertSrcFlat = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_position;
			
			uniform mat4 u_viewProjection;
			uniform mat4 u_Transform;

			void main(){

				gl_Position = u_viewProjection*u_Transform*vec4(a_position,1);

			}
		)";

		std::string fragSrcFlat = R"(
			#version 330 core
			
			layout(location = 0) out vec4 o_color;
			
			uniform vec4 u_color;
			
			void main(){
				o_color = vec4(u_color);
			}
		)";
		m_flatColorShader.reset(Cobalt::Shader::Create(vertSrcFlat, fragSrcFlat));

		m_flatColorShader->Bind();
		std::dynamic_pointer_cast<Cobalt::OpenGLShader>(m_flatColorShader)->UploadUniformFloat4("u_color", { .8, 0.1, 0.3, 1.0 });

		m_textureShader.reset(Cobalt::Shader::Create("assets/shaders/texture.glsl"));
		std::dynamic_pointer_cast<Cobalt::OpenGLShader>(m_textureShader)->Bind();
		std::dynamic_pointer_cast<Cobalt::OpenGLShader>(m_textureShader)->UploadUniformInt("u_texture", 0);


		std::string vertSrcSq = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_position;
			uniform mat4 u_viewProjection;		
			uniform mat4 u_Transform;

			out vec4 v_position;

			void main(){
				gl_Position = u_viewProjection*u_Transform*vec4(a_position,1);
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

		m_shaderSq.reset(Cobalt::Shader::Create(vertSrcSq, fragSrcSq));

		m_textureTest = Cobalt::Texture2D::Create("assets/textures/map.png");
		m_textureAlien = Cobalt::Texture2D::Create("assets/textures/alien.png");

	}

private:

	Cobalt::Ref<Cobalt::Shader> m_flatColorShader, m_textureShader;
	Cobalt::Ref<Cobalt::VertexArray> m_vertexArray;
	Cobalt::Ref<Cobalt::VertexBuffer> m_vertexBuffer;
	Cobalt::Ref<Cobalt::Shader> m_shaderSq;
	Cobalt::Ref<Cobalt::IndexBuffer> m_indexBuffer;
	Cobalt::Ref<Cobalt::VertexArray> m_vertexArraySq;

	Cobalt::Ref<Cobalt::Texture2D> m_textureTest;
	Cobalt::Ref<Cobalt::Texture2D> m_textureAlien;


	Cobalt::OrthographicCamera m_camera;
	glm::vec4 clearColor = { 0, .2, .8, 1 };
	glm::vec3 squarePosition = { 0 ,0, 0 };

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