#include "arpch.h"

#include "Arrow/Core/Core.h"
#include "OpenGLShader.h"

namespace Arrow {

	//--- Shader Creation ---

	OpenGLShader::OpenGLShader(const std::string& filepath) {
		std::string source = ReadFile(filepath);
		std::unordered_map<GLenum, std::string> mapData = ParseShader(source);
		m_RendererID = CreateShader(mapData);

		auto lastSlash = filepath.find_last_of("\//");
		lastSlash = lastSlash == filepath.npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		m_Name = filepath.substr(lastSlash, lastDot - lastSlash);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) 
		: m_Name(name) {
		std::unordered_map<GLenum, std::string> mapData;
		mapData[GL_VERTEX_SHADER] = vertexSrc;
		mapData[GL_FRAGMENT_SHADER] = fragmentSrc;
		m_RendererID = CreateShader(mapData);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath) {
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		
		std::string result;
		if (in) {
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		} else
			AR_ERROR("File not opened {0}", filepath);

		return result;
	}

	static GLenum ShaderType(const std::string& type) {
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;
		if (type == "geomerty")
			return GL_GEOMETRY_SHADER;

		ASSERT(false, "Invalid shader type found. Shader {0} does't exist", type);

		return 0;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::ParseShader(const std::string& source) {
		std::unordered_map<GLenum, std::string> mapData;

		const char* token = "#type";
		size_t tokenLeght = strlen(token);
		size_t pos = source.find(token, 0);
		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);
			ASSERT(false, "File is empty");
			size_t begin = pos + tokenLeght + 1;
			std::string type = source.substr(begin, eol - begin);

			size_t nextLine = source.find_first_not_of("\r\n", eol);
			pos = source.find(token, nextLine);
			mapData[ShaderType(type)] = source.substr(nextLine, pos - (nextLine == std::string::npos ? source.size() - 1 : nextLine));
		}

		return mapData;
	}

	uint32_t OpenGLShader::CompileShader(GLenum type, const std::string& source) {
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			std::vector<GLchar> message(length);
			glGetShaderInfoLog(id, length, &length, &message[0]);
			switch (type) {
				case GL_VERTEX_SHADER: AR_ERROR("Failed to compile vertex shader : {0}", message.data()); break;
				case GL_FRAGMENT_SHADER: AR_ERROR("Failed to compile vertex shader : {0}", message.data()); break;
			}
			
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	uint32_t OpenGLShader::CreateShader(const std::unordered_map<GLenum, std::string> mapData) {
		uint32_t program = glCreateProgram();

		for (auto& data : mapData) {
			uint32_t shader = CompileShader(data.first, data.second);
			glAttachShader(program, shader);
			glDeleteShader(shader);
		}
		
		glLinkProgram(program);
		glValidateProgram(program);

		return program;
	}

	//---Uniform Uploading---

	void OpenGLShader::UploadUniformFloat(const std::string& name, const float& value) {
		glUniform1f(GetUniformLocation(name), value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values) {
		glUniform2f(GetUniformLocation(name), values.x, values.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values) {
		glUniform3f(GetUniformLocation(name), values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values) {
		glUniform4f(GetUniformLocation(name), values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformMat2(const std::string& name, const glm::mat2& matrix) {
		glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) {
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}

	uint32_t OpenGLShader::GetUniformLocation(const std::string& name) {
		if (m_UniformCache.find(name) != m_UniformCache.end())
			return m_UniformCache[name];

		uint32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			AR_ERROR("Invalid Uniform name ({0})", name);
		m_UniformCache[name] = location;

		return m_UniformCache[name];
	}

	//------------------------------------

	OpenGLShader::~OpenGLShader() {
		Unbind();
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}

}