#include "arpch.h"

#include "Arrow/Renderer/Model.h"

#include "glm/glm.hpp"

namespace Arrow {

	std::shared_ptr<Model> Model::Create(const std::string& filepath) {
		return std::make_shared<Model>(filepath);
	}

	std::shared_ptr<Model> Model::Create(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer) {
		return std::make_shared<Model>(vertexBuffer, indexBuffer);
	}

	std::shared_ptr<Model> Model::CreateCube() {
		float vertecies[3 * 24] = {
			//Positions
			-0.5f, -0.5f, 0.5f,
			 0.5f, -0.5f, 0.5f,
			 0.5f,  0.5f, 0.5f,
			-0.5f,  0.5f, 0.5f,
							   
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
							   
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
							   
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,
							   
			-0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
							   
			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f
		};
		
		unsigned int indecies[6 * 6] = {
			0,  1,  2,
			2,  3,  0,
			        
			4,  5,  6,
			6,  7,  4,
		
			8,  9,  10,
			10, 11, 8,
		
			12, 13, 14,
			14, 15, 12,
		
			16, 17, 18,
			18, 19, 16,
		
			20, 21, 22,
			22, 23, 20
		};
		
		std::shared_ptr<VertexBuffer> vertexBuffer = Arrow::VertexBuffer::Create(vertecies, sizeof(vertecies));
		std::shared_ptr<IndexBuffer> indexBuffer = Arrow::IndexBuffer::Create(indecies, sizeof(indecies));
		
		Arrow::BufferLayout layout = {
			{ Arrow::ShaderDataType::Float3, "a_Position" },
		};
		
		vertexBuffer->SetLayout(layout);

		return std::make_shared<Model>(vertexBuffer, indexBuffer);
	}

	Model::Model(const std::string& filepath) {
		size_t pos = filepath.rfind('.') + 1;
		std::string type = filepath.substr(pos, filepath.size());
		if (type == "obj")
			ProcessObjFile(filepath);
	}

	Model::Model(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer)
		:m_VertexBuffer(vertexBuffer), m_IndexBuffer(indexBuffer) {}

	void Model::ProcessObjFile(const std::string& filepath) {
		char key[64];
		std::vector<unsigned int> vertexIndex;
		std::vector<unsigned int> texIndex;
		std::vector<unsigned int> normalIndex;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> texCoords;
		std::vector<glm::vec3> normals;

		unsigned int vIndex[3], tIndex[3], nIndex[3];
		glm::vec3 vertex;
		glm::vec2 texCoor;
		glm::vec3 normal;

		FILE *file;

		if (fopen_s(& file, filepath.c_str(), "r") != 0)
			AR_ERROR("Can't open file {0}", filepath);
		else {
			while (true) {
				int result = fscanf(file, "%s", key);
				if (result == EOF)
					break;
				else if (strcmp(key, "v") == 0) {
					fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
					vertices.push_back(vertex);
				} else if (strcmp(key, "vt") == 0) {
					fscanf(file, "%f %f %f\n", &texCoor.x, &texCoor.y);
					texCoords.push_back(texCoor);
				} else if (strcmp(key, "vn") == 0) {
					fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
					normals.push_back(normal);
				} else if (strcmp(key, "f") == 0) {
					fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vIndex[0], &tIndex[0], &nIndex[0], &vIndex[1], &tIndex[1], &nIndex[1], &vIndex[2], &tIndex[2], &nIndex[2]);
					vertexIndex.push_back(vIndex[0] - 1);
					vertexIndex.push_back(vIndex[1] - 1);
					vertexIndex.push_back(vIndex[2] - 1);
					texIndex.push_back(tIndex[0] - 1);
					texIndex.push_back(tIndex[1] - 1);
					texIndex.push_back(tIndex[2] - 1);
					normalIndex.push_back(nIndex[0] - 1);
					normalIndex.push_back(nIndex[1] - 1);
					normalIndex.push_back(nIndex[2] - 1);
				}
			}

			std::vector<unsigned int> indecies;
			std::vector<Vertex> vertex;
			std::unordered_map<unsigned int, unsigned int> indexMap;
			unsigned int currentIndex = 0;

			for (unsigned int i = 0; i < vertexIndex.size(); i++) {

				unsigned int previousIndex = -1;
				for (unsigned int j = 0; j < i; j++) {
					if (vertexIndex[i] == vertexIndex[j] && texIndex[i] == texIndex[j] && normalIndex[i] == normalIndex[j]) {
						previousIndex = j;
						break;
					}
				}

				if (previousIndex == -1) {
					vertex.push_back(Vertex(vertices[vertexIndex[i]], texCoords[texIndex[i]], normals[normalIndex[i]]));

					indecies.push_back(currentIndex);
					indexMap[i] = currentIndex;
					currentIndex++;
				} else
					indecies.push_back(indexMap[previousIndex]);
			}

			CalculateTangents(vertex, indecies);

			std::vector<float> vertexData;
			for (auto vrt : vertex) {
				vertexData.push_back(vrt.Position.x);
				vertexData.push_back(vrt.Position.y);
				vertexData.push_back(vrt.Position.z);
				vertexData.push_back(vrt.UV.x);
				vertexData.push_back(vrt.UV.y);
				vertexData.push_back(vrt.Normal.x);
				vertexData.push_back(vrt.Normal.y);
				vertexData.push_back(vrt.Normal.z);
				vertexData.push_back(vrt.Tangent.x);
				vertexData.push_back(vrt.Tangent.y);
				vertexData.push_back(vrt.Tangent.z);
			}

			m_VertexBuffer = VertexBuffer::Create(vertexData.data(), (uint32_t)vertexData.size() * sizeof(float));
			m_IndexBuffer = IndexBuffer::Create(indecies.data(), (uint32_t)indecies.size() * sizeof(unsigned int));

			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float2, "a_TexCoord"},
				{ ShaderDataType::Float3, "a_NormalCoord"},
				{ ShaderDataType::Float3, "a_Tangent"}
			};

			m_VertexBuffer->SetLayout(layout);
		}
	}

	void Model::CalculateTangents(std::vector<Vertex>& vertex, const std::vector<unsigned int>& index) {
		glm::vec3 tang;
		for (int i = 0; i < index.size(); i += 3) {
			glm::vec3 edge1 = vertex[index[i + 1]].Position - vertex[index[i]].Position;
			glm::vec3 edge2 = vertex[index[i + 2]].Position - vertex[index[i]].Position;
			glm::vec2 deltaUV1 = vertex[index[i + 1]].UV - vertex[index[i]].UV;
			glm::vec2 deltaUV2 = vertex[index[i + 2]].UV - vertex[index[i]].UV;

			float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);


			tang.x = (f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x));
			tang.y = (f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y));
			tang.z = (f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z));

			vertex[index[i]].Tangent += tang;
			vertex[index[i + 1]].Tangent += tang;
			vertex[index[i + 2]].Tangent += tang;
		}
		for (auto vrt : vertex) {
			glm::normalize(vrt.Tangent);
		}
	}

}