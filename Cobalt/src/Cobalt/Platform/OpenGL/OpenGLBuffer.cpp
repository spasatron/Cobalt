#include "cbpc.h"
#include "OpenGLBuffer.h"
#include "glad/glad.h"


namespace Cobalt {


	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		glCreateBuffers(1, &m_rendererId);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size){

		glCreateBuffers(1, &m_rendererId);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	}

	

	OpenGLVertexBuffer::~OpenGLVertexBuffer(){
		glDeleteBuffers(1, &m_rendererId);
	}

	void OpenGLVertexBuffer::Bind() const{
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
	}

	void OpenGLVertexBuffer::UnBind() const{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout){
		m_layout = layout;
	}

	const BufferLayout& OpenGLVertexBuffer::GetLayout() const{
		return m_layout;
	}

	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);


	}



	////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : m_count(count){

		glCreateBuffers(1, &m_rendererId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer(){
		glDeleteBuffers(1, &m_rendererId);
	}

	void OpenGLIndexBuffer::Bind() const{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
	}

	void OpenGLIndexBuffer::UnBind() const{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}