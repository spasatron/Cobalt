#include "cbpc.h"

#include "VertexArray.h"
#include "Renderer.h"

#include "Cobalt/Platform/OpenGL/OpenGLVertexArray.h"

namespace Cobalt {




	VertexArray* VertexArray::Create(){
		switch (Renderer::GetRendererAPI()) {
		case RendererAPI::OpenGL:		return new OpenGLVertexArray();
		case RendererAPI::None:			COBALT_ASSERT(false, "RenderAPI::None is currently not supported")
			return nullptr;
		}

		COBALT_CORE_ERROR("COULD NOT FIND RENDERER API");
		return nullptr;
	}

}