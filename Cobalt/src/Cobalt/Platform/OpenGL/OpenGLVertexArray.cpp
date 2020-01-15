#include "cbpc.h"

#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Cobalt {

	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type) {
		switch (type)
		{

		case Cobalt::ShaderDataType::Float:

		case Cobalt::ShaderDataType::Float2:

		case Cobalt::ShaderDataType::Float3:

		case Cobalt::ShaderDataType::Float4:

		case Cobalt::ShaderDataType::Mat3:

		case Cobalt::ShaderDataType::Mat4:
			return GL_FLOAT;

		case Cobalt::ShaderDataType::Int:

		case Cobalt::ShaderDataType::Int2:

		case Cobalt::ShaderDataType::Int3:

		case Cobalt::ShaderDataType::Int4:
			return GL_INT;

		case Cobalt::ShaderDataType::Bool:
			return GL_BOOL;
		}

		COBALT_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;

	}


	OpenGLVertexArray::OpenGLVertexArray(){
		glCreateVertexArrays(1, &m_rendererId);


	}

	void OpenGLVertexArray::Bind() const{
		glBindVertexArray(m_rendererId);
	}

	void OpenGLVertexArray::UnBind() const{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer){
		COBALT_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "No Layout Selected for vertex Buffer");
		glBindVertexArray(m_rendererId);
		vertexBuffer->Bind();

		
		const auto& layout = vertexBuffer->GetLayout();
		uint32_t index = 0;
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLType(element.type), element.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.offset);
			index++;
		}
		m_vertexBuffers.push_back(vertexBuffer);

	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer){
		glBindVertexArray(m_rendererId);
		indexBuffer->Bind();
		m_indexBuffer = indexBuffer;
	}

}