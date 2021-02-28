#include "arpch.h"

#include "Arrow/Renderer/FrameBuffer.h"
#include "Arrow/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Arrow {

	std::shared_ptr<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecifications& specs) {
		switch (RendererAPI::GetAPI()) {
			case RendererAPI::API::NONE: return nullptr; ASSERT(false, "No API selected"); break;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLFrameBuffer>(specs); break;
		}

		AR_ERROR("No Vertex Buffer Created");
		return nullptr;
	}

}