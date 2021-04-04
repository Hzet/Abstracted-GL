#include "shader-program.hpp"

#include <glm/gtc/type_ptr.hpp>

#include "../System/gl-core.hpp"
#include "../System/error.hpp"
#include "../System/error-code.hpp"

namespace agl
{
	constexpr static std::uint64_t GetBit(std::uint64_t type)
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

		AGL_CORE_ERROR("Invalid shader type - {}", error::INVALID_VALUE, type);
		return 0u;
	}

	CShader CShader::LoadFromFile(const std::string &vertex, const std::string &fragment, const std::string &geometry /*= ""*/, const std::string &tessControl /*= ""*/, const std::string &tessEvaluation /*= ""*/, const std::string &compute /*= ""*/)
	{
		CShader result;
		result.attachFromFile(GL_VERTEX_SHADER, vertex);
		result.attachFromFile(GL_FRAGMENT_SHADER, fragment);
		result.attachFromFile(GL_GEOMETRY_SHADER, geometry);
		result.attachFromFile(GL_TESS_CONTROL_SHADER, tessControl);
		result.attachFromFile(GL_TESS_EVALUATION_SHADER, tessEvaluation);
		result.attachFromFile(GL_COMPUTE_SHADER, compute);

		return result;
	}

	CShader CShader::LoadFromSource(const std::string &vertex, const std::string &fragment, const std::string &geometry /*= ""*/, const std::string &tessControl /*= ""*/, const std::string &tessEvaluation /*= ""*/, const std::string &compute /*= ""*/)
	{
		CShader result;
		result.attachFromSource(GL_VERTEX_SHADER, vertex);
		result.attachFromSource(GL_FRAGMENT_SHADER, fragment);
		result.attachFromSource(GL_GEOMETRY_SHADER, geometry);
		result.attachFromSource(GL_TESS_CONTROL_SHADER, tessControl);
		result.attachFromSource(GL_TESS_EVALUATION_SHADER, tessEvaluation);
		result.attachFromSource(GL_COMPUTE_SHADER, compute);

		return result;
	}

	CShader::CShader()
		: shaderBits_(0u)
	{
	}

	CShader::~CShader()
	{
		if (!isMoveConstructing())
			destroy();
	}

	bool CShader::attachFromSource(std::uint64_t type, const std::string &source)
	{
		if (source.empty())
			return false;

		subshaders_.emplace_back(graphics::CSubShader());
		const bool result = subshaders_.back().setSource(type, source);

		if (result)
			setBit(GetBit(type));

		return result;
	}

	bool CShader::attachFromFile(std::uint64_t type, const std::string &filename)
	{
		if (filename.empty())
			return false;

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
			AGL_CORE_ERROR("Vertex shader is obligatory to compile a shader program!", error::SHADER_LINK);
			return false;
		}
		else if (!hasShader(GL_FRAGMENT_SHADER_BIT))
		{
			AGL_CORE_ERROR("Fragment shader is obligatory to compile a shader program!", error::SHADER_LINK);
			return false;
		}

		if (!compileSubshaders())
		{
			AGL_CORE_ERROR("Shader could not be linked!", error::SHADER_LINK);
			return false;
		}

		create();

		for (const auto &v : subshaders_)
			AGL_CALL(glAttachShader(objectID_, v.getID()));

		AGL_CALL(glLinkProgram(objectID_));

		std::int32_t result;
		AGL_CALL(glGetProgramiv(objectID_, GL_LINK_STATUS, &result));

		subshaders_.clear();

		if (!result)
		{
			std::int32_t length;
			AGL_CALL(glGetProgramiv(objectID_, GL_INFO_LOG_LENGTH, &length));

			std::string message;
			message.resize(length);

			AGL_CALL(glGetProgramInfoLog(objectID_, length, NULL, &message[0u]));
			AGL_CORE_ERROR("Failed to link a shader program! \nDescription: {}", error::SHADER_LINK, message);

			return false;
		}

		return true;
	}

	void CShader::setActive() const
	{
		bind();
	}

	bool CShader::hasShader(std::uint64_t bit) const
	{
		return (shaderBits_ & bit);
	}

	void CShader::create()
	{
		if (isCreated())
			destroy();

		AGL_CALL(objectID_ = glCreateProgram());
	}

	void CShader::bind() const
	{
		AGL_CALL(glUseProgram(objectID_));
	}

	void CShader::setBit(std::uint64_t bit)
	{
		shaderBits_ |= bit;
	}

	void CShader::destroy()
	{
		AGL_CALL(glDeleteProgram(objectID_));

		objectID_ = 0u;
		shaderBits_ = 0u;
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
			subshaders_.clear();

		return result;
	}

	void CShader::setUniform(const std::string &name, const float value) const
	{
		glUniform1f(getLocation(name), value);
	}

	void CShader::setUniform(const std::string &name, const std::int32_t value) const
	{
		AGL_CALL(glUniform1i(getLocation(name), value));
	}

	void CShader::setUniform(const std::string &name, const std::uint32_t value) const
	{
		AGL_CALL(glUniform1ui(getLocation(name), value));

	}

	void CShader::setUniform(const std::string &name, const glm::vec2 &value) const
	{
		AGL_CALL(glUniform2f(getLocation(name), value.x, value.y));
	}

	void CShader::setUniform(const std::string &name, const glm::vec3 &value) const
	{
		AGL_CALL(glUniform3f(getLocation(name), value.x, value.y, value.z));
	}

	void CShader::setUniform(const std::string &name, const glm::vec4 &value) const
	{
		AGL_CALL(glUniform4f(getLocation(name), value.x, value.y, value.z, value.w));
	}

	void CShader::setUniform(const std::string &name, const glm::mat4 &value) const
	{
		AGL_CALL(glUniformMatrix4fv(getLocation(name), 1u, GL_FALSE, glm::value_ptr(value)));
	}

	void CShader::setUniform(const std::string &name, std::int32_t const * const value, std::uint64_t count) const
	{
		AGL_CALL(glUniform1iv(getLocation(name), count, value));
	}

	std::int32_t CShader::getLocation(const std::string &name) const
	{
		std::int32_t result;

		AGL_CALL(result = glGetUniformLocation(objectID_, name.c_str()));
		AGL_CORE_ASSERT(result != -1, "Uniform with such name does not exist!\nName: {}", name);

		return result;
	}
}

