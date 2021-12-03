#pragma once

#include "Arrow/ImGui/ImGuiLayer.h"

namespace Arrow {

	class OpenGLImGuiLayer : public ImGuiLayer {
	public:
		OpenGLImGuiLayer();
		virtual  ~OpenGLImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		virtual void Begin() override;
		virtual void End() override;
	};

}