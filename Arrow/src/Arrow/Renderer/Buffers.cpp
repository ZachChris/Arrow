#include "arpch.h"

#include "Arrow/Renderer/Buffers.h"
#include "Arrow/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLBuffers.h"

namespace Arrow {

	//-----Vertex Buffer-----//

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* data, uint32_t size) {
		switch (RendererAPI::GetAPI()) {
			case RendererAPI::API::NONE: return nullptr; ASSERT(false, "No API selected"); break;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(data, size); break;
		}

		AR_ERROR("No Vertex Buffer Created");
		return nullptr;
	}

	//-----Index Buffer------//

	std::shared_ptr<IndexBuffer> IndexBuffer::Create(unsigned int* data, uint32_t count) {
		switch (RendererAPI::GetAPI()) {
			case RendererAPI::API::NONE: return nullptr; ASSERT(false, "No API selected"); break;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(data, count); break;
		}

		AR_ERROR("No Index Buffer Created");
		return nullptr;
	}

}