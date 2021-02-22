#pragma once

#include "Arrow/Renderer/Buffers.h"

namespace Arrow{

	class VertexBuffer;
	class IndexBuffer;

	class Model {
	public:	
		Model(const std::string& filepath);
		Model(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer);
		~Model() {}

		inline const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const { return m_VertexBuffer; }
		inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

		//Custom Model
		static std::shared_ptr<Model> Create(const std::string& filepath);
		static std::shared_ptr<Model> Create(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer);

		//Fixxed Model
		static std::shared_ptr<Model> CreateCube();
	private:
		//void ProcessFile(const std::string& source);
		void ProcessObjFile(const std::string& source);
	private:
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};

}
