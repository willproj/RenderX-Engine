#pragma once
#include "thirdparty_header.h"


namespace engine::openglcore
{
	class Shader
	{
	private:
		uint32_t m_ShaderID;
	public:
		Shader() {};
		Shader(const std::string& vsPath, const std::string& fsPath, const std::string& geoPath = "");
		~Shader();

		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetVec2(const std::string& name, const glm::vec2& value) const;
		void SetVec2(const std::string& name, float x, float y) const;
		void SetVec3(const std::string& name, const glm::vec3& value) const;
		void SetVec3(const std::string& name, float x, float y, float z) const;
		void SetVec4(const std::string& name, const glm::vec4& value) const;
		void SetVec4(const std::string& name, float x, float y, float z, float w) const;
		void SetMat2(const std::string& name, const glm::mat2& mat) const;
		void SetMat3(const std::string& name, const glm::mat3& mat) const;
		void SetMat4(const std::string& name, const glm::mat4& mat) const;

		void UseShaderProgram();
		uint32_t GetShaderProgramID()const { return m_ShaderID; }

	private:
		uint32_t CreateShader(const std::string& file, int type);
		uint32_t& CreateShaderProgram(const std::string& vertexshader, const std::string& fragmentshader, const std::string& gemoetrySource = "");
		void CheckShaderError(const std::string& name, GLuint shader);
		std::string ReadFile(const std::string& filepath);
	};
}