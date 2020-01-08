#include "cbpc.h"
#include "Shader.h"

#include <glad/glad.h>

Cobalt::Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc){


		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const GLchar* source = (const GLchar*)vertexSrc.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	// Compile the vertex shader
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(vertexShader);

		
		COBALT_CORE_ERROR("{0}", infoLog.data());
		COBALT_CORE_ASSERT(false, "Vertex Shader Failed to Compile:");
		return;
	}

	// Create an empty fragment shader handle
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	source = (const GLchar*)fragmentSrc.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	// Compile the fragment shader
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(fragmentShader);
		// Either of them. Don't leak shaders.
		glDeleteShader(vertexShader);

		// Use the infoLog as you see fit.

		// In this simple program, we'll just leave
		
		COBALT_CORE_ERROR("{0}", infoLog.data());
		COBALT_CORE_ASSERT(false, "Fragment Shader Failed to Compile:");
		return;

	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	m_rendererId = glCreateProgram();

	// Attach our shaders to our program
	glAttachShader(m_rendererId, vertexShader);
	glAttachShader(m_rendererId, fragmentShader);

	// Link our program
	glLinkProgram(m_rendererId);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(m_rendererId, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_rendererId, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_rendererId, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(m_rendererId);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Use the infoLog as you see fit.
		COBALT_CORE_ERROR("{0}", infoLog.data());
		COBALT_CORE_ASSERT(false, "Linking Failed:");
		// In this simple program, we'll just leave
		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(m_rendererId, vertexShader);
	glDetachShader(m_rendererId, fragmentShader);


}

Cobalt::Shader::~Shader(){
	glDeleteProgram(m_rendererId);
}

void Cobalt::Shader::Bind() const{
	glUseProgram(m_rendererId);
}

void Cobalt::Shader::UnBind() const{
	glUseProgram(0);
}
