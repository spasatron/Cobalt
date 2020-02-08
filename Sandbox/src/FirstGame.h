#pragma once

#include <Cobalt.h>




class RectangleMy {
public:
	RectangleMy() {}
	RectangleMy(glm::vec2 upLeft, glm::vec2 downRight);
	void Draw();
	void SetVertex(glm::vec2 down) { m_downR = down; }
	glm::vec2& GetVertexRef() { return m_downR; }
	glm::vec4 GetVerticies() { return glm::vec4(m_upL.x, m_upL.y, m_downR.x, m_downR.y); }
private:
	glm::vec2 m_upL = { 0,0 }, m_downR{ 0,0 };
};



class Player {
public:
	void PlayerInput(Cobalt::TimeStep ts);
	void OnUpdate(Cobalt::TimeStep ts);
	void Draw();
	void TestCollision(RectangleMy* object);
private:
	glm::vec2 GetUpperLeft();
	glm::vec2 GetLowerRight();
private:
	float sizeY = .6f/4.0f, sizeX = .36f / 3.8f;
	glm::vec4 m_color = { .8f, 0.1f, 0.3f, 1.0f };
	float speedY = 0, speedX = 0;
	glm::vec2 m_characterPos = { 0.0f, 0.0f };
	float gravity = -3.0f;
	bool gameWon = false;
	float charRot = 0;
	float scaleSpeed = 0.0f, scale = 1.0f;
	float scaleChange = .4f;
};







class FirstGame : public Cobalt::Layer
{
public:

	FirstGame();
	virtual ~FirstGame() override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Cobalt::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Cobalt::Event& e) override;


private:
	Cobalt::OrthographicCameraController m_cameraController;
	RectangleMy* m_rect = nullptr;
	Player m_player;
	float winRot = 0;
	
};

