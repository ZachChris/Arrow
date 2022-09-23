#pragma once

#include "Registry.h"

namespace Arrow {

	class Scene {
		friend class Entity;
	public:
		Scene() {

		}
	private:
		Registry m_Registry;
	};

}