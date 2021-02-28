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

		virtual const FrameBufferSpecifications& GetSpecifications() const = 0;
		virtual const uint32_t& GetColorAttachment() const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static std::shared_ptr<FrameBuffer> Create(const FrameBufferSpecifications& specs);
	};

}