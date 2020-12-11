#include "shader-program.hpp"

#include <glm/gtc/type_ptr.hpp>

#include "../System/gl-core.hpp"
#include "../System/error.hpp"
#include "../System/core-error-codes.hpp"

namespace agl
{
	static std::int32_t getLocation(std::uint32_t programID, const std::string &name)
	{
		std::int32_t result;

		AGL_CALL(result = glGetUniformLocation(programID, name.c_str()));
		AGL_CORE_ASSERT(result != -1, "Uniform with such name does not exist!");

		return result;
	}

	constexpr std::uint64_t CShader::GetBit(std::uint64_t type)
	{
		switch (type)
		{
			switch (type)
			{
			case GL_VERTEX_SHADER: return GL_VERTEX_SHADER_BIT;
			case GL_TESS_CONTROL_SHADER: return GL_TESS_CONTROL_SHADER_BIT;
			case GL_TESS_EVALUATION_SHADER: return GL_TESS_EVALUATION_SHADER_BIT;
			case GL_GEOMETRY_SHADER: return GL_GEOMETRY_SHADER_BIT;
			case GL_FRAGMENT_SHADER: return GL_FRAGMENT_SHADER_BIT;
			case GL_COMPUTE_SHADER: return GL_COMPUTE_SHADER_BIT;
			}

			AGL_CORE_ERROR("Invalid shader type - {}", Error::INVALID_VALUE, type);
			return 0u;
		}
	}

	CShader::CShader()
		: programID_(0u)
	{
	}

	CShader::~CShader()
	{
		if (!isMoveConstructing())
			destroy();
	}


	bool CShader::attachFromString(std::uint64_t type, const std::string &source)
	{
		subshaders_.emplace_back(graphics::CSubShader());
		const bool result = subshaders_.back().setSource(type, source);

		if (result)
			setBit(GetBit(type));

		return result;
	}

	bool CShader::attachFromFile(std::uint64_t type, const std::string &filename)
	{
		subshaders_.emplace_back(graphics::CSubShader());
		const bool result = subshaders_.back().loadFromFile(type, filename);

		if (result)
			setBit(GetBit(type));

		return result;
	}

	bool CShader::attachFromMemory(std::uint64_t type, const char *data, std::uint64_t size)
	{
		subshaders_.emplace_back(graphics::CSubShader());
		const bool result = subshaders_.back().loadFromMemory(type, data, size);

		if (result)
			setBit(GetBit(type));

		return result;
	}

	bool CShader::link()
	{
		if (!hasShader(GL_VERTEX_SHADER_BIT))
		{
			AGL_CORE_ERROR("Vertex shader is obligatory to compile a shader program!", Error::SHADER_LINK);
			return false;
		}
		else if (!hasShader(GL_FRAGMENT_SHADER_BIT))
		{
			AGL_CORE_ERROR("Fragment shader is obligatory to compile a shader program!", Error::SHADER_LINK);
			return false;
		}

		if (!compileSubshaders())
		{
			AGL_CORE_ERROR("Shader could not be linked!", Error::SHADER_LINK);
			return false;
		}

		AGL_CALL(programID_ = glCreateProgram());

		for (const auto &v : subshaders_)
			AGL_CALL(glAttachShader(v.getType(), v.getID()));

		std::int32_t result;

		AGL_CALL(glGetProgramiv(programID_, GL_LINK_STATUS, &result));

		if (!result)
		{
			std::int32_t length;
			AGL_CALL(glGetProgramiv(programID_, GL_INFO_LOG_LENGTH, &length));

			std::string message;
			message.resize(length);

			AGL_CALL(glGetProgramInfoLog(programID_, length, NULL, &message[0u]));
			AGL_CORE_ERROR("Failed to link a shader program! \nDescription: {}", Error::SHADER_LINK, message);

			for (auto &v : subshaders_)
				v.destroy();

			return false;
		}

		return true;
	}

	void CShader::setActive()
	{
		AGL_CALL(glUseProgram(programID_));
	}

	bool CShader::hasShader(std::uint64_t bit)
	{
		return (shaderBits_ & bit);
	}

	float CShader::setFloat(const std::string &name, const float value) const
	{
		AGL_CALL(glUniform1f(getLocation(programID_, name), value));
	}

	glm::vec2 CShader::setVec2(const std::string &name, const glm::vec2 &value) const
	{
		AGL_CALL(glUniform2f(getLocation(programID_, name), value.x, value.y));
	}

	glm::vec3 CShader::setVec3(const std::string &name, const glm::vec3 &value) const
	{
		AGL_CALL(glUniform3f(getLocation(programID_, name), value.x, value.y, value.z));
	}

	glm::vec4 CShader::setVec4(const std::string &name, const glm::vec4 &value) const
	{
		AGL_CALL(glUniform4f(getLocation(programID_, name), value.x, value.y, value.z, value.w));
	}

	glm::mat4 CShader::setMat4(const std::string &name, const glm::mat4 &value) const
	{
		AGL_CALL(glUniformMatrix4fv(getLocation(programID_, name), 1u, GL_FALSE, glm::value_ptr(value)));
	}

	std::int32_t CShader::setInt(const std::string &name, const std::int32_t value) const
	{
		AGL_CALL(glUniform1i(getLocation(programID_, name), value));
	}

	std::uint32_t CShader::setUnsigned(const std::string &name, const std::uint32_t value) const
	{
		AGL_CALL(glUniform1ui(getLocation(programID_, name), value));
	}

	std::vector<std::int32_t> CShader::setIntArray(const std::string &name, std::int32_t const * const value, std::uint64_t count) const
	{
		AGL_CALL(glUniform1iv(getLocation(programID_, name), count, value));
	}

	void CShader::setBit(std::uint64_t bit)
	{
		shaderBits_ |= bit;
	}

	void CShader::destroy()
	{
		AGL_CALL(glDeleteProgram(programID_));
	}

	bool CShader::compileSubshaders()
	{
		bool result = true;
		for (auto &v : subshaders_)
		{
			if (!v.compile())
			{
				result = false;
				break;
			}
		}

		if (!result)
			for (auto &v : subshaders_)
				v.destroy();

		return result;
	}
}
