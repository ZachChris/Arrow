#pragma once

namespace Arrow {

	struct FrameBufferSpecifications {
		uint32_t Width, Height;
		int Sambles = 1;
		bool SwapChainTarget = false;
	};

	class FrameBuffer {
	public:
		virtual ~FrameBuffer() {}

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual const FrameBufferSpecifications& GetSpecifications() const = 0;
		virtual const uint32_t& GetColorAttachment() const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static std::shared_ptr<FrameBuffer> Create(const FrameBufferSpecifications& specs);
	};

}