#pragma once

#include "Cobalt/Core/Layer.h"
#include "Cobalt/Events/MouseEvent.h"

namespace Cobalt{


	class COBALT_API ImGuiLayer : public Layer
	{
	public:

		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();
		

	private:
		float m_time = 0.0f;

		//To Do Key Events

	};

}