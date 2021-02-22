#pragma once

#include "Arrow/Renderer/VertexArray.h"
#include "glm/glm.hpp"

namespace Arrow {

	class VertexArray;
	class Shader;
	class Model;

	enum class DepthMode {
		Always, Never, Less, Equal,
		Lequal, Greater, Notequal, Gequal
	};

	class RendererAPI {
	public:
		enum class API {
			NONE = 0, OpenGL = 1
		};
	public:
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DepthTest(bool value) = 0;
		virtual void DepthMask(bool value) = 0;
		virtual void ChangeDepthMode(DepthMode mode) = 0;

		virtual void BindTexture2D(uint32_t id, uint32_t slot) = 0;

		virtual void BindDrawFramebuffer() = 0;

		virtual void Draw(const std::shared_ptr<Model>& model) = 0;
		virtual void Draw(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }
		inline static void SetAPI(API api) { s_API = api; }
	private:
		static API s_API;
	};

}