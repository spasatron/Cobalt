#pragma once

#include "Cobalt/Renderer/VertexArray.h"


namespace Cobalt {

	class OpenGLVertexArray : public VertexArray{
	public:

		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() override{}


		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_vertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_indexBuffer; }


	private:
		std::vector<Ref<VertexBuffer>> m_vertexBuffers;
		Ref<IndexBuffer> m_indexBuffer;
		uint32_t m_rendererId;
	};

}