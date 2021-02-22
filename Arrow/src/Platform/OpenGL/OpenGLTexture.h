#pragma once

#include "Arrow/Renderer/Texture.h"

#include <glad/glad.h>

namespace Arrow {

	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const std::string& filepath);
		~OpenGLTexture2D();

		inline int GetWidth() override { return m_Width; }
		inline int GetHeight() override { return m_Height; }

		void Bind(uint32_t slot) const override;
		void Unbind() const override;

	private:
		uint32_t m_RendererID;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, m_BPP;
	};

	class OpenGLCubemap : public Cubemap {
	public:
		OpenGLCubemap(const std::vector<std::string>& filepath);
		~OpenGLCubemap();

		inline int GetWidth() override { return m_Width; }
		inline int GetHeight() override { return m_Height; }

		void Bind(uint32_t slot) const override;
		void Unbind() const override;

	private:
		uint32_t m_RendererID;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, m_BPP;
	};

}