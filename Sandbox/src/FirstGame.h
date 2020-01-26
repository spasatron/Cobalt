#pragma once

#include <Cobalt.h>

class FirstGame : public Cobalt::Layer
{
public:

	FirstGame();
	virtual ~FirstGame() override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Cobalt::TimeStep ts) override;
	virtual void OnEvent(Cobalt::Event& e) override;


private:
	Cobalt::OrthographicCameraController m_cameraController;
	glm::vec4 m_color = { .8f, 0.1f, 0.3f, 1.0f };
	glm::vec2 m_characterPos = { 0.0f, 0.0f };
	const float gravity = -3.0f;
	float speed = 0.0f;
	bool gameWon = false;
	float rotWin = 45, charRot = 0;
	float scaleSpeed = 0.0f, scale = 1.0f;
	float scaleChange = .4f;
};

