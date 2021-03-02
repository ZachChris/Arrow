#include "arpch.h"

#include "Arrow/Renderer/Texture.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Arrow{

	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& filepath, const TextureSpecifications& specs) {
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::NONE: return nullptr; ASSERT(false, "No API selected"); break;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(filepath, specs); break;
		}

		AR_ERROR("No Texture2D Created");
		return nullptr;
	}

	std::shared_ptr<Cubemap> Cubemap::Create(const std::vector<std::string>& filepath) {
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::NONE: return nullptr; ASSERT(false, "No API selected"); break;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLCubemap>(filepath); break;
		}

		AR_ERROR("No Cubemap Created");
		return nullptr;
	}

}