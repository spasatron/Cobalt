#include "cbpc.h"

#include "OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <glad/glad.h>

namespace Cobalt {

	static GLenum ShaderTypeFromString(const std::string& type) {
		if (type == "vertex") 
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		COBALT_CORE_ASSERT(nullptr, "Unknown Shader Type");
		return 0;
	}




	OpenGLShader::OpenGLShader(const std::string name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_name(name)
	{
		
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);

		


	}

	OpenGLShader::OpenGLShader(const std::string& fileName)
	{
		std::string source = ReadFile(fileName);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);
		// assets/shaders.texture.glsl
		// extracts texture from filepath
		auto lastSlash = fileName.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = fileName.rfind('.');
		auto count = lastDot == std::string::npos ? fileName.size() - lastSlash : lastDot - lastSlash;
		m_name = fileName.substr(lastSlash, count);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_rendererId);
	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_rendererId);
	}

	void OpenGLShader::UnBind() const {
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int i)
	{
		UploadUniformInt(name, i);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& matrix4)
	{
		UploadUniformMat4(name, matrix4);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& floatVec4)
	{
		UploadUniformFloat4(name, floatVec4);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& floatVec3)
	{
		UploadUniformFloat3(name, floatVec3);
	}


	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& uniform)
	{
		GLint location = glGetUniformLocation(m_rendererId, name.c_str());
		glUniform2f(location, uniform.x, uniform.y);
	}
	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& uniform)
	{
		GLint location = glGetUniformLocation(m_rendererId, name.c_str());
		glUniform3f(location, uniform.x, uniform.y, uniform.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& uniform)
	{
		GLint location = glGetUniformLocation(m_rendererId, name.c_str());
		glUniform4f(location, uniform.x, uniform.y, uniform.z, uniform.w);
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& uniform) {
		GLint location = glGetUniformLocation(m_rendererId, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
	}
	void OpenGLShader::UploadUniformInt(const std::string& name, int num){
		GLint location = glGetUniformLocation(m_rendererId, name.c_str());
		glUniform1i(location, num);
	}
	std::string OpenGLShader::ReadFile(const std::string& fileName)
	{
		std::string result;
		std::ifstream in(fileName, std::ios::in | std::ios::binary);

		if (in) {

			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else {
			COBALT_CORE_ERROR("Could not open file {0}", fileName);
		}
		return result;
	}
	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string source){
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);
			COBALT_CORE_ASSERT(eol != std::string::npos, "Syntax Error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol- begin);
			COBALT_CORE_ASSERT(type == "vertex" || type == "pixel"|| type == "fragment", "Invalid Shader Type Specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}
	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string> shaderSources){
		GLuint program = glCreateProgram();
		COBALT_CORE_ASSERT(shaderSources.size() <= 2, "Only 2 Shaders are supported at the moment")
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;
		for (auto& keyValue : shaderSources) {
			GLenum sourceType = keyValue.first;
			const std::string& sourceString = keyValue.second;

			GLuint shader = glCreateShader(sourceType);

			// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
			const GLchar* source = (const GLchar*)sourceString.c_str();
			glShaderSource(shader, 1, &source, 0);

			// Compile the vertex shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);


				COBALT_CORE_ERROR("{0}", infoLog.data());
				COBALT_CORE_ASSERT(false, "Shader Failed to Compile:");
				break;
			}
			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}
		

	
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (auto id : glShaderIDs)
				glDeleteShader(id);

			// Use the infoLog as you see fit.
			COBALT_CORE_ERROR("{0}", infoLog.data());
			COBALT_CORE_ASSERT(false, "Linking Failed:");
			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		for (auto id : glShaderIDs)
			glDetachShader(program, id);

		m_rendererId = program;
	}
}