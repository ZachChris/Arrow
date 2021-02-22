#include "arpch.h"

#include "OpenGLRendererAPI.h"
#include <glad/glad.h>

namespace Arrow {

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void OpenGLRendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DepthTest(bool value) {
		if (value)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::DepthMask(bool value) {
		if (value)
			glDepthMask(GL_TRUE);
		else
			glDepthMask(GL_FALSE);
	}

	void OpenGLRendererAPI::ChangeDepthMode(DepthMode mode) {
		switch (mode) {
			case DepthMode::Always: glDepthFunc(GL_ALWAYS); break;
			case DepthMode::Never: glDepthFunc(GL_NEVER); break;
			case DepthMode::Less: glDepthFunc(GL_LESS); break;
			case DepthMode::Equal: glDepthFunc(GL_EQUAL); break;
			case DepthMode::Lequal: glDepthFunc(GL_LEQUAL); break;
			case DepthMode::Greater: glDepthFunc(GL_GREATER); break;
			case DepthMode::Notequal: glDepthFunc(GL_NOTEQUAL); break;
			case DepthMode::Gequal: glDepthFunc(GL_GEQUAL); break;
		}

	}

	void OpenGLRendererAPI::BindTexture2D(uint32_t id, uint32_t slot) {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void OpenGLRendererAPI::BindDrawFramebuffer() {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	void OpenGLRendererAPI::Draw(const std::shared_ptr<Model>& model) {
		model->GetVertexBuffer()->Bind();
		model->GetIndexBuffer()->Bind();
		int count = model->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::Draw(const std::shared_ptr<VertexArray>& vertexArray) {
		vertexArray->Bind();
		vertexArray->GetIndexBuffer()->Bind();
		int count = vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

}