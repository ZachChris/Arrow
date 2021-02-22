#pragma once

#include "arpch.h"

namespace Arrow {

	class Input {
	public:
		inline static bool KeyPressed(int keyCode) { return s_Instance->KeyPressedImp(keyCode); }
		inline static bool MouseButtonPressed(int button) { return s_Instance->MouseButtonPressedImp(button); }

		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImp(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImp(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImp(); }
	protected:
		virtual bool KeyPressedImp(int keyCode) = 0;
		virtual bool MouseButtonPressedImp(int button) = 0;
		
		virtual std::pair<float, float> GetMousePositionImp() = 0;
		virtual float GetMouseXImp() = 0;
		virtual float GetMouseYImp() = 0;
	private:
		static Input* s_Instance;
	};

}