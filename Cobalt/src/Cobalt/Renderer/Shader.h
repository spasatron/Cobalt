#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Cobalt {

	class Shader {
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void UnBind() const;


		void UploadUniformMat4(const std::string& name, const glm::mat4& uniform);
	private:
		uint32_t m_rendererId;
	};

}