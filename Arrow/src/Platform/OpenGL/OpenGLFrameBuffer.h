#pragma once

#include "Arrow/Renderer/FrameBuffer.h"

namespace Arrow {

	class OpenGLFrameBuffer : public FrameBuffer {
	public:
		OpenGLFrameBuffer(const FrameBufferSpecifications& specs);
		virtual ~OpenGLFrameBuffer();

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual const FrameBufferSpecifications& GetSpecifications() const override { return m_Specs; }
		virtual const uint32_t& GetColorAttachment() const override { return m_ColorAttachment; }

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		void Invalidate();
	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
		FrameBufferSpecifications m_Specs;
	};

}