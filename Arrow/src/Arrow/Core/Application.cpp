#include "arpch.h"
#include "Application.h"
#include "Log.h"

#include "Input/Input.h"
#include "Input/KeyCodes.h"
#include "Input/MouseCodes.h"

#include "DeltaTime.h"

namespace Arrow {
	
	Application* Application::s_Instanse = nullptr;

	Application::Application() {
		s_Instanse = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(&Application::OnEvent));

		lastTime = m_Window->GetTime();

		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() {
	}

	void Application::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
			if (event.Handeled)
				break;
			(*it)->OnEvent(event);
		}

		dispatcher.Dispatch<ApplicationClosedEvent>(BIND_EVENT_FN(&Application::OnWindowClose));
		dispatcher.Dispatch<ApplicationResizedEvent>(BIND_EVENT_FN(&Application::OnWindowResize));
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::PopLayer(Layer* layer) {
		m_LayerStack.PopLayer(layer);
		layer->OnDetach();
	}

	void Application::PopOverlay(Layer* overlay) {
		m_LayerStack.PopOverlay(overlay);
		overlay->OnDetach();
	}

	void Application::Run() {

		while (m_Running) {
			currentTime = m_Window->GetTime();
			DeltaTime deltaTime(currentTime - lastTime);
			lastTime = currentTime;

			for (auto layer : m_LayerStack)
				layer->OnUpdate(deltaTime);

			m_ImGuiLayer->Begin();
			for (auto layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(ApplicationClosedEvent& event) {
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(ApplicationResizedEvent& event) {
		if (event.GetWidth() == 0 || event.GetHeight() == 0) {
			m_Minimized = true;
		} else
			m_Minimized = false;

		RenderCommand::SetViewport(0, 0, event.GetWidth(), event.GetHeight());

		return true;
	}

}