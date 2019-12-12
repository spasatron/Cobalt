#pragma once

#include "Core.h"
#include <stdio.h>

namespace Cobalt {
	class COBALT_API  Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};
	//To be defined in client
	Application* CreateApplication();
}

