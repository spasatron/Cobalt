#include "cbpc.h"

#include "VertexArray.h"
#include "Renderer.h"

#include "Cobalt/Platform/OpenGL/OpenGLVertexArray.h"

namespace Cobalt {




	Ref<VertexArray> VertexArray::Create(){
		switch (Renderer::GetRendererAPI()) {
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLVertexArray>();
		case RendererAPI::API::None:			COBALT_ASSERT(false, "RenderAPI::None is currently not supported");
			return nullptr;
		}

		COBALT_CORE_ERROR("COULD NOT FIND RENDERER API");
		return nullptr;
	}

}