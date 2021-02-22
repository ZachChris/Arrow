#pragma once

#include "Arrow/Renderer/Buffers.h"

namespace Arrow {
	
	//-----Vertex Buffer-----

	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* data, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual BufferLayout GetLayout() override { return m_BufferLayout; }
		virtual void SetLayout(const BufferLayout& bufferLayout) override { m_BufferLayout = bufferLayout; }
	private:
		uint32_t m_RendererID;
		BufferLayout m_BufferLayout;
	};

	//-----Index Buffer-----

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(unsigned int* data, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() override { return m_Count/sizeof(unsigned int); }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}