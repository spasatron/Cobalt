#pragma once

#include "Cobalt/Renderer/Buffer.h"

namespace Cobalt {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:

		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		
		virtual ~OpenGLVertexBuffer() override;
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetLayout(const BufferLayout& layout) override;
		virtual const BufferLayout& GetLayout() const override;
		virtual void SetData(const void* data, uint32_t size) override;




	private:
		BufferLayout m_layout;
		uint32_t m_rendererId;
	};


	///////////////////////////////////


	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer() override;
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual uint32_t GetCount() const override {	return m_count;	}


	private:
		uint32_t m_count;
		uint32_t m_rendererId;
	};


}