#include "MandelbrotLayer.h"
#include "glm/gtc/matrix_transform.hpp"


void MandelbrotLayer::OnUpdate(Cobalt::TimeStep ts)
{

	if (Cobalt::Input::IsKeyPressed(COBALT_KEY_UP)) {
		scale -= scale / 100;
	}
	if (Cobalt::Input::IsKeyPressed(COBALT_KEY_DOWN)) {
		scale += scale / 10;
	}

	if (Cobalt::Input::IsKeyPressed(COBALT_KEY_J)) {
		currentMode = RenderMode::Julia;
	}
	else if (Cobalt::Input::IsKeyPressed(COBALT_KEY_M)) {
		currentMode = RenderMode::Mandelbrot;
	}



	Cobalt::RenderCommand::SetClearColor({ .2f, .3f, .8f, 1.0f });
	Cobalt::RenderCommand::Clear();
	Cobalt::Renderer::BeginScene(m_camera);
	glm::mat4 transform = glm::scale(glm::mat4(1.0f), { scale, scale, scale });
	if(currentMode == RenderMode::Mandelbrot)
		Cobalt::Renderer::Submit(m_shaderM, m_vertexArray, transform);
	else
		Cobalt::Renderer::Submit(m_shaderJ, m_vertexArray);
	Cobalt::Renderer::EndScene();



}

void MandelbrotLayer::OnAttach()
{
	m_vertexArray = Cobalt::VertexArray::Create();
	
	//Vertex Buffer and Layout
	float scape[3 * 4] = {
			-1.0f, -1.0f,
			 1.0f, -1.0f, 
			 1.0f,  1.0f, 
			-1.0f,  1.0f 
	};

	m_vBuffer = Cobalt::VertexBuffer::Create(scape , sizeof(scape));

	Cobalt::BufferLayout layout = {
		{Cobalt::ShaderDataType::Float2, "verticies"}
	};

	m_vBuffer->SetLayout(layout);
	//Index Buffer

	uint32_t indicesSq[6] = { 0, 1, 2, 2, 3, 0 };
	m_iBuffer = Cobalt::IndexBuffer::Create(indicesSq, sizeof(indicesSq) / sizeof(uint32_t));

	
	m_vertexArray->AddVertexBuffer(m_vBuffer);
	m_vertexArray->SetIndexBuffer(m_iBuffer);

	m_shaderJ = Cobalt::Shader::Create("assets/shaders/julia.glsl");
	m_shaderM = Cobalt::Shader::Create("assets/shaders/mandelbrot.glsl");
}

void MandelbrotLayer::OnEvent(Cobalt::Event& e)
{

	Cobalt::EventDispatcher dispatch(e);
	if (currentMode == RenderMode::Julia) {
		dispatch.Dispatch<Cobalt::MouseMovedEvent>(COBALT_BIND_EVENT_FUNCTION(MandelbrotLayer::SetMousePos));
	}
}

bool MandelbrotLayer::SetMousePos(Cobalt::MouseMovedEvent& e)
{
	//COBALT_INFO("{0}, {1}", e.GetX() / 1280.f - .5, e.GetY() / 720.f -.5);
	m_shaderJ->Bind();
	m_shaderJ->SetFloat2("u_mousePos", { 4*(e.GetX() / 1280.f - .5), 4*(e.GetY() / 720.f  - .5)});
	return false;
}





