#include "include/shader.h"

namespace engine::openglcore
{
	Shader::Shader(const std::string& vsPath, const std::string& fsPath, const std::string& geoPath)
	{
		std::string vertexSource = ReadFile(vsPath);
		std::string fragmentSource = ReadFile(fsPath);
		std::string geometrySource = ReadFile(geoPath);
		std::cout << vertexSource << std::endl;
		std::cout << fragmentSource << std::endl;
		std::cout << geometrySource << std::endl;
		m_ShaderID = CreateShaderProgram(vertexSource, fragmentSource, geometrySource);
	}

	Shader::~Shader()
	{
		glDeleteShader(m_ShaderID);
	}

	void Shader::UseShaderProgram()
	{
		glUseProgram(m_ShaderID);
	}


	void Shader::SetBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), (GLint)value);
	}

	void Shader::SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), value);
	}

	void Shader::SetUint(const std::string& name, uint32_t value) const
	{
		glUniform1ui(glGetUniformLocation(m_ShaderID, name.c_str()), value);
	}

	void Shader::SetFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_ShaderID, name.c_str()), value);
	}

	void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, &value[0]);
	}

	void Shader::SetVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(m_ShaderID, name.c_str()), x, y);
	}

	void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, &value[0]);
	}

	void Shader::SetVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(m_ShaderID, name.c_str()), x, y, z);
	}

	void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, &value[0]);
	}

	void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
	{
		glUniform4f(glGetUniformLocation(m_ShaderID, name.c_str()), x, y, z, w);
	}

	void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	uint32_t Shader::CreateShader(const std::string& file, int type)
	{
		GLuint shader = glCreateShader(type);
		const char* shader_src = file.c_str();
		glShaderSource(shader, 1, &shader_src, NULL);
		glCompileShader(shader);
		CheckShaderError("shader", shader);
		return shader;
	}

	uint32_t& Shader::CreateShaderProgram(const std::string& vertexsource, const std::string& fragmentsource, const std::string& geometrySource)
	{
		GLuint vertexShader = CreateShader(vertexsource, GL_VERTEX_SHADER);
		GLuint fragmentShader = CreateShader(fragmentsource, GL_FRAGMENT_SHADER);
		GLuint geometryShader = NULL;
		if (geometrySource != "")
		{
			geometryShader = CreateShader(geometrySource, GL_GEOMETRY_SHADER);
		}
		m_ShaderID = glCreateProgram();
		glAttachShader(m_ShaderID, vertexShader);
		glAttachShader(m_ShaderID, fragmentShader);
		if (geometryShader != NULL)
			glAttachShader(m_ShaderID, geometryShader);
		glLinkProgram(m_ShaderID);
		CheckShaderError("program", m_ShaderID);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		if (geometryShader != NULL)
			glDeleteShader(geometryShader);
		return m_ShaderID;
	}


	void Shader::CheckShaderError(const std::string& name, GLuint shader)
	{
		if (name == "program")
		{
			int success;
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				char infoLog[1024];
				glGetProgramInfoLog(m_ShaderID, 1024, NULL, infoLog);
				std::cout << "Error:" << "program:" << infoLog << std::endl;
				throw new std::exception();
			}
			else std::cout << "Shader program created successfully!" << std::endl;
		}
		else
		{
			int success;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				char infoLog[1024];
				glGetShaderInfoLog(m_ShaderID, 1024, NULL, infoLog);
				std::cout << "Error:" << "program:" << infoLog << std::endl;
				throw new std::exception();
			}
			else std::cout << "Shader created successfully!" << std::endl;
		}
	}
	std::string Shader::ReadFile(const std::string& filepath)
	{
		std::ifstream infile(filepath);
		if (infile)
		{
			std::stringstream strstream;
			strstream << infile.rdbuf();
			std::string result = strstream.str();
			return result;
		}
		return "";
	}
}