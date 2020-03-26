#include "cbpc.h"

#include "Renderer2D.h"
#include "RenderCommand.h"


#include "Shader.h"
#include "VertexArray.h"

#include <glm/gtc/matrix_transform.hpp>


//We need to remove all of this below eventually




namespace Cobalt {


	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TextureCoord;
		//TODO TextID;
	};

	struct Renderer2DData {
		//Constants For setting the number of draw calls

		const uint32_t MaxQuad = 10000;
		const uint32_t MaxQuadVertex = 4 * MaxQuad;
		const uint32_t MaxQuadIndex = 6 * MaxQuad;

		Ref<VertexArray> m_vertexArray; 
		Ref<VertexBuffer> m_vertexBuffer;
		Ref<Shader> flatColorShader;
		Ref<Shader> textureShader;
		Ref<Shader> fontShader;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
	};

	//Can move this to pointer if needed.
	static Renderer2DData s_data;



	void Renderer2D::Init()
	{
		s_data.m_vertexArray = VertexArray::Create();

		s_data.m_vertexBuffer = VertexBuffer::Create(s_data.MaxQuadVertex * sizeof(QuadVertex));

		BufferLayout layoutSq = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
			{ShaderDataType::Float2, "a_TextureCoord"}
		};

		s_data.m_vertexBuffer->SetLayout(layoutSq);

		//Must be careful here. Might be better to refrence count later.
		//Gen the Quad Indicies

		uint32_t* quadIndices = new uint32_t[s_data.MaxQuadIndex];
		
		uint32_t pos = 0;

		for (uint32_t i = 0; i < s_data.MaxQuadIndex; i += 6) {

			quadIndices[i + 0] = pos + 0;
			quadIndices[i + 1] = pos + 1;
			quadIndices[i + 2] = pos + 2;

			quadIndices[i + 3] = pos + 2;
			quadIndices[i + 4] = pos + 3;
			quadIndices[i + 5] = pos + 0;

			pos += 4;
		}

		Ref<IndexBuffer> m_indexBuffer = IndexBuffer::Create(quadIndices, s_data.MaxQuadIndex);

		
		
		s_data.m_vertexArray->AddVertexBuffer(s_data.m_vertexBuffer);

		s_data.QuadVertexBufferBase = new QuadVertex[s_data.MaxQuadVertex];

		s_data.m_vertexArray->SetIndexBuffer(m_indexBuffer);
			  
		s_data.flatColorShader = Shader::Create("assets/shaders/flatColor.glsl");
		s_data.textureShader = Shader::Create("assets/shaders/texture.glsl");
		s_data.fontShader = Shader::Create("assets/shaders/font.glsl");
		s_data.textureShader->Bind();
		s_data.textureShader->SetInt("u_texture", 0);


		delete[] quadIndices;

		
	}



	void Renderer2D::Shutdown()
	{

	}

	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{

		s_data.QuadVertexBufferPtr = s_data.QuadVertexBufferBase;
		s_data.QuadIndexCount = 0;


		//Bind shader with the current camera settings
		s_data.flatColorShader->Bind();
		s_data.flatColorShader->SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());
	
		s_data.textureShader->Bind();
		s_data.textureShader->SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());

		s_data.fontShader->Bind();
		s_data.fontShader->SetMat4("projection", camera.GetViewProjectionMatrix());


		s_data.flatColorShader->Bind();
	}

	void Renderer2D::EndScene()
	{

		uint32_t dataSize = (uint8_t*)s_data.QuadVertexBufferPtr - (uint8_t*)s_data.QuadVertexBufferBase;
		s_data.m_vertexBuffer->SetData(s_data.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		RenderCommand::DrawIndexed(s_data.m_vertexArray, s_data.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation)
	{

		//Load all of the information into the QuadVertexBufferPtr. This is all displayed at the end of the scene when Flush is called
		s_data.QuadVertexBufferPtr->Position = position;
		s_data.QuadVertexBufferPtr->Color = color;
		s_data.QuadVertexBufferPtr->TextureCoord = {0.0f, 0.0f};
		s_data.QuadVertexBufferPtr++;

		s_data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, position.z};
		s_data.QuadVertexBufferPtr->Color = color;
		s_data.QuadVertexBufferPtr->TextureCoord = { 1.0f, 0.0f };
		s_data.QuadVertexBufferPtr++;

		s_data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		s_data.QuadVertexBufferPtr->Color = color;
		s_data.QuadVertexBufferPtr->TextureCoord = { 1.0f, 1.0f };
		s_data.QuadVertexBufferPtr++;

		s_data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, position.z };
		s_data.QuadVertexBufferPtr->Color = color;
		s_data.QuadVertexBufferPtr->TextureCoord = { 0.0f, 1.0f };
		s_data.QuadVertexBufferPtr++;

		s_data.QuadIndexCount += 6;


		/*
		s_data.flatColorShader->Bind();
		s_data.flatColorShader->SetFloat4("u_color", color);
		//Calculate transform matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data.flatColorShader->SetMat4("u_transform", transform);
		s_data.m_vertexArray->Bind();
		RenderCommand::DrawIndexed(s_data.m_vertexArray);
		*/	
	}


	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, float rotation)
	{
		s_data.textureShader->Bind();
		//Calculate transform matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data.flatColorShader->SetMat4("u_transform", transform);
		s_data.m_vertexArray->Bind();
		texture->Bind();
		RenderCommand::DrawIndexed(s_data.m_vertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, float rotation)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, rotation);
	}


	

}