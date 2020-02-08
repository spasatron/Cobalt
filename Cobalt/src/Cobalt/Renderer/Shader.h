#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Cobalt {

	class Shader {
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual const std::string& GetName() const = 0;

		virtual void SetInt(const std::string& name, int i) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix4) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& floatVec4) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& floatVec3) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& floatVec2) = 0;

		static Ref<Shader> Create(const std::string& name,const std::string& vertexSrc, const std::string& fragmentSrc);
		static Ref<Shader> Create(const std::string& fileName);
	};

	class ShaderLibrary {
	public:

		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filePath);
		Ref<Shader> Load(const std::string name, const std::string& filePath);

		Ref<Shader> Get(const std::string& name);
	private:
		std::unordered_map<std::string, Ref<Shader>> m_shaders;
	};

}