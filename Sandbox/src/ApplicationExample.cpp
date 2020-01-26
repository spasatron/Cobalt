#include <Cobalt.h>
#include <Cobalt/Core/EntryPoint.h>


#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>



//Include Sandbox2D play layer
#include "Sandbox2D.h"
#include "FirstGame.h"


class ExampleLayer : public Cobalt::Layer {

public:
	ExampleLayer() : Layer("Example Layer"), m_cameraController(1280.0f/720.0f){
	}

	void OnUpdate(Cobalt::TimeStep ts) override{

		
		m_cameraController.OnUpdate(ts);

		alienPosition.y -= ts*alienSpeed / 5;

		alienSpeed += ts;

		if (Cobalt::Input::IsKeyPressed(COBALT_KEY_LEFT)) {
			alienPosition.x -= ts;

		}
		if (Cobalt::Input::IsKeyPressed(COBALT_KEY_UP)) {

			alienSpeed -= 1;
		}
		if (Cobalt::Input::IsKeyPressed(COBALT_KEY_DOWN)) {

			alienPosition.y -= ts;
		}
		if (Cobalt::Input::IsKeyPressed(COBALT_KEY_RIGHT)) {
			alienPosition.x += ts;
		}


		Cobalt::RenderCommand::SetClearColor(clearColor);
		Cobalt::RenderCommand::Clear();

		Cobalt::Renderer::BeginScene(m_cameraController.GetCamera());

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), alienPosition);
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
		Cobalt::Renderer::Submit(m_shaderLib.Get("texture"), m_vertexArraySq);
		m_textureAlien->Bind();
		Cobalt::Renderer::Submit(m_shaderLib.Get("texture"), m_vertexArray,glm::translate(glm::mat4(1.0f), alienPosition)*glm::scale(glm::mat4(1.0f), glm::vec3(.2f)));
		Cobalt::Renderer::EndScene();


	}



	void OnEvent(Cobalt::Event& e) override {

		m_cameraController.OnEvent(e);
	}


	void OnImGuiRender() override {
		
		ImGui::Begin("Pick Background Color");
		ImGui::ColorPicker3("Pick Background", &clearColor.x);
		ImGui::End();
		
	}




	void OnAttach() override {

		m_vertexArray = Cobalt::VertexArray::Create();

		/*
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
		*/
		float verticesRec[5 * 4] = {
			-1.2f, -0.6f, 0.0f, 0.0f, 0.0f,
			1.2f, -0.6f, 0.0f, 1.0f, 0.0f,
			1.2f, 0.6f, 0.0f, 1.0f, 1.0f,
			-1.2f, 0.6f, 0.0f, 0.0f, 1.0f
		};

		float verticesSq[5 * 4] = {
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};
		
		m_vertexBuffer = Cobalt::VertexBuffer::Create(verticesSq, sizeof(verticesSq));
		
		m_vertexArraySq = Cobalt::VertexArray::Create();
		Cobalt::Ref<Cobalt::VertexBuffer> squareVB;
		squareVB = Cobalt::VertexBuffer::Create(verticesRec, sizeof(verticesRec));



		Cobalt::BufferLayout layoutSq = {
			{Cobalt::ShaderDataType::Float3, "vertices"},
			{Cobalt::ShaderDataType::Float2, "u_texture"}
		};
		squareVB->SetLayout(layoutSq);
		m_vertexBuffer->SetLayout(layoutSq);
		
		uint32_t indicesSq[6] = { 0, 1, 2, 2, 3, 0};

		Cobalt::Ref<Cobalt::IndexBuffer> squareIB;
		squareIB = Cobalt::IndexBuffer::Create(indicesSq, sizeof(indicesSq) / sizeof(uint32_t));
		m_vertexArraySq->AddVertexBuffer(squareVB);
		m_vertexArray->AddVertexBuffer(m_vertexBuffer);
		m_vertexArraySq->SetIndexBuffer(squareIB);
		m_vertexArray->SetIndexBuffer(squareIB);

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
		m_flatColorShader = Cobalt::Shader::Create("FlatColorShader",vertSrcFlat, fragSrcFlat);

		m_flatColorShader->Bind();
		m_flatColorShader->SetFloat4("u_color", { .8, 0.1, 0.3, 1.0 });

		auto textureShader = m_shaderLib.Load("assets/shaders/texture.glsl");
		textureShader->Bind();
		textureShader->SetInt("u_texture", 0);


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

		m_shaderSq = Cobalt::Shader::Create("SquareShader", vertSrcSq, fragSrcSq);

		m_textureTest = Cobalt::Texture2D::Create("assets/textures/map.png");
		m_textureAlien = Cobalt::Texture2D::Create("assets/textures/alien.png");

	}

private:

	Cobalt::ShaderLibrary m_shaderLib;
	Cobalt::Ref<Cobalt::Shader> m_flatColorShader;
	Cobalt::Ref<Cobalt::VertexArray> m_vertexArray;
	Cobalt::Ref<Cobalt::VertexBuffer> m_vertexBuffer;
	Cobalt::Ref<Cobalt::Shader> m_shaderSq;
	Cobalt::Ref<Cobalt::IndexBuffer> m_indexBuffer;
	Cobalt::Ref<Cobalt::VertexArray> m_vertexArraySq;

	Cobalt::Ref<Cobalt::Texture2D> m_textureTest;
	Cobalt::Ref<Cobalt::Texture2D> m_textureAlien;


	Cobalt::OrthographicCameraController m_cameraController;
	glm::vec4 clearColor = { 0, .2, .8, 1 };
	glm::vec3 alienPosition = { 0 ,0, 0 };

	float alienSpeed = 0.0f;

};




class Sandbox : public Cobalt::Application {
public: 
	Sandbox() {
		//Use this for an example layer
		//PushLayer(new ExampleLayer());
		PushLayer(new FirstGame());
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