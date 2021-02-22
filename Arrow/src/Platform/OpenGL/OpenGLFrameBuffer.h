#pragma once

#include "Arrow/Renderer/FrameBuffer.h"

namespace Arrow {

	class OpenGLFrameBuffer : public FrameBuffer {
	public:
		OpenGLFrameBuffer(const FrameBufferSpecifications& specs);
		virtual ~OpenGLFrameBuffer();

		virtual const FrameBufferSpecifications& GetSpecifications() const override { return m_Specs; }
		virtual const uint32_t& GetColorAttachment() const override { return m_ColorAttachment; }

		virtual const void Bind() override;
		virtual const void Unbind() override;
	private:
		void Invalidate();
	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment, m_DepthAttachment;
		FrameBufferSpecifications m_Specs;
	};

}