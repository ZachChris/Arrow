#include "arpch.h"

#include "Arrow/Renderer/Renderer.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Arrow {

	struct RendererStorage {
		std::shared_ptr<Shader> SkyboxShader;
		std::shared_ptr<Shader> DrawShader;
		std::shared_ptr<Shader> FramebufferShader;

		std::shared_ptr<VertexArray> SkyboxArray;
		std::shared_ptr<VertexArray> FramebufferArray;

		std::shared_ptr<Cubemap> Skybox;
	};

	static RendererStorage* s_Data;

	void Renderer::Init() {
		AR_WARN("Renderer isn't initalized properly!");
	}

	void Renderer::Init(const std::shared_ptr<Shader>& skyboxShader, const std::shared_ptr<Shader>& drawShader, const std::shared_ptr<Shader>& framebufferShader, const std::shared_ptr<Cubemap>& skybox) {
		s_Data = new RendererStorage();
		
		s_Data->SkyboxShader = skyboxShader;
		s_Data->DrawShader = drawShader;
		s_Data->FramebufferShader = framebufferShader;
		
		s_Data->Skybox = skybox;
		
		s_Data->SkyboxArray = VertexArray::Create();
		
		float skyboxVertices[] = {        
			  -1.f, -1.f, -1.f,
			   1.f, -1.f, -1.f,
		
			  -1.f, -1.f,  1.f,
			   1.f, -1.f,  1.f,
		
			  -1.f,  1.f, -1.f,
			   1.f,  1.f, -1.f,
		
			  -1.f,  1.f,  1.f,
			   1.f,  1.f,  1.f
		};
		
		unsigned int skyboxIndicies[] = {
			4, 0, 5,
			0, 1, 5,
		
			6, 2, 4,
			2, 0, 4,
		
			7, 3, 6,
			3, 2, 6,
		
			5, 1, 7,
			1, 3, 7,
		
			0, 2, 1,
			2, 3, 1,
		
			5, 7, 4,
			7, 6, 4,
		};
		
		Ref<VertexBuffer> skyboxBuffer = VertexBuffer::Create(skyboxVertices, sizeof(skyboxVertices));
		Ref<IndexBuffer> skyboxIndex = IndexBuffer::Create(skyboxIndicies, sizeof(skyboxIndicies));
		
		BufferLayout layout = {
			{ Arrow::ShaderDataType::Float3, "a_TexCoord" }
		};
		skyboxBuffer->SetLayout(layout);
		
		s_Data->SkyboxArray->AddVertexBuffer(skyboxBuffer);
		s_Data->SkyboxArray->SetIndexBuffer(skyboxIndex);

		s_Data->FramebufferArray = VertexArray::Create();

		float quadVertices[] = {
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f,
		-1.0f,  1.0f,  0.0f, 1.0f
		};

		unsigned int quadIndicies[] = {
			0, 1, 2,
			2, 3, 0
		};

		Ref<VertexBuffer> framebufferBuffer = VertexBuffer::Create(quadVertices, sizeof(quadVertices));
		Ref<IndexBuffer> framebufferIndex = IndexBuffer::Create(quadIndicies, sizeof(quadIndicies));

		BufferLayout fbLayout = {
			{ Arrow::ShaderDataType::Float2, "a_Positions" },
			{ Arrow::ShaderDataType::Float2, "a_TexCoord" },
		};
		framebufferBuffer->SetLayout(fbLayout);

		s_Data->FramebufferArray->AddVertexBuffer(framebufferBuffer);
		s_Data->FramebufferArray->SetIndexBuffer(framebufferIndex);
	}

	void Renderer::Shutdown() {
		delete s_Data;
	}

	void Renderer::BeginScene(PerspectiveCameraController controller, PointLight pointLight, SpotLight spotLight) {
		s_Data->DrawShader->Bind();

		s_Data->DrawShader->UploadUniformMat4("u_ProgView", controller.GetViewProgectionMatrix());
		s_Data->DrawShader->UploadUniformFloat3("u_ViewPos", controller.GetPosition());

		s_Data->DrawShader->UploadUniformFloat3("u_PointLight.Position", pointLight.GetPosition());
		s_Data->DrawShader->UploadUniformFloat3("u_PointLight.Color", pointLight.GetColor());
		s_Data->DrawShader->UploadUniformFloat("u_PointLight.Constant", pointLight.GetConstant());
		s_Data->DrawShader->UploadUniformFloat("u_PointLight.Linear", pointLight.GetLinear());
		s_Data->DrawShader->UploadUniformFloat("u_PointLight.Quadratic", pointLight.GetQuadratic());

		//s_Data->DrawShader->UploadUniformFloat3("u_SpotLight.Position", spotLight.GetPosition());
		//s_Data->DrawShader->UploadUniformFloat3("u_SpotLight.Direction", spotLight.GetDirection());
		//s_Data->DrawShader->UploadUniformFloat3("u_SpotLight.Color", spotLight.GetColor());
		//s_Data->DrawShader->UploadUniformFloat("u_SpotLight.Constant", spotLight.GetConstant());
		//s_Data->DrawShader->UploadUniformFloat("u_SpotLight.Linear", spotLight.GetLinear());
		//s_Data->DrawShader->UploadUniformFloat("u_SpotLight.Quadratic", spotLight.GetQuadratic());
		//s_Data->DrawShader->UploadUniformFloat("u_SpotLight.CutOff", spotLight.GetCutOff());
	}

	void Renderer::Submit(const std::shared_ptr<Model>& model, const glm::vec3& position, const glm::vec3& scale) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
		transform = glm::scale(transform, scale);
		s_Data->DrawShader->UploadUniformMat4("u_Model", transform);
		RenderCommand::Draw(model);
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const glm::vec3& position, const glm::vec3& scale) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
		transform = glm::scale(transform, scale);
		s_Data->DrawShader->UploadUniformMat4("u_Model", transform);
		RenderCommand::Draw(vertexArray);
	}

	void Renderer::EndScene(PerspectiveCameraController controller, const std::shared_ptr<FrameBuffer>& frameBuffer) {
		RenderCommand::ChangeDepthMode(DepthMode::Lequal);

		s_Data->SkyboxShader->Bind();
		s_Data->SkyboxShader->UploadUniformMat4("u_Prog", controller.GetProgectionMatrix());
		glm::mat4 view = glm::mat4(glm::mat3(controller.GetViewMatrix()));
		s_Data->SkyboxShader->UploadUniformMat4("u_View", view);

		s_Data->SkyboxArray->Bind();

		s_Data->Skybox->Bind();

		RenderCommand::Draw(s_Data->SkyboxArray);

		RenderCommand::ChangeDepthMode(DepthMode::Less);

		RenderCommand::BindDrawFramebuffer();

		RenderCommand::DepthTest(false);

		RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
		RenderCommand::Clear();

		s_Data->FramebufferShader->Bind();
		s_Data->FramebufferArray->Bind();

		RenderCommand::BindTexture2D(frameBuffer->GetColorAttachment());

		RenderCommand::Draw(s_Data->FramebufferArray);

		RenderCommand::DepthTest(true);
	}

	void Renderer::EndScene(const std::shared_ptr<FrameBuffer>& frameBuffer) {
		RenderCommand::BindDrawFramebuffer();
		
		RenderCommand::DepthTest(false);
		
		RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
		RenderCommand::Clear();
		
		s_Data->FramebufferShader->Bind();
		s_Data->FramebufferArray->Bind();
		
		RenderCommand::BindTexture2D(frameBuffer->GetColorAttachment());
		
		RenderCommand::Draw(s_Data->FramebufferArray);
		
		RenderCommand::DepthTest(true);
	}
}