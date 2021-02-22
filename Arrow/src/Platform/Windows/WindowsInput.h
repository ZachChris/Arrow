#pragma once

#include "Input/Input.h"

namespace Arrow {

	class WindowsInput : public Input {
	protected:
		virtual bool KeyPressedImp(int keyCode) override;
		virtual bool MouseButtonPressedImp(int button) override;

		virtual std::pair<float, float> GetMousePositionImp() override;
		virtual float GetMouseXImp() override;
		virtual float GetMouseYImp() override;
	};

}