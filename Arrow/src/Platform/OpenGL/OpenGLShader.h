#pragma once

#include "Arrow/Renderer/Shader.h"
#include "glm/glm.hpp"

#include <glad/glad.h>
#include <unordered_map>

namespace Arrow {

	class OpenGLShader : public Shader {
	public:	
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

		virtual ~OpenGLShader();

		virtual std::string GetName() const override { return m_Name; }

		virtual void UploadUniformFloat(const std::string& name, const float& value) override;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& values) override;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& values) override;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& values) override;

		virtual void UploadUniformMat2(const std::string& name, const glm::mat2& matrix) override;
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		//---Shader Creation Helper Funcs---
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> ParseShader(const std::string& source);
		uint32_t CompileShader(GLenum type, const std::string& source);
		uint32_t CreateShader(const std::unordered_map<GLenum, std::string> mapData);

		//---To help with uniforms
		uint32_t GetUniformLocation(const std::string& name);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
		std::unordered_map<std::string, uint32_t> m_UniformCache;
	};

}