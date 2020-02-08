#include "cbpc.h"

#include "Renderer.h"
#include "Renderer2D.h"

#include "Cobalt/Platform/OpenGL/OpenGLShader.h"

namespace Cobalt {


	Renderer::SceneData* Renderer::m_sceneData = new Renderer::SceneData;

	void Renderer::Init(){
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height){
		RenderCommand::SetViewPort(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera) {
		m_sceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene() {

	}
	void Renderer::Submit(const Ref<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform) {




		shader->Bind();
		shader->SetMat4("u_viewProjection", m_sceneData->viewProjectionMatrix);
		shader->SetMat4("u_transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}