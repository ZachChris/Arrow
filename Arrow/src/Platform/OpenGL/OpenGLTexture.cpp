#include "arpch.h"

#include "Platform/OpenGL/OpenGLTexture.h"

#include "stb_image.h"

namespace Arrow {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath) {
		stbi_set_flip_vertically_on_load(1);
		m_LocalBuffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

		glGenTextures(1, &m_RendererID);
		Bind(0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
		Unbind();

		if (m_LocalBuffer)
			stbi_image_free(m_LocalBuffer);
		else
			AR_ERROR("No Texture2D data!!!");
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void OpenGLTexture2D::Unbind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	OpenGLCubemap::OpenGLCubemap(const std::vector<std::string>& filepaths) {
		glGenTextures(1, &m_RendererID);
		Bind(0);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		stbi_set_flip_vertically_on_load(0);
		for (unsigned int i = 0; i < filepaths.size(); i++) {
			m_LocalBuffer = stbi_load(filepaths[i].c_str(), &m_Width, &m_Height, &m_BPP, 0);
			if (m_LocalBuffer) {
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer);
				stbi_image_free(m_LocalBuffer);
			} else
				AR_ERROR("No Cubemap data({0})!!!", i+1);
		}
	}

	OpenGLCubemap::~OpenGLCubemap() {
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLCubemap::Bind(uint32_t slot) const {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
	}

	void OpenGLCubemap::Unbind() const {
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}