#pragma once

#include <string>

namespace Arrow {

	enum class EventClass {
		NONE = 0,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		ApplicationClosed, ApplicationResized
	};

	enum EventFlags {
		NONE = 0,
		ApplicationFlag,
		InputFlag,
		KeyboardFlag,
		MouseFlag,
		MouseButtonFlag
	};

	class Event {
		friend class EventDispacher;
	public:
		virtual EventClass GetEventClass() const = 0;
		virtual int GetFlags() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string GetLogInfo() const { return GetName(); };
	public:
		bool Handeled = false;
	};

	#define EVENT_CLASS_TYPE(type)  static EventClass GetStaticClass() { return EventClass::##type; }\
									virtual EventClass GetEventClass() const override { return GetStaticClass(); }\
									virtual const char* GetName() const override { return #type; }

	#define EVENT_CLASS_CATEGORY(category) virtual int GetFlags() const override { return category; }


	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			:m_Event(event) {
		}

		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventClass() == T::GetStaticClass()) {
				m_Event.Handeled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.GetLogInfo();
	}
	
}
