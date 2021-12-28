#pragma once

#include "Arrow/Renderer/RendererAPI.h"
#include "Arrow/Renderer/RenderCommand.h"
#include "Arrow/Renderer/VertexArray.h"
#include "Arrow/Renderer/CameraController.h"
#include "Arrow/Renderer/Light.h"
#include "Arrow/Renderer/FrameBuffer.h"
#include "Arrow/Renderer/Shader.h"
#include "Arrow/Renderer/Texture.h"
#include "Arrow/Renderer/Camera.h"
#include "Arrow/Renderer/Model.h"

namespace Arrow {
	class VertexArray;
	class Shader;
	class Model;
	class Cubemap;

	class Renderer {
	public:
		static void Init();
		static void Init(const std::shared_ptr<Shader>& skyboxShader, const std::shared_ptr<Shader>& drawShader, const std::shared_ptr<Shader>& framebufferShader, const std::shared_ptr<Cubemap>& skybox);
		static void Shutdown();

		static void BeginScene(PerspectiveCameraController controller, PointLight pointLight, SpotLight spotLight);

		static void EndScene() {}
		static void EndScene(PerspectiveCameraController controller, const std::shared_ptr<FrameBuffer>& frameBuffer);
		static void EndScene(const std::shared_ptr<FrameBuffer>& frameBuffer);
		static void Submit(const std::shared_ptr<Model>& model, const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f));
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f));
	};

}