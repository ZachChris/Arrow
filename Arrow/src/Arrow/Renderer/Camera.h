#pragma once

#include "Arrow/Core/DeltaTime.h"

#include "glm/glm.hpp"

namespace Arrow {

	class PerspectiveCamera {
	public:
		PerspectiveCamera(const float& fov, const float& aspectRatio, const float& zNear, const float& zFar, const glm::vec3& pos = glm::vec3(0.0f), const glm::vec3& rot = glm::vec3(0.0f));

		void SetPosition(const glm::vec3& pos);
		void SetRotation(const glm::vec3& rot);

		void LookAt() {}

		void SetAspectRatio(const float& aspectRatio);

		const inline glm::mat4& GetProgectionMatrix() { return m_Prog; }
		const inline glm::mat4& GetViewMatrix() { return m_View; }
		const inline glm::mat4& GetViewProgectionMatrix() { return m_Matrix; }
		const inline glm::vec3& GetPosition() { return m_Position; }
		const inline glm::vec3& GetRotation() { return m_Rotation; }
	private:
		void RecalculateMatrix();
	private:
		glm::mat4 m_Matrix;
		glm::mat4 m_Prog;
		glm::mat4 m_View;

		glm::vec3 m_Position;
		glm::vec3 m_Rotation;

		float m_Fov;
		float m_AspectRatio;
		float m_zNear;
		float m_zFar;
	};

}