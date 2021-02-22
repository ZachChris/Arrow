#pragma once

#include "Arrow/Core/Core.h"
#include "Arrow/Renderer/Buffers.h"
#include <memory>

namespace Arrow {

	class VertexBuffer;
	class IndexBuffer;

	class VertexArray {
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unnind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> indexBuffer) = 0;

		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();
	};

}