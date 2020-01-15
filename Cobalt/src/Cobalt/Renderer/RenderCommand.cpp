#include "cbpc.h"

#include "RenderCommand.h"

#include "Cobalt/Platform/OpenGL/OpenGLRendererAPI.h"


namespace Cobalt {


	RendererAPI* RenderCommand::s_rendererAPI = new OpenGLRendererAPI();


}