#pragma once


#include "Cobalt/Renderer/Shader.h"
#include <glm/glm.hpp>


namespace Cobalt{

	class OpenGLShader : public Shader {
		public:
			OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
			virtual ~OpenGLShader() override;

			virtual void Bind() const;
			virtual void UnBind() const;


			virtual void UploadUniformMat4(const std::string& name, const glm::mat4& uniform);
		private:
			uint32_t m_rendererId;

	};



}