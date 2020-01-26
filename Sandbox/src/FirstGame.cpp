#include "FirstGame.h"

#include <glm/gtc/type_ptr.hpp>
#include <algorithm>
/*

Notes - we need to figure out how to handle collisions a little better, guess and check won't do. Player object should have a collider.
We can make the next level be contained on the previous player character, thus loading it once you reach the end of the level.
Obviously, we could use a main menu
Sound effects, the movement effects look real cool already


*/




FirstGame::FirstGame()
	: Layer("Sandbox2D"), m_cameraController(1280.0f / 720.0f)
{
}

FirstGame::~FirstGame()
{

}

void FirstGame::OnAttach()
{
	
}

void FirstGame::OnDetach()
{
	Cobalt::Renderer2D::Shutdown();
}

void FirstGame::OnUpdate(Cobalt::TimeStep ts)
{

	if (m_characterPos.x > 1.06f && m_characterPos.x < 1.34f && m_characterPos.y > -.3 && m_characterPos.y < 0) {
		gameWon = true;
	}

	if (gameWon) {
		charRot += 120 * ts;
		scaleSpeed += scaleChange * ts;
	}
	scale += scaleSpeed;


	if (m_characterPos.y >= -.47f) {
		speed += gravity * ts;
	}
	else {
		speed = 0;
		m_characterPos.y = -.47f;
	}


	if (Cobalt::Input::IsKeyPressed(COBALT_KEY_UP) && speed == 0) {
		speed = 2;
	}
	if (Cobalt::Input::IsKeyPressed(COBALT_KEY_LEFT)) {
		m_characterPos.x -= ts;
	}
	if (Cobalt::Input::IsKeyPressed(COBALT_KEY_RIGHT)) {
		m_characterPos.x += ts;
	}



	rotWin += 90 * ts;

	m_characterPos.y += speed*ts;

	m_cameraController.OnUpdate(ts);

	Cobalt::RenderCommand::SetClearColor({ .05f, .07f, .13f, 1.0f });
	Cobalt::RenderCommand::Clear();

	Cobalt::Renderer2D::BeginScene(m_cameraController.GetCamera());


	//Draw ground
	Cobalt::Renderer2D::DrawQuad({ 1.2f, -.1f }, { .05f, .05f }, { .68f, .7f, .1f, 1.0f }, rotWin);
	Cobalt::Renderer2D::DrawQuad({ 0.0f, -.8f, .1f }, { 3.0f, .3f }, { 0.2f, 0.3f, .8f , 1.0f});

	//Draw a bouncy swaure on the way up
	if (speed >= 0) {
		Cobalt::Renderer2D::DrawQuad(m_characterPos, { scale*std::min(.6f / (4.0f * std::abs(speed / 1.5f)), .6f / 3.8f), scale*std::max(1.0f / 4.0f, std::abs(speed / 1.3f) * 1.0f / 4.0f) }, m_color, charRot);
	}
	else {
		Cobalt::Renderer2D::DrawQuad(m_characterPos, {  scale*.6f / 3.8f, scale*1.0f / 4.0f}, m_color, charRot);
	}


	if (scale > 30) {
		scaleChange = 100.0f;
		Cobalt::Renderer2D::DrawQuad(m_characterPos, { std::min(scale/3000.0f, 1.0f)*std::min(.6f / (4.0f * std::abs(speed / 1.5f)), .6f / 3.8f), std::min(1.0f, scale/3000.0f)*std::max(1.0f / 4.0f, std::abs(speed / 1.3f) * 1.0f / 4.0f) }, { .2f, .7f, .4f , 1.0f});
	}


	Cobalt::Renderer2D::EndScene();

}




void FirstGame::OnEvent(Cobalt::Event& e)
{
	m_cameraController.OnEvent(e);
}




