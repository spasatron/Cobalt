#include "FirstGame.h"

#include <glm/gtc/type_ptr.hpp>
#include <algorithm>
#include "imgui/imgui.h"
/*

Notes - we need to figure out how to handle collisions a little better, guess and check won't do. Player object should have a collider.
We can make the next level be contained on the previous player character, thus loading it once you reach the end of the level.
Obviously, we could use a main menu
Sound effects, the movement effects look real cool already


*/



RectangleMy::RectangleMy(glm::vec2 upLeft, glm::vec2 downRight) : m_upL(upLeft), m_downR(downRight) {
}
void RectangleMy::Draw() {

	Cobalt::Renderer2D::DrawQuad({ (m_upL.x + m_downR.x) / 2, (m_upL.y + m_downR.y) / 2 }, { (m_downR.x-m_upL.x)/2, (m_upL.y -m_downR.y)/2}, { 0.0f, 0.0f, 0.0f, 1.0f });
	// Just a way to check the corners
	Cobalt::Renderer2D::DrawQuad({ m_upL.x, m_upL.y }, { .1f, .1f }, { 1.0f, 1.0f, 1.0f, 1.0f });
	Cobalt::Renderer2D::DrawQuad({ m_downR.x, m_downR.y }, { .1f, .1f }, { 1.0f, 1.0f, 1.0f, 1.0f });
	
}


void Player::PlayerInput(Cobalt::TimeStep ts)
{
	speedX = 0;
	if (m_characterPos.x > 1.06f && m_characterPos.x < 1.34f && m_characterPos.y > -.3 && m_characterPos.y < 0) {
		gameWon = true;
	}

	if (gameWon) {
		charRot += 120 * ts;
		scaleSpeed += scaleChange * ts;
	}
	scale += scaleSpeed;
	//Collision handling
	if (m_characterPos.y >= -.47f) {
		speedY += gravity * ts;
	}
	else {
		speedY = 0;
		m_characterPos.y = -.47f;
	}
	if (Cobalt::Input::IsKeyPressed(COBALT_KEY_UP) && speedY == 0.0f) {
		speedY = 2;
	}
	if (Cobalt::Input::IsKeyPressed(COBALT_KEY_LEFT)) {
		speedX = -1;
	}
	if (Cobalt::Input::IsKeyPressed(COBALT_KEY_RIGHT)) {
		speedX = 1;
	}

}

void Player::OnUpdate(Cobalt::TimeStep ts) {
	m_characterPos.y += speedY * ts;
	m_characterPos.x += speedX * ts;
}


void Player::Draw() {
	if (speedY >= 0) {
		Cobalt::Renderer2D::DrawQuad(m_characterPos, { scale * std::min(sizeX/(std::abs(speedY / 1.5f)), sizeX), scale * std::max(sizeY, std::abs(speedY / 1.3f) * sizeY) }, m_color, charRot);
	}
	else {
		Cobalt::Renderer2D::DrawQuad(m_characterPos, { scale * sizeX, scale * sizeY }, m_color, charRot);
	}


	if (scale > 30) {
		scaleChange = 100.0f;
		if (speedY >= 0) {
			Cobalt::Renderer2D::DrawQuad(m_characterPos, { .6f*std::min(scale / 3000.0f, 1.0f) * std::min(.6f / (4.0f * std::abs(speedY / 1.5f)), .6f / 3.8f), .6f*std::min(1.0f, scale / 3000.0f) * std::max(1.0f / 4.0f, std::abs(speedY / 1.3f) * 1.0f / 4.0f) }, { .2f, .7f, .4f , 1.0f });
		}
		else {
			Cobalt::Renderer2D::DrawQuad(m_characterPos, {.6f* std::min(scale / 3000.0f, 1.0f) * .6f / 3.8f, .6*std::min(scale / 3000.0f, 1.0f) * 1.0f / 4.0f }, { .2f, .7f, .4f , 1.0f });
		}
	}

}

void Player::TestCollision(RectangleMy* object)
{

	glm::vec4 position = object->GetVerticies();

	if (position.z > GetUpperLeft().x && position.y  > .01f+ GetLowerRight().y && position.w < .01f + GetUpperLeft().y && position.x < GetLowerRight().x) {
		speedX = std::max(0.0f, speedX);
	}
	if (position.y > GetLowerRight().y && position.x < GetLowerRight().x && position.z > GetUpperLeft().x) {
		speedY = std::max(0.0f, speedY);
	}


}

glm::vec2 Player::GetUpperLeft()
{
	glm::vec2 upL;
	upL.x = m_characterPos.x - sizeX;
	upL.y = m_characterPos.y + sizeY;
	return upL;
}

glm::vec2 Player::GetLowerRight()
{
	glm::vec2 downL;
	downL.x = m_characterPos.x + sizeX;
	downL.y = m_characterPos.y - sizeY;
	return downL;
}



FirstGame::FirstGame()
	: Layer("Sandbox2D"), m_cameraController(1280.0f / 720.0f)
{
}

FirstGame::~FirstGame()
{

}

void FirstGame::OnAttach()
{
	m_rect = new RectangleMy({ -1.0f, 0.0f }, { -.5f, -.5f });
}

void FirstGame::OnDetach()
{
	delete m_rect;
	Cobalt::Renderer2D::Shutdown();
}

void FirstGame::OnUpdate(Cobalt::TimeStep ts)
{




	m_player.PlayerInput(ts);
	winRot += 90 * ts;
	m_player.TestCollision(m_rect);
	m_player.OnUpdate(ts);
	m_cameraController.OnUpdate(ts);

	Cobalt::RenderCommand::SetClearColor({ .05f, .07f, .13f, 1.0f });
	Cobalt::RenderCommand::Clear();

	Cobalt::Renderer2D::BeginScene(m_cameraController.GetCamera());

	
	//Draw ground
	//Cobalt::Renderer2D::DrawQuad({ 1.2f, -.1f }, { .6f*.05f, .6f*.05f }, { .68f, .7f, .1f, 1.0f }, winRot);
	Cobalt::Renderer2D::DrawQuad({ 0.0f, -.8f, .1f }, { .6f*3.0f, .6f*.3f }, { 0.2f, 0.3f, .8f , 1.0f});
	m_rect->Draw();
	m_player.Draw();
	//Draw a bouncy swaure on the way up
	
	Cobalt::Renderer2D::EndScene();

}

void FirstGame::OnImGuiRender()
{
	/* Just a test of the verticies
	ImGui::Begin("Vertex");
	ImGui::DragFloat2("Change downRight vertex", glm::value_ptr(m_rect->GetVertexRef()));
	ImGui::End();
	*/
}





void FirstGame::OnEvent(Cobalt::Event& e)
{
	m_cameraController.OnEvent(e);
}




