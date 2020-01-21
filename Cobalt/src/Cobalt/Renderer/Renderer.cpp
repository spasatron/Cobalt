#include "cbpc.h"

#include "Renderer.h"

#include "Cobalt/Platform/OpenGL/OpenGLShader.h"

namespace Cobalt {


	Renderer::SceneData* Renderer::m_sceneData = new Renderer::SceneData;

	void Renderer::Init(){
		RenderCommand::Init();
	}

	void Renderer::BeginScene(OrthographicCamera& camera) {
		m_sceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene() {

	}
	void Renderer::Submit(const Ref<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform) {




		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_viewProjection", m_sceneData->viewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}