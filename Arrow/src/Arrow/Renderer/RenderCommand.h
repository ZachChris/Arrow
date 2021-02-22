#pragma once

#include "Arrow/Renderer/RendererAPI.h"
#include "Arrow/Renderer/VertexArray.h"
#include "glm/glm.hpp"

namespace Arrow {

	class VertexArray;
	class RendererAPI;
	class Shader;
	class Model;

	enum class DepthMode;

	class RenderCommand {
	public:
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

		static void SetClearColor(const glm::vec4& color);
		static void Clear();

		static void DepthTest(bool value);
		static void DepthMask(bool value);
		static void ChangeDepthMode(DepthMode mode);

		static void BindTexture2D(uint32_t id, uint32_t slot = 0);

		static void BindDrawFramebuffer();

		static void Draw(const std::shared_ptr<Model>& model);
		static void Draw(const std::shared_ptr<VertexArray>& vertexArray);
	private:
		static RendererAPI* s_Instance;
	};

}