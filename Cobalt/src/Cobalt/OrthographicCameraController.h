#pragma once

#include "Cobalt/Renderer/OrthographicCamera.h"
#include "Cobalt/Core/TimeStep.h"

#include "Cobalt/Events/MouseEvent.h"
#include "Cobalt/Events/ApplicationEvent.h"

namespace Cobalt {

	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRatio); //Set by defualt zoom level = 1 so 2 units of space vertically
		
		OrthographicCamera& GetCamera() { return m_camera; }
		const OrthographicCamera& GetCamera() const { return m_camera; }

		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		float m_aspectRatio;
		float m_zoomLevel = 1.0f;
		OrthographicCamera m_camera;

		glm::vec3 m_cameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_cameraRotation = 0.0f;

		float m_cameraTranslationSpeed = 1.0f;
		float m_cameraRotationSpeed = 30.0f;

	};

}