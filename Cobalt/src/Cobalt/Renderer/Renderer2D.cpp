#include "cbpc.h"

#include "Renderer2D.h"
#include "RenderCommand.h"


#include "Shader.h"
#include "VertexArray.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Cobalt {

	struct Renderer2DStorage {
		Ref<VertexArray> m_vertexArray;
		Ref<Shader> flatColorShader;
		Ref<Shader> textureShader;
	};

	static Renderer2DStorage* s_data;

	void Renderer2D::Init()
	{
		s_data = new Renderer2DStorage();
		s_data->m_vertexArray = VertexArray::Create();

		float verticesRec[5 * 4] = {
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};
		Ref<VertexBuffer> m_vertexBuffer = VertexBuffer::Create(verticesRec, sizeof(verticesRec));

		BufferLayout layoutSq = {
			{ShaderDataType::Float3, "vertices"},
			{ShaderDataType::Float2, "textureCoords"}
		};
		m_vertexBuffer->SetLayout(layoutSq);
		uint32_t indicesSq[6] = { 0, 1, 2, 2, 3, 0 };

		Ref<IndexBuffer> m_indexBuffer = IndexBuffer::Create(indicesSq, sizeof(indicesSq) / sizeof(uint32_t));
		s_data->m_vertexArray->AddVertexBuffer(m_vertexBuffer);
		s_data->m_vertexArray->SetIndexBuffer(m_indexBuffer);

		s_data->flatColorShader = Shader::Create("assets/shaders/flatColor.glsl");
		s_data->textureShader = Shader::Create("assets/shaders/texture.glsl");
		s_data->textureShader->Bind();
		s_data->textureShader->SetInt("u_texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_data;
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		//Bind shader with the current camera settings
		s_data->flatColorShader->Bind();
		s_data->flatColorShader->SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());
	
		s_data->textureShader->Bind();
		s_data->textureShader->SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		s_data->flatColorShader->Bind();
		s_data->flatColorShader->SetFloat4("u_color", color);
		//Calculate transform matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data->flatColorShader->SetMat4("u_transform", transform);
		s_data->m_vertexArray->Bind();
		RenderCommand::DrawIndexed(s_data->m_vertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, float rotation)
	{
		s_data->textureShader->Bind();
		//Calculate transform matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data->flatColorShader->SetMat4("u_transform", transform);
		s_data->m_vertexArray->Bind();
		texture->Bind();
		RenderCommand::DrawIndexed(s_data->m_vertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, float rotation)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, rotation);
	}

}