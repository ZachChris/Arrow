#include "arpch.h"

#ifdef PLATFORM_WINDOWS

	#include "WindowsWindow.h"

	#include "Arrow/Events/ApplicationEvents.h"
	#include "Arrow/Events/InputEvents.h"

	#include "Platform/OpenGL/OpenGLContext.h"

	namespace Arrow {
		static bool glInitialized = false;

		void GLFWErrorCallback(int error, const char* message) {
			AR_ERROR("Error: {0} {1}", error, message);
		}

		Window* Window::Create(WindowProperties& props) {
			return new WindowsWindow(props);
		}

		WindowsWindow::WindowsWindow(const WindowProperties& props) {
			Init(props);
		}

		WindowsWindow::~WindowsWindow() {
			Shutdown();
		}

		void WindowsWindow::Init(const WindowProperties& props) {
			m_Data.Title = props.Title;
			m_Data.Width = props.Width;
			m_Data.Height = props.Height;

			if (!glInitialized) {
				int success = glfwInit();

				glfwSetErrorCallback(GLFWErrorCallback);
				glInitialized = true;
			}

			m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);

			m_Context = new OpenGLContext(m_Window);
			m_Context->Init();

			glfwSetWindowUserPointer(m_Window, &m_Data);
			SetVSync(true);

			glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				ApplicationResizedEvent event(width, height);
				data.EventCb(event);
				});

			glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				ApplicationClosedEvent event;
				data.EventCb(event);
				});

			glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action) {
					case GLFW_PRESS: {
						KeyPressedEvent event(key, 0);
						data.EventCb(event);
						break;
					}
					case GLFW_REPEAT: {
						KeyPressedEvent event(key, 1);
						data.EventCb(event);
						break;
					}
					case GLFW_RELEASE: {
						KeyReleasedEvent event(key);
						data.EventCb(event);
						break;
					}
				}
			});

			glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action) {
					case GLFW_PRESS: {
						MouseButtonPressedEvent event(button, 0);
						data.EventCb(event);
						break;
					}
					case GLFW_REPEAT: {
						MouseButtonPressedEvent event(button, 1);
						data.EventCb(event);
						break;
					}
					case GLFW_RELEASE: {
						MouseButtonReleasedEvent event(button);
						data.EventCb(event);
						break;
					}
				}
			});

			glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCb(event);
			});

			glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCb(event);
			});

		}

		void WindowsWindow::Shutdown() {
			glfwDestroyWindow(m_Window);
		}

		void WindowsWindow::OnUpdate() {
			glfwPollEvents();
			m_Context->SwapBuffers();
		}

		void WindowsWindow::SetVSync(bool enabled) {
			m_Data.IsVSync = enabled;

			if (enabled)
				glfwSwapInterval(1);
			else
				glfwSwapInterval(0);
		}

	}

#endif