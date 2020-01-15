#include "cbpc.h"
#include "Buffer.h"
#include "Renderer.h"

//Platform specific stuff needs to be surrounded by #if COBALT_PLAT and #endif

#include "Cobalt/Platform/OpenGL/OpenGLBuffer.h"

namespace Cobalt {


	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {

		switch (Renderer::GetRendererAPI()) {
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		case RendererAPI::None:
			COBALT_INFO("None Render API SELECTED");
			return nullptr;
		}
		COBALT_CORE_ERROR("COULD NOT FIND RENDERER API");
		return nullptr;


	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		switch (Renderer::GetRendererAPI()) {
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		case RendererAPI::None:
			COBALT_INFO("None Render API SELECTED");
			return nullptr;
		}
		COBALT_CORE_ERROR("COULD NOT FIND RENDERER API");
		return nullptr;
	}


}