#pragma once

#include "Arrow/Core/Core.h"
#include "Arrow/Renderer/Renderer.h"

#include <string>

namespace Arrow {

	enum class TextureFormat {
		Red, RG, RGB, RGBA, Depth, DepthStencil
	};

	struct TextureSpecifications {
		TextureFormat Format;
		//To DO: Parametri

		TextureSpecifications(TextureFormat format = TextureFormat::RGBA)
			: Format(format) {}
	};

	class Texture {
	public:
		virtual int GetWidth() = 0;
		virtual int GetHeight() = 0;

		virtual void Bind(uint32_t slot) const = 0;
		virtual void Unbind() const = 0;
	};

	class Texture2D : public Texture {
	public:
		virtual ~Texture2D() {}

		virtual int GetWidth() override = 0;
		virtual int GetHeight() override = 0;

		virtual void Bind(uint32_t slot = 0)  const override= 0;
		virtual void Unbind() const override = 0;

		static std::shared_ptr<Texture2D> Create(const std::string& filepath, const TextureSpecifications& specs = TextureSpecifications());
	};

	class Cubemap : public Texture {
	public:
		virtual int GetWidth() override = 0;
		virtual int GetHeight() override = 0;

		virtual void Bind(uint32_t slot = 0) const override = 0;
		virtual void Unbind() const override = 0;

		static std::shared_ptr<Cubemap> Create(const std::vector<std::string>& filepath);
	};
}