#include "arpch.h"
#include "OpenGLContext.h"

#include "Core/Core.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Arrow {

	OpenGLContext::OpenGLContext(GLFWwindow* window) 
		:m_Window(window) {}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		ASSERT(status == 0, "Failed to initialize Glad!");

		AR_INFO("OpenGL Info:");
		AR_INFO(" Vendor: {0}", glGetString(GL_VENDOR));
		AR_INFO(" Renderer: {0}", glGetString(GL_RENDERER));
		AR_INFO(" Version: {0}", glGetString(GL_VERSION));

		glEnable(GL_MULTISAMPLE);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glShadeModel(GL_SMOOTH);
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_Window);
	}
}