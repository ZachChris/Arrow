#pragma once

#include "Arrow/Core/Layer.h"

namespace Arrow {

	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override {}
		virtual void OnDetach() override {}
		virtual void OnImGuiRender() override {}

		virtual void Begin() {}
		virtual void End() {}

		
	private:
		//void SetStyle(); TO DO
	};

	ImGuiLayer* CreateImGuiLayer();
}