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
		//ProcessFile(filepath);
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

		FILE* file = fopen(filepath.c_str(), "r");

		if (file == NULL)
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

			std::vector<glm::vec3> tangent;
			tangent.resize(vertexIndex.size());
			glm::vec3 tang;
			for (int i = 0; i < vertexIndex.size(); i += 3) {
				glm::vec3 edge1 = vertices[vertexIndex[i + 1.0]] - vertices[vertexIndex[i]];
				glm::vec3 edge2 = vertices[vertexIndex[i + 2.0]] - vertices[vertexIndex[i]];
				glm::vec2 deltaUV1 = texCoords[texIndex[i + 1.0]] - texCoords[texIndex[i]];
				glm::vec2 deltaUV2 = texCoords[texIndex[i + 2.0]] - texCoords[texIndex[i]];

				float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);


				tang.x = (f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x));
				tang.y = (f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y));
				tang.z = (f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z));

				tangent[vertexIndex[i]] += tang;
				tangent[vertexIndex[i + 1.0]] += tang;
				tangent[vertexIndex[i + 2.0]] += tang;
			}
			for (auto tang : tangent) {
				glm::normalize(tang);
			}

			std::vector<unsigned int> indecies;
			std::vector<float> vertexData;
			std::unordered_map<int, int> indexMap;
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
					vertexData.push_back(vertices[vertexIndex[i]].x);
					vertexData.push_back(vertices[vertexIndex[i]].y);
					vertexData.push_back(vertices[vertexIndex[i]].z);
					vertexData.push_back(texCoords[texIndex[i]].x);
					vertexData.push_back(texCoords[texIndex[i]].y);
					vertexData.push_back(normals[normalIndex[i]].x);
					vertexData.push_back(normals[normalIndex[i]].y);
					vertexData.push_back(normals[normalIndex[i]].z);
					vertexData.push_back(tangent[vertexIndex[i]].x);
					vertexData.push_back(tangent[vertexIndex[i]].y);
					vertexData.push_back(tangent[vertexIndex[i]].z);

					indecies.push_back(currentIndex);
					indexMap[i] = currentIndex;
					currentIndex++;
				} else
					indecies.push_back(indexMap[previousIndex]);
			}

			m_VertexBuffer = VertexBuffer::Create(vertexData.data(), vertexData.size() * sizeof(float));
			m_IndexBuffer = IndexBuffer::Create(indecies.data(), indecies.size() * sizeof(unsigned int));

			Arrow::BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float2, "a_TexCoord"},
				{ ShaderDataType::Float3, "a_NormalCoord"},
				{ ShaderDataType::Float3, "a_Tangent"}
			};

			m_VertexBuffer->SetLayout(layout);
		}
	}

}