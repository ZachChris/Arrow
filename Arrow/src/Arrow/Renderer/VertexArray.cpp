#include "arpch.h"

#include "Arrow/Renderer/VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Arrow {

	Ref<VertexArray> VertexArray::Create() {
		switch (RendererAPI::GetAPI()) {
			case RendererAPI::API::NONE: return nullptr; AR_ERROR("No API selected!!!"); break;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>(); break;
		}

		AR_ERROR("No Vertex Array Created!!!");
		return nullptr;
	}
}