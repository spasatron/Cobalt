#pragma once

#include "Cobalt/Layer.h"
#include "Cobalt/Events/MouseEvent.h"

namespace Cobalt{


	class COBALT_API ImGuiLayer : public Layer
	{
	public:

		ImGuiLayer();
		~ImGuiLayer();
		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);

		

	private:
		float m_time = 0.0f;

		bool ImGuiOnMousePress(MouseButtonPressedEvent& e);
		bool ImGuiOnMouseMoved(MouseMovedEvent& e);
		bool ImGuiOnMouseReleased(MouseButtonReleasedEvent& e);
		bool ImGuiOnMouseScroll(MouseScrolledEvent& e);

		//To Do Key Events

	};

}