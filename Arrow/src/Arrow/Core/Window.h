#pragma once

#include <string>
#include "Arrow/Events/Events.h"

namespace Arrow {

	struct WindowProperties {
		std::string Title;
		unsigned int Width, Height;

		WindowProperties(std::string title = "Arrow Engine", int width = 1280, int height = 720)
			:Title(title), Width(width), Height(height) {}
	};

	class Window {
	public:
		using EventFn = std::function<void(Event&)>;

	public:
		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventFn& callback) = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool GetVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual float GetTime() const = 0;

		static Window* Create(WindowProperties& props = WindowProperties());

	};



}