#pragma once

namespace Cobalt {

	class COBALT_API GraphicsContext {

	public:
		
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

	private:


	};

}