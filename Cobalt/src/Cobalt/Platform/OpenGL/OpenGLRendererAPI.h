#pragma once

#include "Cobalt/Renderer/RendererAPI.h"


namespace Cobalt {

	class OpenGLRendererAPI : public RendererAPI {
	public:
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;


	};



}