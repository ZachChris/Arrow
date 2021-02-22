#include "arpch.h"

#include "Arrow/Renderer/CameraController.h"

#include "Arrow/Input/Input.h"
#include "Arrow/Input/KeyCodes.h"
#include "Arrow/Input/MouseCodes.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Arrow {

	PerspectiveCameraController::PerspectiveCameraController(const float& fov, const float& aspectRatio, const float& zNear, const float& zFar, const float& movementSpeed, const float& sensitivity)
		: m_Camera(fov, aspectRatio, zNear, zFar), m_MovementSpeed(movementSpeed), m_Sensitivity(sensitivity),
		  pitch(0), yaw(0), deltaX(0), deltaY(0), m_ZoomLevel(0),
		  m_Position(glm::vec3(-2.0f, 0.0f, 0.0f)), m_Rotation(glm::vec3(0.0f)), cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)) {

		lastX = Input::GetMouseX();
		lastY = Input::GetMouseY();
	}

	void PerspectiveCameraController::OnUpdate(DeltaTime deltaTime) {
		deltaX = (Input::GetMouseX() - lastX);
		deltaY = (Input::GetMouseY() - lastY);
		lastX = Input::GetMouseX();
		lastY = Input::GetMouseY();

		deltaX *= m_Sensitivity;
		deltaY *= m_Sensitivity;


		if (Input::MouseButtonPressed(AR_MOUSE_BUTTON_2)) {
			yaw -= deltaX;
			pitch += deltaY;
		}

		if (pitch > 89.0f)
			pitch = 89.0f;
		else if (pitch < -89.0f)
			pitch = -89.0f;

		m_Rotation.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		m_Rotation.y = sin(glm::radians(pitch));
		m_Rotation.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(m_Rotation);
		m_Camera.SetRotation(glm::normalize(m_Rotation));

		if (m_ZoomLevel != 0) {
			m_Position += (float)deltaTime * cameraFront * m_ZoomLevel * 5.0f;
			m_ZoomLevel = 0;
		}
		if (deltaX != 0 && Input::MouseButtonPressed(AR_MOUSE_BUTTON_3))
			m_Position -= glm::normalize(glm::cross(cameraFront, { 0.0f, 1.0f, 0.0f })) * (float)deltaTime * deltaX;
		if (deltaY != 0 && Input::MouseButtonPressed(AR_MOUSE_BUTTON_3))
			m_Position += glm::normalize(glm::cross(cameraFront, { 0.0f, 0.0f, 1.0f })) * (float)deltaTime * deltaY;

		m_Camera.SetPosition(m_Position);
	}

}