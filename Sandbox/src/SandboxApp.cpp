#include <Arrow.h>
#include <Arrow/Core/EntryPoint.h>

#include "SandboxLayer.h"

class Sandbox : public Arrow::Application {
public:
	Sandbox() {
		PushLayer(new SandboxLayer());
	}
};

Arrow::Application* Arrow::CreateApplication() {
	return new Sandbox();
}