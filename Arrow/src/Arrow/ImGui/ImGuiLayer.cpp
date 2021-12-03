#include "arpch.h"

#include "ImGuiLayer.h"

#include "Arrow/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLImGuiLayer.h"

namespace Arrow {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer") {}

	ImGuiLayer::~ImGuiLayer() {}

	ImGuiLayer* CreateImGuiLayer() {
		switch (RendererAPI::GetAPI()) {
			case RendererAPI::API::NONE: ASSERT(false, "No API selected"); break;
			case RendererAPI::API::OpenGL:return new OpenGLImGuiLayer; break;
		}
	}

}