#pragma once

#include "Cobalt/Core/Core.h"


namespace Cobalt {
	class COBALT_API Input {
	public:

		//Ways to to get input for the Engine
		static inline bool IsKeyPressed(int keyCode) { return s_instance->IsKeyPressedImpl(keyCode); }
		static inline bool IsMouseButtonPressed(int mouseButton) { return s_instance->IsMouseButtonPressedImpl(mouseButton); }
		static inline std::pair<float, float> GetMousePosition() { return s_instance->GetMousePositionImpl(); }
		//Not Ideal, Use method to Get Both
		static inline float GetMouseX() { return s_instance->GetMouseXImpl(); }
		static inline float GetMouseY() { return s_instance->GetMouseYImpl(); }
		

	protected:
		//This here is implemented per platform
		virtual bool IsKeyPressedImpl(int keyCode) = 0;
		virtual bool IsMouseButtonPressedImpl(int mouseButton) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:


		static Input* s_instance;

	};
}



