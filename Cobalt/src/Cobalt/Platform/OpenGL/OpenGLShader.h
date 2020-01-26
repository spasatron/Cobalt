#pragma once


#include "Cobalt/Renderer/Shader.h"
#include <glm/glm.hpp>

//TO DO Remove:
typedef unsigned int GLenum;
//


namespace Cobalt{

	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string name, const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& fileName);
		virtual ~OpenGLShader() override;

		virtual void Bind() const;
		virtual void UnBind() const;
		virtual const std::string& GetName() const override { return m_name; }

		virtual void SetInt(const std::string& name, int i) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix4) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& floatVec4) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& floatVec3) override;

		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& uniform);
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& uniform);
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& uniform);
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& uniform);
		virtual void UploadUniformInt(const std::string& name, int num);
	private:
		std::string ReadFile(const std::string& fileName);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string source);
		void Compile(const std::unordered_map<GLenum, std::string> shaderSources);
	private:
		uint32_t m_rendererId;
		std::string m_name;
	};



}