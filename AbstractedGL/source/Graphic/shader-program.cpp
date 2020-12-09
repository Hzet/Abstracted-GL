#include "shader-program.hpp"

#include "../System/gl-core.hpp"
#include "../System/error.hpp"
#include "../System/core-error-codes.hpp"

namespace agl
{
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
		: programID_(0u),
		move_(false)
	{
	}

	CShader::CShader(CShader &&other)
		: programID_(std::move(other.programID_)),
		shaderBits_(std::move(other.shaderBits_)),
		subshaders_(std::move(other.subshaders_))
	{
		other.move_ = true;
	}

	CShader::~CShader()
	{
		if (!move_)
			destroy();
	}


	bool CShader::attachFromString(std::uint64_t type, const std::string &source)
	{
		subshaders_.emplace_back(utility::CSubShader());
		const bool result = subshaders_.back().setSource(type, source);

		if (result)
			setBit(GetBit(type));

		return result;
	}

	bool CShader::attachFromFile(std::uint64_t type, const std::string &filename)
	{
		subshaders_.emplace_back(utility::CSubShader());
		const bool result = subshaders_.back().loadFromFile(type, filename);

		if (result)
			setBit(GetBit(type));

		return result;
	}

	bool CShader::attachFromMemory(std::uint64_t type, const char *data, std::uint64_t size)
	{
		subshaders_.emplace_back(utility::CSubShader());
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

