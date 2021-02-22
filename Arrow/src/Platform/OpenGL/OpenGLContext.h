#pragma once

#include "Renderer\RendererContext.h"

struct GLFWwindow;

namespace Arrow {

	class OpenGLContext : public RendererContext {
	public:
		OpenGLContext(GLFWwindow* window);
		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_Window;
	};
}