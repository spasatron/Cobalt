#pragma once

#include "Core.h"


namespace Cobalt {
	class COBALT_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};
	Application* CreateApplication();
}

