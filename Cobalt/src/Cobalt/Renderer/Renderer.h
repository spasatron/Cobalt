#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Cobalt {

	class Renderer {
	public:

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));


		inline static RendererAPI::API GetRendererAPI() { return RendererAPI::GetAPI(); }

	private:

		struct SceneData {
			glm::mat4 viewProjectionMatrix;
		};

		static SceneData* m_sceneData;

	};


}