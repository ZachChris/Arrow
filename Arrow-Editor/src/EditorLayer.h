#pragma once

#include "Arrow.h"

#include "glm/glm.hpp"
#include "glm/vec4.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Arrow {

	class EditorLayer : public Layer {
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		//virtual void OnDetach() override {}
		
		virtual void OnUpdate(DeltaTime deltaTime) override;
		virtual void OnImGuiRender() override;

		//virtual void OnEvent(Event& event) override;
	private:
		//---Rendering---//
		Ref<VertexArray> vertexArray;
		Ref<FrameBuffer> frameBuffer;
		Ref<Model> model;
		Ref<Shader> skyboxShader, drawShader, framebufferShader;
		Ref<Texture2D> texture, specular, normal;
		Ref<Cubemap> skybox;
		ShaderLibrary shaderLibrary;

		PointLight pointLight;
		SpotLight spotLight;

		Scene m_Scene;
		Ref<Entity> m_Entity;
		TransformComponent m_Transform;

		//---Camera---//
		PerspectiveCameraController controller;
		glm::vec2 m_ViewportSize;
	};

}