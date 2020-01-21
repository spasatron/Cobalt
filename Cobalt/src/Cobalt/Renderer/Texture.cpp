#include "cbpc.h"

#include "Texture.h"
#include "Renderer.h"

#include "Cobalt/Platform/OpenGL/OpenGLTexture.h"

namespace Cobalt {



	Ref<Texture2D> Texture2D::Create(const std::string& path){
		switch (Renderer::GetRendererAPI()) {
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLTexture2D>(path);
			case RendererAPI::API::None:			COBALT_ASSERT(false, "RenderAPI::None is currently not supported");
			return nullptr;
		}

		COBALT_CORE_ERROR("COULD NOT FIND RENDERER API");
		return nullptr;
	}

}