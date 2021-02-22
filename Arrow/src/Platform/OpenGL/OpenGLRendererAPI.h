#pragma once

#include "Arrow/Renderer/RendererAPI.h"

namespace Arrow {

	class OpenGLRendererAPI : public RendererAPI {
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DepthTest(bool value) override;
		virtual void DepthMask(bool value) override;
		virtual void ChangeDepthMode(DepthMode mode) override;

		virtual void BindTexture2D(uint32_t id, uint32_t slot) override;

		virtual void BindDrawFramebuffer() override;

		virtual void Draw(const std::shared_ptr<Model>& model) override;
		virtual void Draw(const std::shared_ptr<VertexArray>& vertexArray) override;
	};

}