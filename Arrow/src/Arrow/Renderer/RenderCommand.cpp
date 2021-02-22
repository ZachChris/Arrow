#include "arpch.h"

#include "Arrow/Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Arrow {

	RendererAPI* RenderCommand::s_Instance = new OpenGLRendererAPI();

	void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_Instance->SetViewport(x, y, width, height); }

	void RenderCommand::SetClearColor(const glm::vec4& color) { s_Instance->SetClearColor(color); }
	void RenderCommand::Clear() { s_Instance->Clear(); }

	void RenderCommand::DepthTest(bool value) { s_Instance->DepthTest(value); }
	void RenderCommand::DepthMask(bool value) { s_Instance->DepthMask(value); }
	void RenderCommand::ChangeDepthMode(DepthMode mode) { s_Instance->ChangeDepthMode(mode); }

	void RenderCommand::BindTexture2D(uint32_t id, uint32_t slot) { s_Instance->BindTexture2D(id, slot); }

	void RenderCommand::BindDrawFramebuffer() { s_Instance->BindDrawFramebuffer(); }

	void RenderCommand::Draw(const std::shared_ptr<Model>& model) { s_Instance->Draw(model); }
	void RenderCommand::Draw(const std::shared_ptr<VertexArray>& vertexArray) { s_Instance->Draw(vertexArray); }

}