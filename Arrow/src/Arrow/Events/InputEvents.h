#pragma once

#include "Events.h"
#include <sstream>

namespace Arrow {

	class KeyPressedEvent : public Event {
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			:m_KeyCode(keyCode), m_RepeatCount(repeatCount) {}

		EVENT_CLASS_CATEGORY(KeyboardFlag | InputFlag)
		EVENT_CLASS_TYPE(KeyPressed)

		virtual std::string GetLogInfo() const override { 
			std::stringstream ss;
			ss << "KeyPressed: " << m_KeyCode << ", " << m_RepeatCount;
			return ss.str();
		}

		inline int GetKeyCode() { return m_KeyCode; }
		inline int GetRepeatCount() { return m_RepeatCount; }

	private:
		int m_KeyCode, m_RepeatCount;
	};

	class KeyReleasedEvent : public Event {
	public:
		KeyReleasedEvent(int keyCode)
			:m_KeyCode(keyCode) {}

		EVENT_CLASS_CATEGORY(KeyboardFlag | InputFlag)
		EVENT_CLASS_TYPE(KeyReleased)

		virtual std::string GetLogInfo() const override {
			std::stringstream ss;
			ss << "KeyReleased: " << m_KeyCode;
			return ss.str();
		}

		inline int GetKeyCode() { return m_KeyCode; }

	private:
		int m_KeyCode;
	};

	class MouseButtonPressedEvent : public Event {
	public:
		MouseButtonPressedEvent(int buttonCode, int repeatCount)
			:m_ButtonCode(buttonCode) ,m_RepeatCount(repeatCount) {
		}

		EVENT_CLASS_CATEGORY(MouseButtonFlag | InputFlag)
		EVENT_CLASS_TYPE(MouseButtonPressed)

		virtual std::string GetLogInfo() const override {
			std::stringstream ss;
			ss << "MouseButtonPressed: " << m_ButtonCode;
			return ss.str();
		}

		inline int GetKeyCode() { return m_ButtonCode; }

	private:
		int m_ButtonCode;
		int m_RepeatCount;
	};

	class MouseButtonReleasedEvent : public Event {
	public:
		MouseButtonReleasedEvent(int buttonCode)
			:m_ButtonCode(buttonCode) {
		}

		EVENT_CLASS_CATEGORY(MouseButtonFlag | InputFlag)
		EVENT_CLASS_TYPE(MouseButtonReleased)

		virtual std::string GetLogInfo() const override {
			std::stringstream ss;
			ss << "MouseButtonReleased: " << m_ButtonCode;
			return ss.str();
		}

		inline int GetKeyCode() { return m_ButtonCode; }

	private:
		int m_ButtonCode;
	};

	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float mouseX, float mouseY)
			: m_MouseX(mouseX), m_MouseY(mouseY) {}

		EVENT_CLASS_CATEGORY(MouseFlag)
		EVENT_CLASS_TYPE(MouseMoved)

		virtual std::string GetLogInfo() const override {
			std::stringstream ss;
			ss << "MouseMoved: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		inline float GetMouseX() const { return m_MouseX; }
		inline float GetMouseY() const { return m_MouseY; }

	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event {
	public:

		MouseScrolledEvent(float scrollX, float scrollY)
			: m_ScrollX(scrollX), m_ScrollY(scrollY) {
		}

		EVENT_CLASS_CATEGORY(MouseFlag)
		EVENT_CLASS_TYPE(MouseScrolled)

		virtual std::string GetLogInfo() const override {
			std::stringstream ss;
			ss << "MouseScrolled: " << m_ScrollX << ", " << m_ScrollY;
			return ss.str();
		}

		inline float GetMouseScrollX() const { return m_ScrollX; }
		inline float GetMouseScrollY() const { return m_ScrollY; }

	private:
		float m_ScrollX, m_ScrollY;
	};

}