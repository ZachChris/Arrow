#pragma once

#include "glm/glm.hpp"

namespace Arrow {

	class Transform {
	public:
		Transform()
			: m_Position(glm::vec3(0.0f)), m_Rotation(glm::vec3(0.0f)), m_Scale(glm::vec3(1.0f)) {
		//TO DO 
			m_Transform = glm::mat4(1.0f);
		}

		Transform(glm::vec3 position, glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f))
			: m_Position(position), m_Rotation(rotation), m_Scale(scale) {
			//TO DO 
			m_Transform = glm::mat4(1.0f);
		}

		~Transform() {}

		void SetPosition(const glm::vec3 position) { m_Position = position; }
		void SetRotation(const glm::vec3 rotation) { m_Rotation = rotation; }
		void SetScale(const glm::vec3 scale) { m_Scale = scale; }

		glm::vec3 GetPosition() { return m_Position; }
		glm::vec3 GetRotation() { return m_Rotation; }
		glm::vec3 GetScale() { return m_Scale; }

	private:
		glm::mat4 m_Transform;

		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
	};

}
