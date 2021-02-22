#include "arpch.h"

#include "Arrow/Renderer/Camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Arrow {

	PerspectiveCamera::PerspectiveCamera(const float& fov, const float& aspectRatio, const float& zNear, const float& zFar, const glm::vec3& pos, const glm::vec3& rot)
		: m_Fov(fov), m_AspectRatio(aspectRatio), m_zNear(zNear), m_zFar(zFar), m_Position(pos), m_Rotation(rot) {

		m_Prog = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_zNear, m_zFar);
		m_View = glm::lookAt(m_Position, m_Position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		m_Matrix = m_Prog * m_View;
	}

	void PerspectiveCamera::SetPosition(const glm::vec3& pos) {
		m_Position = pos;
		RecalculateMatrix();
	}

	void PerspectiveCamera::SetRotation(const glm::vec3& rot) {
		m_Rotation = rot;
		RecalculateMatrix();
	}

	void PerspectiveCamera::SetAspectRatio(const float& aspectRatio) {
		m_AspectRatio = aspectRatio;
		m_Prog = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_zNear, m_zFar);
		RecalculateMatrix();
	}

	void PerspectiveCamera::RecalculateMatrix() {
		m_View = glm::lookAt(m_Position, m_Position + m_Rotation, glm::vec3(0.0f, 1.0f, 0.0f));

		m_Matrix = m_Prog * m_View;
	}

}