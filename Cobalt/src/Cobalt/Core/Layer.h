#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Events/Event.h"
#include "Cobalt/Core/TimeStep.h"


namespace Cobalt {



	//Intended use is to subclass the Layer in your own application
	class COBALT_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();


		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(TimeStep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}


		inline const std::string& GetName() const { return m_debugName; }

	private:

		std::string m_debugName;
	};

}