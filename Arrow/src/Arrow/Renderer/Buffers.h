#pragma once

#include "Arrow/Core/Core.h"
#include "Arrow/Renderer/Renderer.h"
#include "Arrow/Renderer/Shader.h"

#include <vector>
#include <string>

namespace Arrow {

	//-----Buffer Layout-----//

	struct BufferElement {
		ShaderDataType m_DataType;
		std::string m_Name;
		uint32_t m_Size;
		uint32_t m_Offset;
		bool m_Normalized;

		BufferElement() = default;
		BufferElement(ShaderDataType type, std::string name, bool normalized = false)
			:m_DataType(type), m_Name(name), m_Normalized(normalized), m_Size(ShaderDataTypeSize(type)), m_Offset(0) {}

		static int CalculateCount(ShaderDataType type) {
				switch (type) {
					case ShaderDataType::Float:		return 1;
					case ShaderDataType::Float2:	return 2;
					case ShaderDataType::Float3:	return 3;
					case ShaderDataType::Float4:	return 4;
					case ShaderDataType::Int:		return 1;
					case ShaderDataType::Int2:		return 2;
					case ShaderDataType::Int3:		return 3;
					case ShaderDataType::Int4:		return 4;
					case ShaderDataType::Mat3:		return 1;//check if right
					case ShaderDataType::Mat4:		return 1;//check if right
					case ShaderDataType::Bool:		return 1;
			}

			AR_ERROR("Uknown Shader Data Type!!!");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			:m_Elements(elements) {
		
			CalculateStrideAndOffset();
		}
		~BufferLayout() {}
		
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() { return m_Elements; }
	private:
		void CalculateStrideAndOffset() {
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.m_Offset = offset;
				offset += element.m_Size;
				m_Stride += element.m_Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	//-----Vertex Buffer-----//

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual BufferLayout GetLayout() = 0;
		virtual void SetLayout(const BufferLayout& bufferLayout) = 0;

		static std::shared_ptr<VertexBuffer> Create(float* data, uint32_t size);
	};
	
	//-----Index Buffer-----//

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() = 0;

		static std::shared_ptr<IndexBuffer> Create(unsigned int* data, uint32_t count);
	};

}