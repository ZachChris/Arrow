#include "EditorLayer.h"
#include "imgui.h"

namespace Arrow {

    EditorLayer::EditorLayer()
        : Layer("Editor Layer"), controller(60.0f, 1280.f / 720.f, 0.1f, 100.0f, 1.0f, 0.1f),
        pointLight({ -1.0f, 1.0f, 0.0f }, glm::vec3(1.0f), 1.0f, 0.007f, 0.0002f),
        spotLight({ 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, glm::vec3(1.0f), glm::cos(glm::radians(12.5f)), 1.0f, 0.007f, 0.0002f) {

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
                                          "resources/textures/skybox/back.png" });

        skyboxShader = shaderLibrary.Load("resources/shaders/Skybox.glsl");
        drawShader = shaderLibrary.Load("resources/shaders/Material.glsl");
        framebufferShader = shaderLibrary.Load("resources/shaders/FrameBuffer.glsl");
        Arrow::Renderer::Init(skyboxShader, drawShader, framebufferShader, skybox);
    }
        
    void EditorLayer::OnAttach() {}

    void EditorLayer::OnUpdate(DeltaTime deltaTime) {
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

	void EditorLayer::OnImGuiRender() {
        static bool dockspaceOpen = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen) {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->GetWorkPos());
            ImGui::SetNextWindowSize(viewport->GetWorkSize());
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        } else {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            ImGui::Begin("Viewport");
            ImVec2 viewportSize = ImGui::GetContentRegionAvail();
            if (m_ViewportSize != *((glm::vec2*)&viewportSize)) {
                //frameBuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
                m_ViewportSize = { viewportSize.x, viewportSize.y };

                controller.SetAspectRatio(m_ViewportSize.x / m_ViewportSize.y);
            }
            ImGui::Image((void*)frameBuffer->GetColorAttachment(), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
            ImGui::End();
            ImGui::PopStyleVar();

        ImGui::End();
	}

}