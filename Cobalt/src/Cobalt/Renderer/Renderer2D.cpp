#include "cbpc.h"

#include "Renderer2D.h"
#include "RenderCommand.h"


#include "Shader.h"
#include "VertexArray.h"

#include <glm/gtc/matrix_transform.hpp>


//We need to remove all of this below eventually

#include <glad/glad.h>



namespace Cobalt {

	struct Renderer2DStorage {
		Ref<VertexArray> m_vertexArray;
		Ref<Shader> flatColorShader;
		Ref<Shader> textureShader;
		Ref<Shader> fontShader;
		texture_atlas_t* atlas;
		texture_font_t* font;
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
		s_data->fontShader = Shader::Create("assets/shaders/font.glsl");
		s_data->textureShader->Bind();
		s_data->textureShader->SetInt("u_texture", 0);




		//To remove
		s_data->atlas = texture_atlas_new(512, 512, 1);
		s_data->font = texture_font_new_from_file(s_data->atlas, 32, "assets/fonts/handy00.ttf");
	}



	void Renderer2D::Shutdown()
	{
		glDeleteTextures(1, &s_data->atlas->id);
		delete s_data;
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		//Bind shader with the current camera settings
		s_data->flatColorShader->Bind();
		s_data->flatColorShader->SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());
	
		s_data->textureShader->Bind();
		s_data->textureShader->SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());

		s_data->fontShader->Bind();
		s_data->fontShader->SetMat4("projection", camera.GetViewProjectionMatrix());
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

	void Renderer2D::RenderText(const std::string& text, const glm::vec2& pos, const glm::vec4& color)
	{
		
		texture_font_get_glyph(s_data->font, text.c_str());

		glGenTextures(1, &s_data->atlas->id);
		glBindTexture(GL_TEXTURE_2D, s_data->atlas->id);

	}

	

}