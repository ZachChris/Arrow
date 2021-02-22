#pragma once

	extern Arrow::Application* Arrow::CreateApplication();

	int main(int argc, char** argv) {
		Arrow::Log::Init();

		auto app = Arrow::CreateApplication();
		app->Run();
		delete app;
	}
