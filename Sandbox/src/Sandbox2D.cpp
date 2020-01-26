#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_cameraController(1280.0f / 720.0f)
{
}

Sandbox2D::~Sandbox2D()
{

}

void Sandbox2D::OnAttach()
{
	m_texture = Cobalt::Texture2D::Create("assets/textures/alien.png");
}

void Sandbox2D::OnDetach()
{
	Cobalt::Renderer2D::Shutdown();
}

void Sandbox2D::OnUpdate(Cobalt::TimeStep ts)
{

	m_cameraController.OnUpdate(ts);

	Cobalt::RenderCommand::SetClearColor({.05f, .07f, .13f, 1.0f});
	Cobalt::RenderCommand::Clear();

	Cobalt::Renderer2D::BeginScene(m_cameraController.GetCamera());

	Cobalt::Renderer2D::DrawQuad({ .0f, .0f, .1f }, { .2f, .2f }, m_texture);
	Cobalt::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { .6f, 1.0f }, m_color, 45.0f);

	Cobalt::Renderer2D::EndScene();

}

void Sandbox2D::OnImGuiRender()
{
	
	ImGui::Begin("Color Picker");
	ImGui::ColorPicker4("Pick", glm::value_ptr(m_color));
	ImGui::End();
	
}


void Sandbox2D::OnEvent(Cobalt::Event& e)
{
	m_cameraController.OnEvent(e);
}
