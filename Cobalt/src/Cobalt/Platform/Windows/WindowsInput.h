#pragma once

#include "Cobalt/Input.h"

namespace Cobalt {


	class WindowsInput : public Input
	{


	protected:
		virtual bool IsKeyPressedImpl(int keyCode) override;
		virtual bool IsMouseButtonPressedImpl(int mouseButton) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;


	};

}