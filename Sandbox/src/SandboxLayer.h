#pragma once

#include <Arrow.h>

class SandboxLayer : public Arrow::Layer {
public:
	SandboxLayer();
	virtual ~SandboxLayer() = default;

	void OnAttach() override;
	void OnDetach() override {}

	void OnUpdate(Arrow::DeltaTime deltaTime) override;
	void OnEvent(Arrow::Event& event) override;
private:
	//---Rendering---//
	Arrow::Ref<Arrow::VertexArray> vertexArray;
	Arrow::Ref<Arrow::FrameBuffer> frameBuffer;
	Arrow::Ref<Arrow::Model> model;
	Arrow::Ref<Arrow::Shader> skyboxShader, drawShader, framebufferShader;
	Arrow::Ref<Arrow::Texture2D> texture, specular, normal;
	Arrow::Ref<Arrow::Cubemap> skybox;
	Arrow::ShaderLibrary shaderLibrary;

	Arrow::PointLight pointLight;
	Arrow::SpotLight spotLight;

	//---Camera---//
	Arrow::PerspectiveCameraController controller;
};