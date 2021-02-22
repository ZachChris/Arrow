#pragma once

#include "Events.h"

namespace Arrow {

	class ApplicationClosedEvent : public Event {
	public:
		ApplicationClosedEvent() {}

		EVENT_CLASS_CATEGORY(ApplicationFlag)
		EVENT_CLASS_TYPE(ApplicationClosed)
	};

	class ApplicationResizedEvent : public Event {
	public:
		ApplicationResizedEvent(int width, int height) 
		:m_Width(width), m_Height(height) {}

		EVENT_CLASS_CATEGORY(ApplicationFlag)
		EVENT_CLASS_TYPE(ApplicationResized)

		virtual std::string GetLogInfo() const override {
			std::stringstream ss;
			ss << "Window Resized: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		inline int GetWidth() { return m_Width; }
		inline int GetHeight() { return m_Height; }

	private:
		int m_Width, m_Height;
	};

}