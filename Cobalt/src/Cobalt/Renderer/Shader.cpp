#include "cbpc.h"
#include "Shader.h"

#include "Renderer.h"

#include "Cobalt/Platform/OpenGL/OpenGLShader.h"



namespace Cobalt {
	
	
	Ref<Shader> Shader::Create(const std::string& name,const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetRendererAPI()) {
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		case RendererAPI::API::None:			COBALT_ASSERT(false, "RenderAPI::None is currently not supported");
			return nullptr;
		}
		COBALT_CORE_ERROR("COULD NOT FIND RENDERER API");
		return nullptr;
	}


	Ref<Shader> Shader::Create(const std::string& fileName) {
		switch (Renderer::GetRendererAPI()) {
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLShader>(fileName);
		case RendererAPI::API::None:			COBALT_ASSERT(false, "RenderAPI::None is currently not supported");
			return nullptr;
		}
		COBALT_CORE_ERROR("COULD NOT FIND RENDERER API");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader) {
		COBALT_CORE_ASSERT(m_shaders.find(name) == m_shaders.end(), "Shaders must have a unique name");
		m_shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader){
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string name, const std::string& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(name, shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		COBALT_CORE_ASSERT(m_shaders.find(name) != m_shaders.end(), "Shaders not found");
		return m_shaders[name];
	}
}