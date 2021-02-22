#include "arpch.h"

#include "WindowsInput.h"
#include "WindowsWindow.h"
#include "Core/Application.h"

namespace Arrow {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::KeyPressedImp(int keyCode) {
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::MouseButtonPressedImp(int button) {
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImp() {
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		return { (float)mouseX, (float)mouseY };
	}

	float WindowsInput::GetMouseXImp() {
		auto [x, y] = GetMousePositionImp();
		return x;
	}

	float WindowsInput::GetMouseYImp() {
		auto [x, y] = GetMousePositionImp();
		return y;
	}

}