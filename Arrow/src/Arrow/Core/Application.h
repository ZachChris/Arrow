#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"

#include "Arrow/Events/Events.h"
#include "Arrow/Events/InputEvents.h"
#include "Arrow/Events/ApplicationEvents.h"

#include "Arrow/Renderer/Renderer.h"
#include "Arrow/Renderer/RenderCommand.h"
#include "Arrow/Renderer/Buffers.h"
#include "Arrow/Renderer/Shader.h"
#include "Arrow/Renderer/VertexArray.h"

namespace Arrow {

	class Application {
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		void Run();

		inline static Application& Get() { return *s_Instanse;; }
		inline Window& GetWindow() { return *m_Window; }

		bool OnWindowClose(ApplicationClosedEvent& event);
		bool OnWindowResize(ApplicationResizedEvent& event);

	private:
		//---Window Data---
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		//---DeltaTime Data---
		float lastTime;
		float currentTime;

		//---Application Instance---
		static Application* s_Instanse;
	};

	Application* CreateApplication();

}