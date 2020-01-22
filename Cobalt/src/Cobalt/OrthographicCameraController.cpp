#include "cbpc.h"
#include "OrthographicCameraController.h"

#include "Input.h"
#include "KeyCodes.h"

namespace Cobalt {



	OrthographicCameraController::OrthographicCameraController(float aspectRatio) : 
		m_aspectRatio(aspectRatio), m_camera(-m_aspectRatio*m_zoomLevel, m_aspectRatio*m_zoomLevel, -m_zoomLevel, m_zoomLevel){
	}

	void OrthographicCameraController::OnUpdate(TimeStep ts){
		if (Input::IsKeyPressed(COBALT_KEY_Q)) {
			m_cameraRotation -= m_cameraRotationSpeed * ts;
		}
		if (Input::IsKeyPressed(COBALT_KEY_E)) {
			m_cameraRotation += m_cameraRotationSpeed * ts;
		}
		if (Input::IsKeyPressed(COBALT_KEY_A)) {
			m_cameraPosition.x += m_cameraTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(COBALT_KEY_D)) {
			m_cameraPosition.x -= m_cameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(COBALT_KEY_W)) {
			m_cameraPosition.y -= m_cameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(COBALT_KEY_S)) {
			m_cameraPosition.y += m_cameraTranslationSpeed * ts;
		}

		m_cameraTranslationSpeed = m_zoomLevel;
		m_camera.SetPosition(m_cameraPosition);
		m_camera.SetRotation(m_cameraRotation);
	}

	void OrthographicCameraController::OnEvent(Event& e){
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(COBALT_BIND_EVENT_FUNCTION(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(COBALT_BIND_EVENT_FUNCTION(OrthographicCameraController::OnWindowResize));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_zoomLevel -= e.GetYOffset()*.25;
		m_zoomLevel = std::max(m_zoomLevel, .25f);
		m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		m_aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
		return false;
	}

}