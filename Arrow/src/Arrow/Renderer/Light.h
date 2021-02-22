#pragma once

#include "glm/glm.hpp"

namespace Arrow {

	class DirectionalLight {
	public:
		DirectionalLight(const glm::vec3& direction, const glm::vec3& color)
			: m_Direction(direction), m_Color(color) {}

		inline const glm::vec3& GetDirection() { return m_Direction; }
		inline const glm::vec3& GetColor() { return m_Color; }

		inline void SetDirection(const glm::vec3& direction) { m_Direction = direction; }
		inline void SetColor(const glm::vec3& color) { m_Color = color; }
	private:
		glm::vec3 m_Direction;
		glm::vec3 m_Color;
	};

	class PointLight {
	public:
		PointLight(const glm::vec3& position, const glm::vec3& color, const float& constant, const float& linear, const float& quadratic)
			: m_Position(position), m_Color(color),	m_Constant(constant), m_Linear(linear), m_Quadratic(quadratic) {}

		inline const glm::vec3& GetPosition() { return m_Position; }
		inline const glm::vec3& GetColor() { return m_Color; }

		inline const float& GetConstant() { return m_Constant; }
		inline const float& GetLinear() { return m_Linear; }
		inline const float& GetQuadratic() { return m_Quadratic; }

		inline void SetPosition(const glm::vec3& position) { m_Position = position; }
		inline void SetColor(const glm::vec3& color) { m_Color = color; }

		inline void SetConstant(const float& constant) { m_Constant = constant; }
		inline void SetLinear(const float& linear) { m_Linear = linear; }
		inline void SetQuadratic(const float& quadratic) { m_Quadratic = quadratic; }
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Color;

		float m_Constant;
		float m_Linear;
		float m_Quadratic;
	};

	class SpotLight {
	public:
		SpotLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color, const float& cutOff,
			const float& constant, const float& linear, const float& quadratic)
			: m_Position(position), m_Direction(direction), m_Color(color), m_CutOff(cutOff), m_Constant(constant), m_Linear(linear), m_Quadratic(quadratic) {}

		inline const glm::vec3& GetPosition() { return m_Position; }
		inline const glm::vec3& GetDirection() { return m_Direction; }
		inline const glm::vec3& GetColor() { return m_Color; }

		inline const float& GetCutOff() { return m_CutOff; }

		inline const float& GetConstant() { return m_Constant; }
		inline const float& GetLinear() { return m_Linear; }
		inline const float& GetQuadratic() { return m_Quadratic; }

		inline void SetPosition(const glm::vec3& position) { m_Position = position; }
		inline void SetDirection(const glm::vec3& direction) { m_Direction = direction; }
		inline void SetColor(const glm::vec3& color) { m_Color = color; }

		inline void SetCutOff(const float& cutOff) { m_CutOff = cutOff; }

		inline void SetConstant(const float& constant) { m_Constant = constant; }
		inline void SetLinear(const float& linear) { m_Linear = linear; }
		inline void SetQuadratic(const float& quadratic) { m_Quadratic = quadratic; }
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Direction;
		glm::vec3 m_Color;

		float m_CutOff;

		float m_Constant;
		float m_Linear;
		float m_Quadratic;
	};

}