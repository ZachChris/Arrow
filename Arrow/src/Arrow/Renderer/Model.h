#pragma once

#include "Arrow/Renderer/Buffers.h"

namespace Arrow{

	class VertexBuffer;
	class IndexBuffer;

	struct Vertex {
		glm::vec3 Position;
		glm::vec2 UV;
		glm::vec3 Normal;
		glm::vec3 Tangent;

		Vertex(glm::vec3 position, glm::vec2 uv, glm::vec3 normal, glm::vec3 tangent = glm::vec3(0.0f))
			: Position(position), UV(uv), Normal(normal), Tangent(tangent) {}
	};

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
		void ProcessObjFile(const std::string& source);
		void CalculateTangents(std::vector<Vertex>& vertex, const std::vector<unsigned int>& index);
	private:
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};

}
