#include "arpch.h"

#include "Shader.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Arrow {

	std::shared_ptr<Shader> Shader::Create(const std::string& filepath) {
		switch (RendererAPI::GetAPI()) {
			case RendererAPI::API::NONE:	return nullptr; ASSERT(false, "No API selected"); break;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath); break;
		}

		AR_ERROR("No Shader Created");
		return nullptr;
	}

	std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (RendererAPI::GetAPI()) {
			case RendererAPI::API::NONE:	return nullptr; ASSERT(false, "No API selected"); break;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc); break;
		}

		AR_ERROR("No Shader Created");
		return nullptr;
	}

	void ShaderLibrary::Add(std::shared_ptr<Shader> shader) {
		if (Exists(shader->GetName()))
			AR_ERROR("Shader {0} already exists", shader->GetName());

		m_Shaders[shader->GetName()] = shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& filepath) {
		std::shared_ptr<Shader> shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
		std::shared_ptr<Shader> shader = Shader::Create(name, vertexSrc, fragmentSrc);
		Add(shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name) {
		if (Exists(name))
			return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) {
		if (m_Shaders.find(name) != m_Shaders.end())
			return true;

		return false;
	}

}