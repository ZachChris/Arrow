#pragma once

#include <string>
#include "DeltaTime.h"
#include "Arrow/Events/Events.h"

namespace Arrow {

	class Layer {
	public:
		Layer(std::string name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(DeltaTime deltaTime) {}
		virtual void OnEvent(Event& event) {}

		inline std::string& GetName() { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};

}