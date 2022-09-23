#pragma once

namespace Arrow {

	class Component {

	};

	class TransformComponent : public Component {
	public:
		TransformComponent(glm::mat4 transform) 
			: m_Transform(transform) {}
	private:
		glm::mat4 m_Transform;
	};
}