#pragma once

#ifdef PLATFORM_WINDOWS

	#include "Core/Window.h"
	#include "Core/Core.h"
	#include "Renderer/RendererContext.h"

	#include <GLFW/glfw3.h>

	namespace Arrow {

		class WindowsWindow : public Window {
		public:
			WindowsWindow(const WindowProperties& props);
			virtual ~WindowsWindow();

			void OnUpdate() override;

			inline unsigned int GetWidth() const override { return m_Data.Width; }
			inline unsigned int GetHeight() const override { return m_Data.Height; }

			inline void SetEventCallback(const EventFn& callback) override { m_Data.EventCb = callback; }

			void SetVSync(bool enabled) override;
			inline bool GetVSync() const override { return m_Data.IsVSync; }

			inline virtual void* GetNativeWindow() const { return m_Window; }

			inline virtual float GetTime() const override { return (float)glfwGetTime(); }

		private:
			virtual void Init(const WindowProperties& props);
			virtual void Shutdown();
		private:
			GLFWwindow* m_Window;
			RendererContext* m_Context;

			struct WindowData {
				std::string Title;
				unsigned int Width = 1080, Height = 720;
				bool IsVSync = true;

				EventFn EventCb;
			};

			WindowData m_Data;
		};

	}

#endif