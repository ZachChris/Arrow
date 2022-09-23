#pragma once

#include "Scene.h"
#include "Component.h"

namespace Arrow {

	class Entity {
	public:
		Entity(Scene scene) : m_Scene(&scene) {
			m_ID = m_Scene->m_Registry.CreateEntityID();
		}

		template<typename T>
		T& AddComponent(T& component) {
			m_Scene->m_Registry.AddComponent(component, m_ID);
			return component;
		}

		template<typename T>
		T& GetComponent() {
			return m_Scene->m_Registry.GetComponent(m_ID);
		}

	private:
		Scene* m_Scene;
		uint32_t m_ID;
	};

}