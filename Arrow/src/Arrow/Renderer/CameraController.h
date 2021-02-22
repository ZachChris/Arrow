#pragma once

#include "Arrow/Renderer/Camera.h"

namespace Arrow {

	class PerspectiveCameraController {
	public:
		PerspectiveCameraController(const float& fov, const float& aspectRatio, const float& zNear, const float& zFar, const float& movementSpeed, const float& sensitivity);

		void OnUpdate(DeltaTime deltaTime);

		void SetAspectRatio(const float& aspectRatio) { m_Camera.SetAspectRatio(aspectRatio); }
		void SetZoomLevel(const float& zoomLevel) { m_ZoomLevel = zoomLevel; }

		const inline glm::mat4& GetViewProgectionMatrix() { return m_Camera.GetViewProgectionMatrix(); }
		const inline glm::mat4& GetProgectionMatrix() { return m_Camera.GetProgectionMatrix(); }
		const inline glm::mat4& GetViewMatrix() { return m_Camera.GetViewMatrix(); }
		const inline glm::vec3& GetCameraFront() { return cameraFront; }
		const inline glm::vec3& GetPosition() { return m_Position; }
		const inline glm::vec3& GetRotation() { return m_Rotation; }

	private:
		PerspectiveCamera m_Camera;
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 cameraFront;
		float m_MovementSpeed;
		float m_Sensitivity;
		float lastX, lastY;
		float deltaX, deltaY;
		float pitch, yaw;
		float m_ZoomLevel;
	};
}