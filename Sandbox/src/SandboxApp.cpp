#include <Arrow.h>

#include "glm/glm.hpp"
#include "glm/vec4.hpp"
#include "glm/gtc/matrix_transform.hpp"

class SandboxLayer : public Arrow::Layer {
public:
	SandboxLayer()
		: Layer("SandboxLayer") , controller(60.0f, 1280.f / 720.f, 0.1f, 100.0f, 1.0f, 0.1f) , 
		pointLight({ -1.0f, 1.0f, 0.0f }, glm::vec3(1.0f), 1.0f, 0.007f, 0.0002f) ,
		spotLight({ 1.0f, 0.0f, 0.0f } , { -1.0f, 0.0f, 0.0f }, glm::vec3(1.0f), glm::cos(glm::radians(12.5f)), 1.0f, 0.007f, 0.0002f) {

		Arrow::FrameBufferSpecifications specs = { 1280, 720 , 1 };
		frameBuffer = Arrow::FrameBuffer::Create(specs);

		vertexArray = Arrow::VertexArray::Create();

		model = Arrow::Model::Create("resources/models/sphere.obj");

		vertexArray->AddVertexBuffer(model->GetVertexBuffer());
		vertexArray->SetIndexBuffer(model->GetIndexBuffer());

		texture = Arrow::Texture2D::Create("resources/textures/test/woodenFloor_albedo.png");
		normal = Arrow::Texture2D::Create("resources/textures/test/woodenFloor_normals.png");
		specular = Arrow::Texture2D::Create("resources/textures/test/woodenFloor_metalness.png");

		skybox = Arrow::Cubemap::Create({ "resources/textures/skybox/right.png",
										  "resources/textures/skybox/left.png",
										  "resources/textures/skybox/top.png",
										  "resources/textures/skybox/bottom.png",
										  "resources/textures/skybox/front.png",
										  "resources/textures/skybox/back.png"});

		skyboxShader = shaderLibrary.Load("resources/shaders/Skybox.glsl");
		drawShader = shaderLibrary.Load("resources/shaders/Material.glsl");
		framebufferShader = shaderLibrary.Load("resources/shaders/FrameBuffer.glsl");
		Arrow::Renderer::Init(skyboxShader, drawShader, framebufferShader, skybox);
	}

	~SandboxLayer() {
		Arrow::Renderer::Shutdown();
	}

	void OnAttach() override {}
	void OnDetach() override {}

	void OnUpdate(Arrow::DeltaTime deltaTime) override {
		frameBuffer->Bind();
		Arrow::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Arrow::RenderCommand::Clear();

		controller.OnUpdate(deltaTime);

		Arrow::Renderer::BeginScene(controller, pointLight, spotLight);

		texture->Bind(0);
		normal->Bind(1);
		specular->Bind(2);

		vertexArray->Bind();

		Arrow::Renderer::Submit(model, glm::vec3(0.0f));

		Arrow::Renderer::EndScene(frameBuffer);
	}
	
	void OnEvent(Arrow::Event& event) override {
		if (event.GetEventClass() == Arrow::EventClass::ApplicationResized) {
			auto& ev = (Arrow::ApplicationResizedEvent&)event;
			if (ev.GetWidth() != 0 || ev.GetHeight() != 0)
				controller.SetAspectRatio((float)ev.GetWidth() / ev.GetHeight());
		} else if (event.GetEventClass() == Arrow::EventClass::MouseScrolled) {
			auto& ev = (Arrow::MouseScrolledEvent&)event;
			controller.SetZoomLevel(ev.GetMouseScrollY());
		}
	}
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

class Sandbox : public Arrow::Application {
public:
	Sandbox() {
		PushLayer(new SandboxLayer());
	}
};

Arrow::Application* Arrow::CreateApplication() {
	return new Sandbox();
}