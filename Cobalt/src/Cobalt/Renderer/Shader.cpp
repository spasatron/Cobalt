#include "cbpc.h"
#include "Shader.h"

#include "Renderer.h"

#include "Cobalt/Platform/OpenGL/OpenGLShader.h"



namespace Cobalt {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetRendererAPI()) {
		case RendererAPI::API::OpenGL:		return new OpenGLShader(vertexSrc, fragmentSrc);
		case RendererAPI::API::None:			COBALT_ASSERT(false, "RenderAPI::None is currently not supported");
			return nullptr;
		}
		COBALT_CORE_ERROR("COULD NOT FIND RENDERER API");
		return nullptr;
	}
}