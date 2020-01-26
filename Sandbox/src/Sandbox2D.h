#pragma once

#include <Cobalt.h>



class Sandbox2D : public Cobalt::Layer{
public:

	Sandbox2D();
	virtual ~Sandbox2D() override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Cobalt::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Cobalt::Event& e) override;


private:
	Cobalt::OrthographicCameraController m_cameraController;	
	glm::vec4 m_color = { .8f, 0.1f, 0.3f, .3f };
	Cobalt::Ref<Cobalt::Texture2D> m_texture;
};

