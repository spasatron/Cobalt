#pragma once
#include "Cobalt.h"

enum class RenderMode {
	Mandelbrot, Julia
};


class MandelbrotLayer : public Cobalt::Layer
{
public:
	MandelbrotLayer() : Layer("Mandelbrot"), m_camera(-aspectRatio * m_zoomLevel, aspectRatio* m_zoomLevel, -m_zoomLevel, m_zoomLevel){}
	void OnUpdate(Cobalt::TimeStep ts) override;
	void OnAttach() override;
	void OnEvent(Cobalt::Event& e) override;


private:
	bool SetMousePos(Cobalt::MouseMovedEvent& e);
private:
	float aspectRatio = 1280.0f / 720.0f;
	float m_zoomLevel = 1;
	float scape[3 * 4] = {
			-1.0f, -1.0f,
			 1.0f, -1.0f,
			 1.0f,  1.0f,
			-1.0f,  1.0f
	};
	float scale = 1.0f;
	glm::vec3 position = { 1.0f, 0.0f, 0.0f };
	Cobalt::Ref<Cobalt::Shader> m_shaderM, m_shaderJ;
	Cobalt::OrthographicCamera m_camera;
	Cobalt::Ref<Cobalt::VertexArray> m_vertexArray;
	Cobalt::Ref<Cobalt::IndexBuffer> m_iBuffer;
	Cobalt::Ref<Cobalt::VertexBuffer> m_vBuffer;
	RenderMode currentMode = RenderMode::Mandelbrot;
};

